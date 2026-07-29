//----------------------------------------------------------------------
//   Copyright 2026 COSEDA Technologies GmbH
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

#ifndef UVM_HANDLE_H_
#define UVM_HANDLE_H_

#include <cstddef>     
#include <cstdint>
#include <functional>
#include <type_traits> 
#include <utility>

namespace uvm
{

template <typename T>
class uvm_weak_handle;

template <typename T>
class uvm_handle
{
public:
    using element_type = T;
    using deleter_type = void (*)(T *); 

    // Constructors / destructor
    uvm_handle() noexcept;
    uvm_handle(std::nullptr_t) noexcept;

    uvm_handle(const uvm_handle &other) noexcept;
    uvm_handle(uvm_handle &&other) noexcept;

    template <typename U,
              typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    uvm_handle(const uvm_handle<U> &other) noexcept;

    ~uvm_handle();

    // Assignment
    uvm_handle &operator=(const uvm_handle &other) noexcept;
    uvm_handle &operator=(uvm_handle &&other) noexcept;

    // Observers
    T *get() const noexcept;
    T &operator*() const;
    T *operator->() const noexcept;
    explicit operator bool() const noexcept;

    std::uint64_t use_count() const noexcept;

    void reset() noexcept;

    void reset(T *raw) noexcept;

    void reset(T *raw, deleter_type del) noexcept;

    void swap(uvm_handle &other) noexcept;

    // Weak
    uvm_weak_handle<T> weak() const noexcept;

private:
    struct control_block;

    // Private constructor used by adopt_ptr() and weak_ptr::lock()
    uvm_handle(T *raw, control_block *cb) noexcept;

    template <typename U>
    friend class uvm_handle;
    template <typename U>
    friend class uvm_weak_handle;

    template <typename U, typename... Args>
    friend uvm_handle<U> make_handle(Args &&...args);

    template <typename U>
    friend uvm_handle<U> adopt_handle(U *raw) noexcept;

    template <typename U>
    friend uvm_handle<U> adopt_handle(U *raw,
                                typename uvm_handle<U>::deleter_type del) noexcept;

    template <typename To, typename From>
    friend uvm_handle<To> static_pointer_cast(const uvm_handle<From>& p) noexcept;

    template <typename To, typename From>
    friend uvm_handle<To> dynamic_pointer_cast(const uvm_handle<From>& p) noexcept;

private:
    T *ptr_;
    control_block *cb_;
};

template <typename T>
class uvm_weak_handle
{
public:
    // Minimal lifecycle
    uvm_weak_handle() noexcept;
    uvm_weak_handle(const uvm_handle<T> &strong) noexcept;

    uvm_weak_handle(const uvm_weak_handle &other) noexcept;
    uvm_weak_handle(uvm_weak_handle &&other) noexcept;

    template <typename U,
              typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    uvm_weak_handle(const uvm_weak_handle<U> &other) noexcept;

    ~uvm_weak_handle();

    uvm_weak_handle &operator=(const uvm_weak_handle &other) noexcept;
    uvm_weak_handle &operator=(uvm_weak_handle &&other) noexcept;

    void reset() noexcept;

    // NEW: rebind weak pointer to track a different strong pointer
    void reset(const uvm_handle<T> &strong) noexcept;

    // The one essential operation
    uvm_handle<T> lock() const noexcept;

private:
    using control_block = typename uvm_handle<T>::control_block;

    // Used internally for converting weak pointers
    uvm_weak_handle(T *raw, control_block *cb) noexcept;

