#include "example.hpp"

#include <cassert>
#include <cstdlib>
#include <thread>

int main() {

  tsa_example::BankAccount account{};
  std::thread t0([&]() {
    std::size_t ctr = 0;
    while (ctr++ < 100) {
      account.deposit(1000);
    }
  });
  std::thread t1([&]() {
    std::size_t ctr = 0;
    while (ctr++ < 100) {
      account.withdraw(1000);
    }
  });
  t0.join();
  t1.join();
  assert(0 == account.balance());
  exit(EXIT_SUCCESS);
}
