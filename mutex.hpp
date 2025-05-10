#include "thread_safety.hpp"

#include <mutex>
#include <shared_mutex>

namespace tsa {

// Defines an annotated interface for mutexes.
// These methods can be implemented to use any internal mutex implementation.
class CAPABILITY("mutex") Mutex {
private:
  std::mutex mutex_;

public:
  // Acquire/lock this mutex exclusively. Only one thread can have exclusive
  // access at any one time. Write operations to guarded data require an
  // exclusive lock.
  void Lock() ACQUIRE();
  // Release/unlock an exclusive mutex.
  void Unlock() RELEASE();
  // Try to acquire the mutex. Returns true on success, and false on failure.
  bool TryLock() TRY_ACQUIRE(true);
  // Assert that this mutex is currently held by the calling thread.
  // STL has no matching API for mutexes, only std::unique_lock.
  // void AssertHeld() ASSERT_CAPABILITY(this);
  // For negative capabilities.
  // STL has no matching API for mutexes.
  // const Mutex &operator!() const { return *this; }
};

class CAPABILITY("shared_mutex") SharedMutex {
private:
  std::shared_mutex shared_mutex_;

public:
  // Acquire/lock this mutex for read operations, which require only a shared
  // lock. This assumes a multiple-reader, single writer semantics. Multiple
  // threads may acquire the mutex simultaneously as readers, but a writer
  // must wait for all of them to release the mutex before it can acquire it
  // exclusively.
  void ReaderLock() ACQUIRE_SHARED();
  // Release/unlock a shared mutex.
  void ReaderUnlock() RELEASE_SHARED();
  // Try to acquire the mutex for read operations.
  bool ReaderTryLock() TRY_ACQUIRE_SHARED(true);
  // Assert that is mutex is currently held for read operations.
  // owns_lock() is defined only for std::unique_lock.
  // void AssertReaderHeld() ASSERT_SHARED_CAPABILITY(this);
};

} // namespace tsa
