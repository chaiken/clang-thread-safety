#include "mutex.hpp"

namespace tsa {

void Mutex::Lock() { mutex_.lock(); }

void Mutex::Unlock() { mutex_.unlock(); }

bool Mutex::TryLock() { return mutex_.try_lock(); }

void SharedMutex::ReaderLock() { shared_mutex_.lock_shared(); }

void SharedMutex::ReaderLock() { shared_mutex_.unlock_shared(); }

bool SharedMutex::ReaderTryLock() { return shared_mutex_.try_lock_shared(); }

} // namespace tsa
