// { dg-options "-std=gnu++1y" }

// Copyright (C) 2015 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

// 8.2.1 Class template shared_ptr [memory.smartptr.shared]


#include <experimental/memory>
#include <testsuite_hooks.h>


struct A
{
  A() { ++ctor_count; }
  virtual ~A() { ++dtor_count; }
  static long ctor_count;
  static long dtor_count;
};
long A::ctor_count = 0;
long A::dtor_count = 0;

struct B : A
{
  B() { ++ctor_count; }
  virtual ~B() { ++dtor_count; }
  static long ctor_count;
  static long dtor_count;
};
long B::ctor_count = 0;
long B::dtor_count = 0;

struct reset_count_struct
{
  ~reset_count_struct()
    {
      A::ctor_count = 0;
      A::dtor_count = 0;
      B::ctor_count = 0;
      B::dtor_count = 0;
    }
};

// C++14 §20.8.2.2.3 shared_ptr assignment

void
test01() 
{
  reset_count_struct __attribute__((unused)) reset;
  bool test __attribute__((unused)) = true;

  std::experimental::shared_ptr<A[10]> a;

  a = std::experimental::shared_ptr<A[10]> ();
  VERIFY( a.get() == 0 );
  VERIFY( A::ctor_count == 0 );
  VERIFY( A::dtor_count == 0 );
  VERIFY( B::ctor_count == 0 );
  VERIFY( B::dtor_count == 0 );

  a = std::experimental::shared_ptr<A[10]> (new A[10]);
  VERIFY( a.get() != 0 );
  VERIFY( A::ctor_count == 10 );
  VERIFY( A::dtor_count == 0 );
  VERIFY( B::ctor_count == 0 );
  VERIFY( B::dtor_count == 0 );

  a = std::experimental::shared_ptr<B[10]> (new B[10]);
  VERIFY( a.get() != 0 );
  VERIFY( A::ctor_count == 20 );
  VERIFY( A::dtor_count == 10 );
  VERIFY( B::ctor_count == 10 );
  VERIFY( B::dtor_count == 0 );
}

int
main()
{
  test01();
  return 0;
}
