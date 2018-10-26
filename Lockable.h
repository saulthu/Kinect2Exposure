#pragma once
#ifndef LOCKABLE_H_
#define LOCKABLE_H_

#include <memory>
#include <mutex>

// Acts like a pointer to the locked object, but holds a lock for the given variable.
template<typename T>
class Locked
{
public:
  Locked(T& obj, std::mutex& mutex) : _obj(obj), _mutex(mutex) { _mutex.lock(); }
  Locked& operator=(const Locked&) = delete;
  ~Locked() { _mutex.unlock(); }
  // Access members of the locked value.
  const T* operator->() const noexcept { return &_obj; }
  // Access members of the locked value.
  T* operator->() noexcept { return &_obj; }
  // Access the locked value.
  const T& operator*() const noexcept { return _obj; }
  // Access the locked value.
  T& operator*() noexcept { return _obj; }

private:
  T& _obj;
  std::mutex& _mutex;
};

// Lockable value type.
template<typename T>
class Lockable
{
public:
  // Only exists if T() exists.
  Lockable() = default;
  explicit Lockable(T obj) : _obj(std::move(obj)) {}
  // Lock-guards the value for the lifetime of the returned object.
  auto lock() const noexcept { return Locked<const T>(_obj, _mutex); }
  // Lock-guards the value for the lifetime of the returned object.
  auto lock() noexcept { return Locked<T>(_obj, _mutex); }

private:
  T _obj;
  mutable std::mutex _mutex;
};


// Acts like a shared_ptr, but holds a lock for the given pointer.
template<typename TPtr>
class LockedPtr
{
public:
  LockedPtr(TPtr& obj, std::mutex& mutex) : _obj(obj), _mutex(mutex) { _mutex.lock(); }
  LockedPtr& operator=(const LockedPtr&) = delete;
  ~LockedPtr() { _mutex.unlock(); }
  // Access members of the locked shared_ptr.
  auto* operator->() const noexcept { return _obj.get(); }
  // Dereference the locked shared_ptr.
  auto& operator*() const noexcept { return *_obj; }
  // Test if the locked shared_ptr is null.
  explicit operator bool() const noexcept { return bool(_obj); }
  // Assign to the locked shared_ptr (assigns the shared_ptr, not the inner T value).
  void operator=(TPtr obj) { _obj = std::move(obj); }
  // Reset the locked shared_ptr.
  void reset() noexcept { _obj.reset(); }
  // Get the pointer type.
  // WARNING: this is potentially unsafe since the data can be passed around unlocked.
  TPtr value() const noexcept { return _obj; }

private:
  TPtr& _obj;
  std::mutex& _mutex;
};

// Lockable templated pointer type.
template<typename TPtr>
class LockablePtr
{
public:
  LockablePtr()
    : _obj()
    , _mutex(std::make_shared<std::mutex>())
  {
  }
  explicit LockablePtr(TPtr obj)
    : _obj(std::move(obj))
    , _mutex(std::make_shared<std::mutex>())
  {
  }
  // Lock-guards the pointer for the lifetime of the returned object.
  auto lock() const noexcept { return LockedPtr<const TPtr>(_obj, *_mutex); }
  // Lock-guards the pointer for the lifetime of the returned object.
  auto lock() noexcept { return LockedPtr<TPtr>(_obj, *_mutex); }

private:
  TPtr _obj;
  mutable std::shared_ptr<std::mutex> _mutex;  // Shared so object is copyable e.g. TPtr is shared_ptr<T>
};


template<typename T>
using LockableSharedPtr = LockablePtr<std::shared_ptr<T>>;

template<typename T>
using LockableUniquePtr = LockablePtr<std::unique_ptr<T>>;

#endif // LOCKABLE_H_
