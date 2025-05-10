# removed  -Werror
override CXXFLAGS+= -c -Wthread-safety -std=c++17 -ggdb -Wall -Wextra -g -O0
override LDFLAGS+= -ggdb -g
# gcc and clang won't automatically link .cc files against the standard library.
CXX=/usr/bin/clang++

tsa: thread_safety.hpp mutex.hpp mutex.cpp mutex_locker.hpp example.hpp example.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^


clean:
	/bin/rm -f *.o *~ *.pch
