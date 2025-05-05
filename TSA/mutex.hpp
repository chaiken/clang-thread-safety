#include "thread_safety.hpp"

#include <mutex>

namespace tsa {

// Defines an annotated interface for mutexes.
// These methods can be implemented to use any internal mutex implementation.
class CAPABILITY("mutex") Mutex {
public:
  // Acquire/lock this mutex exclusively. Only one thread can have exclusive
  // access at any one time. Write operations to guarded data require an
  // exclusive lock.
  void Lock() ACQUIRE();
  // Acquire/lock this mutex for read operations, which require only a shared
  // lock. This assumes a multiple-reader, single writer semantics. Multiple
  // threads may acquire the mutex simultaneously as readers, but a writer
  // must wait for all of them to release the mutex before it can acquire it
  // exclusively.
  void ReaderLock() ACQUIRE_SHARED();
  // Release/unlock an exclusive mutex.
  void Unlock() RELEASE();
  // Release/unlock a shared mutex.
  void ReaderUnlock() RELEASE_SHARED();
  // Generic unlock, can unlock exclusive and shared mutexes.
  void GenericUnlock() RELEASE_GENERIC();
  // Try to acquire the mutex. Returns true on success, and false on failure.
  bool TryLock() TRY_ACQUIRE(true);
  // Try to acquire the mutex for read operations.
  bool ReaderTryLock() TRY_ACQUIRE_SHARED(true);
  // Assert that this mutex is currently held by the calling thread.
  void AssertHeld() ASSERT_CAPABILITY(this);
  // Assert that is mutex is currently held for read operations.
  void AssertReaderHeld() ASSERT_SHARED_CAPABILITY(this);
  // For negative capabilities.
  const Mutex &operator!() const { return *this; }
};

} // namespace tsa
