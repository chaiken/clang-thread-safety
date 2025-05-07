#include "mutex.hpp"

namespace tsa_example {

// Tag types for selecting a constructor.
struct adopt_lock_t {
} inline constexpr adopt_lock = {};
struct defer_lock_t {
} inline constexpr defer_lock = {};
struct shared_lock_t {
} inline constexpr shared_lock = {};
// MutexLocker is an RAII class that acquires a mutex in its constructor, and
// releases it in its destructor.
class SCOPED_CAPABILITY MutexLocker {
private:
  tsa::Mutex *mut;
  bool locked;

public:
  // Acquire mu, implicitly acquire *this and associate it with mu.
  MutexLocker(tsa::Mutex *mu) ACQUIRE(mu) : mut(mu), locked(true) {
    mu->Lock();
  }
  // Assume mu is held, implicitly acquire *this and associate it with mu.
  MutexLocker(tsa::Mutex *mu, adopt_lock_t) REQUIRES(mu)
      : mut(mu), locked(true) {}
  // Assume mu is not held, implicitly acquire *this and associate it with mu.
  MutexLocker(tsa::Mutex *mu, defer_lock_t) EXCLUDES(mu)
      : mut(mu), locked(false) {}
  // Same as constructors, but without tag types. (Requires C++17 copy elision.)
  static MutexLocker Lock(tsa::Mutex *mu) ACQUIRE(mu) {
    return MutexLocker(mu);
  }
  static MutexLocker Adopt(tsa::Mutex *mu) REQUIRES(mu) {
    return MutexLocker(mu, adopt_lock);
  }
  static MutexLocker DeferLock(tsa::Mutex *mu) EXCLUDES(mu) {
    return MutexLocker(mu, defer_lock);
  }
  // Release *this and all associated mutexes, if they are still held.
  // There is no warning if the scope was already unlocked before.
  ~MutexLocker() RELEASE() {
    if (locked)
      mut->Unlock();
  }
  // Acquire all associated mutexes exclusively.
  void Lock() ACQUIRE() {
    mut->Lock();
    locked = true;
  }
  // Try to acquire all associated mutexes exclusively.
  bool TryLock() TRY_ACQUIRE(true) { return locked = mut->TryLock(); }
  // Release all associated mutexes. Warn on double unlock.
  void Unlock() RELEASE() {
    mut->Unlock();
    locked = false;
  }
};

class SCOPED_CAPABILITY SharedMutexLocker {
private:
  tsa::SharedMutex *mut;
  bool locked;

public:
  // Acquire mu in shared mode, implicitly acquire *this and associate it with
  // mu.
  SharedMutexLocker(tsa::SharedMutex *mu, shared_lock_t) ACQUIRE_SHARED(mu)
      : mut(mu), locked(true) {
    mu->ReaderLock();
  }
  // Assume mu is held in shared mode, implicitly acquire *this and associate it
  // with mu.
  SharedMutexLocker(tsa::SharedMutex *mu, adopt_lock_t, shared_lock_t)
      REQUIRES_SHARED(mu)
      : mut(mu), locked(true) {}
  // Assume mu is not held, implicitly acquire *this and associate it with mu.
  SharedMutexLocker(tsa::SharedMutex *mu, defer_lock_t) EXCLUDES(mu)
      : mut(mu), locked(false) {}
  static SharedMutexLocker ReaderLock(tsa::SharedMutex *mu) ACQUIRE_SHARED(mu) {
    return SharedMutexLocker(mu, shared_lock);
  }
  static SharedMutexLocker AdoptReaderLock(tsa::SharedMutex *mu)
      REQUIRES_SHARED(mu) {
    return SharedMutexLocker(mu, adopt_lock, shared_lock);
  }
  // Release *this and all associated mutexes, if they are still held.
  // There is no warning if the scope was already unlocked before.
  ~SharedMutexLocker() RELEASE() {
    if (locked)
      mut->ReaderUnlock();
  }
  // Acquire all associated mutexes in shared mode.
  void ReaderLock() ACQUIRE_SHARED() {
    mut->ReaderLock();
    locked = true;
  }
  // Try to acquire all associated mutexes in shared mode.
  bool ReaderTryLock() TRY_ACQUIRE_SHARED(true) {
    return locked = mut->ReaderTryLock();
  }
  // Release all associated mutexes. Warn on double unlock.
  void ReaderUnlock() RELEASE() {
    mut->ReaderUnlock();
    locked = false;
  }
};

} // namespace tsa_example
