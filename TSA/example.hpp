#include "mutex_locker.hpp"

namespace tsa_example {

class BankAccount {
private:
  tsa::Mutex mu;
  int balance GUARDED_BY(mu);

  void depositImpl(int amount);

  void withdrawImpl(int amount);

public:
  void withdraw(int amount);

  void transferFrom(BankAccount &b, int amount);
};

} // namespace tsa_example
