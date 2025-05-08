#include "example.hpp"

#include <iostream>

namespace tsa_example {

void BankAccount::depositImpl(const std::size_t amount) { balance_ += amount; }

void BankAccount::withdrawImpl(const std::size_t amount) { balance_ -= amount; }

bool BankAccount::withdraw(const std::size_t amount) {
  tsa::MutexLocker ml(&mu_);
  if (amount <= balance_) {
    withdrawImpl(amount);
    return true;
  }
  std::cerr << "Requested withdrawal " << amount << " exceeds balance "
            << balance_ << std::endl;
  return false;
}

void BankAccount::deposit(const std::size_t amount) {
  tsa::MutexLocker ml(&mu_);
  depositImpl(amount);
}

void BankAccount::transferFrom(BankAccount &b, const std::size_t amount) {
  b.withdraw(amount);
  deposit(amount);
}

} // namespace tsa_example
