#include "mutex.hpp"

class BankAccount {
private:
  Mutex mu;
  int balance GUARDED_BY(mu);

  void depositImpl(int amount);

  void withdrawImpl(int amount);

public:
  void withdraw(int amount);

  void transferFrom(BankAccount &b, int amount);
};