    template <typename U>
    friend class uvm_weak_ptr;

private:
    T *ptr_;
    control_block *cb_;
};

// Creation helpers (usable outside factory)

template <typename T, typename... Args>
uvm_handle<T> make_handle(Args &&...args);

template <typename T>
uvm_handle<T> adopt_handle(T *raw) noexcept;

template <typename T>
uvm_handle<T> adopt_handle(T *raw, typename uvm_handle<T>::deleter_type del) noexcept;

// Cast Functions


template <typename To, typename From>
uvm_handle<To> static_pointer_cast(const uvm_handle<From>& p) noexcept;

template <typename To, typename From>
uvm_handle<To> dynamic_pointer_cast(const uvm_handle<From>& p) noexcept;

template <typename T, typename U>
bool operator==(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept;

template <typename T, typename U>
bool operator!=(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept;

template <typename T>
bool operator==(const uvm_handle<T>& lhs, std::nullptr_t) noexcept;

template <typename T>
bool operator==(std::nullptr_t, const uvm_handle<T>& rhs) noexcept;

template <typename T>
bool operator!=(const uvm_handle<T>& lhs, std::nullptr_t) noexcept;

template <typename T>
bool operator!=(std::nullptr_t, const uvm_handle<T>& rhs) noexcept;

template <typename T, typename U>
bool operator<(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept;

// ============================================================
// Helpers: default deleter
// ============================================================

template <typename T>
static void default_delete(T *p) noexcept
{
    delete p;
}

// ============================================================
// uvm_handle```<T>::control_block
// ============================================================
//
// Per-T control block (because it’s nested inside uvm_handle```<T>).
//
// Counts follow the standard shared_ptr model:
//
// - strong_count: number of owning uvm_handle``` instances
// - weak_count: number of uvm_weak_ptr instances
//              PLUS one "implicit weak" while strong_count > 0
//
// When strong_count reaches 0:
//   - destroy the object (call deleter)
//   - drop the implicit weak
//   - if weak_count becomes 0, delete the control block
//
template <typename T>
struct uvm_handle<T>::control_block
{
    unsigned strong_count;
    unsigned weak_count;

    T *object;
    deleter_type deleter;

    control_block(T *obj, deleter_type del) noexcept
        : strong_count(1)
        , weak_count(1) // implicit weak starts at 1
        , object(obj)
        , deleter(del)
    {
    }

    void destroy_object() noexcept
    {
        // Only called once (when strong_count becomes 0).
        if (object != nullptr) {
            deleter(object);
            object = nullptr;
        }
    }
};

// ============================================================
// uvm_handle```<T> implementation
// ============================================================

template <typename T>
uvm_handle<T>::uvm_handle() noexcept
    : ptr_(nullptr)
    , cb_(nullptr)
{
}

template <typename T>
uvm_handle<T>::uvm_handle(std::nullptr_t) noexcept
    : ptr_(nullptr)
    , cb_(nullptr)
{
}

template <typename T>
uvm_handle<T>::uvm_handle(T *raw, control_block *cb) noexcept
    : ptr_(raw)
    , cb_(cb)
{
}

template <typename T>
uvm_handle<T>::uvm_handle(const uvm_handle &other) noexcept
    : ptr_(other.ptr_)
    , cb_(other.cb_)
{
    if (cb_ != nullptr) {
        ++cb_->strong_count;
    }
}

template <typename T>
uvm_handle<T>::uvm_handle(uvm_handle &&other) noexcept
    : ptr_(other.ptr_)
    , cb_(other.cb_)
{
    other.ptr_ = nullptr;
    other.cb_ = nullptr;
}

template <typename T>
template <typename U, typename>
uvm_handle<T>::uvm_handle(const uvm_handle<U> &other) noexcept
    : ptr_(other.ptr_)
    , cb_(reinterpret_cast<control_block*>(other.cb_))
{
    if (cb_ != nullptr) {
        ++cb_->strong_count;
    }
}

template <typename T>
uvm_handle<T>::~uvm_handle()
{
    reset();
}

template <typename T>
uvm_handle<T> &uvm_handle<T>::operator=(const uvm_handle &other) noexcept
{
    if (this == &other)
        return *this;

    reset();

    ptr_ = other.ptr_;
    cb_ = other.cb_;

    if (cb_ != nullptr) {
        ++cb_->strong_count;
    }
    return *this;
}

template <typename T>
uvm_handle<T> &uvm_handle<T>::operator=(uvm_handle &&other) noexcept
{
    if (this == &other)
        return *this;

    reset();

    ptr_ = other.ptr_;
    cb_ = other.cb_;

    other.ptr_ = nullptr;
    other.cb_ = nullptr;
    return *this;
}

template <typename T>
T *uvm_handle<T>::get() const noexcept
{
    return ptr_;
}

template <typename T>
T &uvm_handle<T>::operator*() const
{
    return *ptr_;
}

template <typename T>
T *uvm_handle<T>::operator->() const noexcept
{
    return ptr_;
}

template <typename T>
uvm_handle<T>::operator bool() const noexcept
{
    return ptr_ != nullptr;
}

template <typename T>
std::uint64_t uvm_handle<T>::use_count() const noexcept
{
    return (cb_ != nullptr) ? static_cast<long>(cb_->strong_count) : 0L;
}

template <typename T>
void uvm_handle<T>::reset() noexcept
{
    if (cb_ == nullptr) {
        ptr_ = nullptr;
        return;
    }

    // Drop one strong reference.
    if (--cb_->strong_count == 0) {

        // Last strong owner: destroy managed object.
        cb_->destroy_object();

        // Drop the implicit weak reference.
        if (--cb_->weak_count == 0) {
            delete cb_;
        }
    }

    ptr_ = nullptr;
    cb_ = nullptr;
}

template <typename T>
void uvm_handle<T>::reset(T *raw) noexcept
{
    // Drop current managed object (if any)
    reset();

    // Adopt the new raw pointer (default delete)
    if (raw == nullptr) {
        return;
    }

    cb_ = new control_block(raw, &default_delete<T>);
    ptr_ = raw;
}

template <typename T>
void uvm_handle<T>::reset(T *raw, deleter_type del) noexcept
{
    // Drop current managed object (if any)
    reset();

    // Adopt the new raw pointer with custom deleter
    if (raw == nullptr) {
        return;
    }

    if (del == nullptr) {
        del = &default_delete<T>;
    }

    cb_ = new control_block(raw, del);
    ptr_ = raw;
}

template <typename T>
void uvm_handle<T>::swap(uvm_handle &other) noexcept
{
    std::swap(ptr_, other.ptr_);
    std::swap(cb_, other.cb_);
}

template <typename T>
uvm_weak_handle<T> uvm_handle<T>::weak() const noexcept
{
    return uvm_weak_handle<T>(*this);
}

// ============================================================
// uvm_weak_ptr<T> implementation
// ============================================================

template <typename T>
uvm_weak_handle<T>::uvm_weak_handle() noexcept
    : ptr_(nullptr)
    , cb_(nullptr)
{
}

template <typename T>
uvm_weak_handle<T>::uvm_weak_handle(const uvm_handle<T> &strong) noexcept
    : ptr_(strong.ptr_)
    , cb_(strong.cb_)
{
    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
}

template <typename T>
uvm_weak_handle<T>::uvm_weak_handle(T *raw, control_block *cb) noexcept
    : ptr_(raw)
    , cb_(cb)
{
    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
}

template <typename T>
uvm_weak_handle<T>::uvm_weak_handle(const uvm_weak_handle &other) noexcept
    : ptr_(other.ptr_)
    , cb_(other.cb_)
{
    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
}

template <typename T>
uvm_weak_handle<T>::uvm_weak_handle(uvm_weak_handle &&other) noexcept
    : ptr_(other.ptr_)
    , cb_(other.cb_)
{
    other.ptr_ = nullptr;
    other.cb_ = nullptr;
}

template <typename T>
template <typename U, typename>
uvm_weak_handle<T>::uvm_weak_handle(const uvm_weak_handle<U> &other) noexcept
    : ptr_(other.ptr_)
    , cb_(other.cb_)
{
    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
}

template <typename T>
uvm_weak_handle<T>::~uvm_weak_handle()
{
    reset();
}

template <typename T>
uvm_weak_handle<T> &uvm_weak_handle<T>::operator=(const uvm_weak_handle &other) noexcept
{
    if (this == &other)
        return *this;

    reset();
    ptr_ = other.ptr_;
    cb_ = other.cb_;

    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
    return *this;
}

template <typename T>
uvm_weak_handle<T> &uvm_weak_handle<T>::operator=(uvm_weak_handle &&other) noexcept
{
    if (this == &other)
        return *this;

    reset();
    ptr_ = other.ptr_;
    cb_ = other.cb_;

    other.ptr_ = nullptr;
    other.cb_ = nullptr;
    return *this;
}

template <typename T>
void uvm_weak_handle<T>::reset() noexcept
{
    if (cb_ == nullptr) {
        ptr_ = nullptr;
        return;
    }

    // Drop one weak reference.
    if (--cb_->weak_count == 0) {
        // Only possible after:
        // - strong_count reached 0 and object was destroyed
        // - implicit weak was dropped
        // - now last weak reference is gone
        delete cb_;
    }

    ptr_ = nullptr;
    cb_ = nullptr;
}

template <typename T>
void uvm_weak_handle<T>::reset(const uvm_handle<T> &strong) noexcept
{
    // Drop current weak reference (if any)
    reset();

    // Rebind to the new strong pointer
    ptr_ = strong.ptr_;
    cb_ = strong.cb_;

    if (cb_ != nullptr) {
        ++cb_->weak_count;
    }
}

template <typename T>
uvm_handle<T> uvm_weak_handle<T>::lock() const noexcept
{
    // Single-threaded SystemC assumption:
    // It is safe to read cb_->strong_count without atomics.
    //
    // If strong_count == 0, the object is already destroyed.
    if (cb_ == nullptr || cb_->strong_count == 0) {
        return uvm_handle<T>(); // empty
    }

    // Promote weak -> strong
    ++cb_->strong_count;

    // Return a new owning handle to the same object/control block.
    return uvm_handle<T>(ptr_, cb_);
}

// ============================================================
// Free functions: make_handle / adopt_handle
// ============================================================

template <typename T, typename... Args>
uvm_handle<T> make_handle(Args &&...args)
{
    // Allocate and manage with the default deleter.
    T *raw = new T(std::forward<Args>(args)...);
    return adopt_handle(raw);
}

template <typename T>
uvm_handle<T> adopt_handle(T *raw) noexcept
{
    if (raw == nullptr) {
        return uvm_handle<T>();
    }

    auto *cb = new typename uvm_handle<T>::control_block(raw, &default_delete<T>);
    return uvm_handle<T>(raw, cb);
}

template <typename T>
uvm_handle<T> adopt_handle(T *raw, typename uvm_handle<T>::deleter_type del) noexcept
{
    if (raw == nullptr) {
        return uvm_handle<T>();
    }

    // If caller passes nullptr, fall back to default delete.
    if (del == nullptr) {
        del = &default_delete<T>;
    }

    auto *cb = new typename uvm_handle<T>::control_block(raw, del);
    return uvm_handle<T>(raw, cb);
}

template <typename To, typename From>
uvm_handle<To> static_pointer_cast(const uvm_handle<From>& p) noexcept
{
    // If p is empty, return empty.
    if (!p.get()) {
        return uvm_handle<To>();
    }

    // Create a new uvm_handle```<To> that shares the SAME control block.
    // We must increment the strong count because we're creating a new strong handle.
    auto* cb = reinterpret_cast<typename uvm_handle<To>::control_block*>(p.cb_);
    ++cb->strong_count;

    return uvm_handle<To>(static_cast<To*>(p.get()), cb);
}

template <typename To, typename From>
uvm_handle<To> dynamic_pointer_cast(const uvm_handle<From>& p) noexcept
{
    if (!p.get()) {
        return uvm_handle<To>();
    }

    // Runtime checked cast
    To* casted = dynamic_cast<To*>(p.get());
    if (!casted) {
        return uvm_handle<To>(); // cast failed
    }

    auto* cb = reinterpret_cast<typename uvm_handle<To>::control_block*>(p.cb_);
    ++cb->strong_count;

    return uvm_handle<To>(casted, cb);
}

template <typename T, typename U>
bool operator==(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator!=(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <typename T>
bool operator==(const uvm_handle<T>& lhs, std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <typename T>
bool operator==(std::nullptr_t, const uvm_handle<T>& rhs) noexcept
{
    return rhs == nullptr;
}

template <typename T>
bool operator!=(const uvm_handle<T>& lhs, std::nullptr_t) noexcept
{
    return !(lhs == nullptr);
}

template <typename T>
bool operator!=(std::nullptr_t, const uvm_handle<T>& rhs) noexcept
{
    return !(rhs == nullptr);
}

template <typename T, typename U>
bool operator<(const uvm_handle<T>& lhs, const uvm_handle<U>& rhs) noexcept
{
    return std::less<const void*>()(lhs.get(), rhs.get());
}


} // namespace uvm

#endif 
