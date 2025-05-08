#include "mutex_locker.hpp"

namespace tsa_example {

class BankAccount {
private:
  // Make the SharedMutex mutable so that const methods can modify it, but not
  // mu_ or balance_.
  mutable tsa::SharedMutex smu_;
  tsa::Mutex mu_;
  // Remove GUARDED_BY from balance_ since otherwise reading it requires a
  // writer lock.
  std::size_t balance_ = 0;

  void depositImpl(const std::size_t amount) REQUIRES(mu_);
  void withdrawImpl(const std::size_t amount) REQUIRES(mu_);

public:
  // Create a getter which takes a reader lock.
  std::size_t balance() const {
    tsa::shared_lock_t lockt;
    tsa::SharedMutexLocker sml(&smu_, lockt);
    return balance_;
  }
  // TODO: fail if amount > balance_.
  void withdraw(const std::size_t amount);
  void deposit(const std::size_t amount);
  void transferFrom(BankAccount &b, const std::size_t amount);
};

} // namespace tsa_example
