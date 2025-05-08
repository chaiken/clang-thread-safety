#include "example.hpp"

namespace tsa_example {

void BankAccount::depositImpl(const int amount) {
  tsa::MutexLocker ml(&mu_);
  balance_ += amount;
}

void BankAccount::withdrawImpl(const int amount) REQUIRES(mu_) {
  balance_ -= amount;
}

void BankAccount::withdraw(const int amount) {
  tsa::MutexLocker ml(&mu_);
  withdrawImpl(amount);
}

void BankAccount::transferFrom(BankAccount &b, const int amount) {
  tsa::MutexLocker mla(&mu_);
  tsa::MutexLocker mlb(&b.mu_);
  b.withdrawImpl(amount);
  depositImpl(amount);
}

} // namespace tsa_example
