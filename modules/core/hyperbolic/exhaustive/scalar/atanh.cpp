//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>

#include <nt2/sdk/unit/exhaustive.hpp>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

#include <cmath>
#include <cstdlib>

struct raw_atanh
{
  float operator()(float x) const
  {
    return nt2::atanh(double(x));
  }
};

int main(int argc, char* argv[])
{
  float mini = nt2::Mone<float>();
  float maxi = nt2::One<float>();
  if(argc >= 2) mini = std::atof(argv[1]);
  if(argc >= 3) maxi = std::atof(argv[2]);
  nt2::exhaustive_test<float> ( mini
                              , maxi
                              , nt2::functor<nt2::tag::atanh_>()
                              , raw_atanh()
                              );

  return 0;
}
