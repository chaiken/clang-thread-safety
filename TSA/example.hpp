#include "mutex_locker.hpp"

namespace tsa_example {

class BankAccount {
private:
  tsa::Mutex mu_;
  std::size_t balance_ GUARDED_BY(mu_);

  void depositImpl(const std::size_t amount) REQUIRES(mu_);
  void withdrawImpl(const std::size_t amount) REQUIRES(mu_);

public:
  void withdraw(const std::size_t amount);
  void deposit(const std::size_t amount);
  void transferFrom(BankAccount &b, const std::size_t amount);
};

} // namespace tsa_example
