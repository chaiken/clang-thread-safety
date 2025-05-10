# removed  -Werror
override CXXFLAGS = -Werror -std=c++17 -ggdb -Wall -Wextra -g -O0
CXXFLAGS_CHECK= -c  -Wthread-safety $(CXXFLAGS)
override LDFLAGS+= -ggdb -g
# gcc and clang won't automatically link .cc files against the standard library.
CXX=/usr/bin/clang++

EXAMPLE_LIBS = thread_safety.hpp mutex.hpp mutex.cpp mutex_locker.hpp example.hpp example.cpp

tsa: $(EXAMPLE_LIBS)
	$(CXX) $(CXXFLAGS_CHECK) $(LDFLAGS) $^

bank_account: $(EXAMPLE_LIBS) bank_account.cpp
	$(CXX) $(CXXFLAGS) -fsanitize=thread $(LDFLAGS) mutex.cpp example.cpp bank_account.cpp -o $@

clean:
	/bin/rm -f *.o *~ *.pch a.out
