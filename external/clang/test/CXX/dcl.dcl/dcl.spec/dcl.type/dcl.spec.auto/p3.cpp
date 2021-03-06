// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++11
// RUN: %clang_cc1 -fsyntax-only -verify %s -std=c++98 -Wno-c++11-extensions
void f() {
  auto a = a; // expected-error{{variable 'a' declared with 'auto' type cannot appear in its own initializer}}
  auto *b = b; // expected-error{{variable 'b' declared with 'auto' type cannot appear in its own initializer}}
  const auto c = c; // expected-error{{variable 'c' declared with 'auto' type cannot appear in its own initializer}}
  if (auto d = d) {} // expected-error {{variable 'd' declared with 'auto' type cannot appear in its own initializer}}
  auto e = ({ auto f = e; 0; }); // expected-error {{variable 'e' declared with 'auto' type cannot appear in its own initializer}}
}

void g() {
  auto a; // expected-error{{declaration of variable 'a' with type 'auto' requires an initializer}}
  
  auto *b; // expected-error{{declaration of variable 'b' with type 'auto *' requires an initializer}}

  if (auto b) {} // expected-error {{expected '='}}
  for (;auto b;) {} // expected-error {{expected '='}}
  while (auto b) {} // expected-error {{expected '='}}
  if (auto b = true) { (void)b; }
}

auto n(1,2,3); // expected-error{{initializer for variable 'n' with type 'auto' contains multiple expressions}}

namespace N
{
  auto a = "const char [16]", *p = &a;
}

void h() {
  auto b = 42ULL;

  for (auto c = 0; c < b; ++c) {
  }
}

template<typename T, typename U> struct same;
template<typename T> struct same<T, T> {};

void p3example() {
  auto x = 5;
  const auto *v = &x, u = 6;
  static auto y = 0.0;
  // In C++98: 'auto' storage class specifier is redundant and incompatible with C++0x
  // In C++0x: 'auto' storage class specifier is not permitted in C++0x, and will not be supported in future releases
  auto int r; // expected-warning {{'auto' storage class specifier}}

  same<__typeof(x), int> xHasTypeInt;
  same<__typeof(v), const int*> vHasTypeConstIntPtr;
  same<__typeof(u), const int> uHasTypeConstInt;
  same<__typeof(y), double> yHasTypeDouble;
}
