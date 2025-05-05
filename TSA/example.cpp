#include "example.hpp"

namespace tsa_example {

void BankAccount::depositImpl(int amount) {
  balance += amount; // WARNING! Cannot write balance without locking mu.
}

void BankAccount::withdrawImpl(int amount) REQUIRES(mu) {
  balance -= amount; // OK. Caller must have locked mu.
}

void BankAccount::withdraw(int amount) {
  mu.Lock();
  withdrawImpl(amount); // OK.  We've locked mu.
} // WARNING!  Failed to unlock mu.

void BankAccount::transferFrom(BankAccount &b, int amount) {
  mu.Lock();
  b.withdrawImpl(
      amount); // WARNING!  Calling withdrawImpl() requires locking b.mu.
  depositImpl(amount); // OK.  depositImpl() has no requirements.
  mu.Unlock();
}

} // namespace tsa_example
