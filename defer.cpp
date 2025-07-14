#include "defer/defer.hpp"

#include <cstdio>

void nothing() { printf("Hello world\n"); }

void something() {
  int a = 0;
  defer_inline(a = 1; printf("A is %d\n", a););
  defer([=] { printf("Should be called first\n"); });
  auto defer_test = deferred(&nothing);
}
