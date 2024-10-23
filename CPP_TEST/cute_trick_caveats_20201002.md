Caveats to Cute C++ Trick of the Day for 2020-10-02 
===================================================

TL;DR
------

Be very careful about using this if you care about performance, and there are aspects of this trick that appear to touch some fragile parts of the compilers, so proceed with caution.

Helpful links
-------------

* [Original tweet](https://twitter.com/The_Whole_Daisy/status/1312084355691421696?s=20)
* [Godbolt for original code snippet](https://godbolt.org/z/T187hP)

Original Code Snippet
---------------------

```c++
#include <utility> // std::forward
template <class Lambda>
struct recursive_lambda : Lambda {
  template <class... Args>
  auto operator()(Args&&... args) {
    return this->Lambda::operator()(*this,
      std::forward<Args>(args)...);
  }
};
template <class Lambda>
recursive_lambda(Lambda) -> recursive_lambda<Lambda>;
int test() {
  auto fibonacci = recursive_lambda{
    [](auto& self, int n) -> int {
      if(n < 2) { return n; }
      else { return self(n-1) + self(n-2); }
    }
  };
  return fibonacci(10);
}
```

Performance Caveat
------------------

First, as always, if you actually care, benchmark and measure. Don't take my word for it.

I was disappointed to find that none of the major compilers could inline this and compile `test()` into essentially `return 55`, whereas for an earlier version of this trick that I had (that's a little uglier), GCC at least figures it out: <https://godbolt.org/z/jE8zaP>. (Interestingly, it does so for the lambda version even though it can't for the normal function version, at least with just vanilla `-O3`).  All of this is basically to say if you care, be careful, since this appears to be an area of added complexity that can trip up optimizers. Also, if you care about performance, you may want to try to find a way to express your algorithm without recursion anyway.

Compiler Differences with Return Type Deduction
-----------------------------------------------

Notice that in line 14 of the original example, I'm specifying the return type of the lambda explicitly. This is because if you don't, the compiler can't deduce the return type because it gets used during deduction. Interestingly, though, an [earlier version of this](https://godbolt.org/z/o9hW6P) where I give the return type in the definition of `recursive_lambda::operator()` using a `declval` expression that's basically just the body of the function, clang is somehow able to compile it (but the other two major compilers still can't). I'm not sure what's conforming here (please let me know if you can figure it out—probably meaning if your name is Richard Smith), but this is at the very least an indication that we're bumping up against boundaries of the language that aren't uniformly supported by compilers.  In production environments especially, proceed with caution.

A Minor Note on Perfect Forwarding and Compilation Times
--------------------------------------------------------

This snippet includes only one header, `<utility>`, and only for the purposes of perfect forwarding. If you really care about compilation times, you can (and should) do the perfect forwarding with a C-style cast. In this example, `recursive_lambda::operator()` would become:

```c++
  template <class... Args>
  auto operator()(Args&&... args) {
    return this->Lambda::operator()(*this, (Args&&)args...);
  }
```

This potentially saves on a bunch of template instantiations of `std::forward`. That said, if you _really_, _really_ care about compilation times, you should be careful about cute tricks in general. As always, if you really care, benchmark and measure; don't take my word for it.

Private Inheritance
-------------------

For safety and sanity in a real-world use of this, you should probably use private inheritance to avoid having the base type call operator participate in overload resolution: <https://godbolt.org/z/WEc9hh>. I omitted this for brevity, but this also means that you can no longer treat `recursive_lambda` as an aggregate, so you need an explicit constructor. The class template definition becomes:

```c++
template <class Lambda>
struct recursive_lambda : private Lambda {
  constexpr explicit recursive_lambda(Lambda l)
    : Lambda(std::move(l)) { }
  template <class... Args>
  auto operator()(Args&&... args) {
    return this->Lambda::operator()(*this,
      std::forward<Args>(args)...);
  }
};
```

This does mean, though, that you no longer need the deduction guide.

One More Minor Note
-------------------

The `this->` in `recursive_lambda::operator()` isn't strictly necessary, but I like it for readability. Most people see `Lambda::` and have to go through several other posibilities before they think "base class member function". Always think about the reader's experience when you write code; code is written for humans, not computers.

...and a personal note
----------------------

This one took me a few tries to figure out. I set this as a challenge to myself sometime yesterday, and it wasn't until this morning when I was thinking about a different trick that I thought of this solution. C++ is hard, even for so-called "experts." But also, this felt like a reminder that C++ has an aspect to it where you get out of it (in terms of code quality and readability) what you put into it. Writing high-quality C++ is a challenge and takes time, but it pays off, and readers of your code will thank you.
