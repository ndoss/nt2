//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_DIGAMMA_HPP_INCLUDED

#include <nt2/euler/functions/digamma.hpp>
#include <nt2/euler/functions/details/digamma_kernel.hpp>
#include <nt2/include/constants/digammalargelim.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/ifnotadd.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_lez.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/tanpi.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::digamma_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 result = nt2::Zero<A0>();
      A0 x = a0;
      bA0 test = nt2::is_lez(a0);
      std::size_t nb;
      if( (nb = nt2::inbtrue(test)) > 0)
      {
        x = nt2::if_else(test, nt2::oneminus(a0), a0);
        A0 remainder = x - nt2::floor(x);
        remainder =  nt2::selsub(nt2::gt(remainder,Half<A0>()),remainder,nt2::One<A0>());
        remainder = nt2::if_zero_else(nt2::is_eqz(remainder), nt2::Pi<A0>()/nt2::tanpi(remainder));
        result = nt2::if_else_zero(test, remainder);
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      A0 r1 = nt2::Zero<A0>();
      test = nt2::gt(x, Digammalargelim<A0>());
      nb = nt2::inbtrue(test);
      if(nb)
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        r1 = seladd(test, result, details::digamma_kernel<A0>::digamma_imp_large(x));
        if (nb >= (uint32_t)meta::cardinal_of<A0>::value) return r1;
      }
      // If x > 2 reduce to the interval [1,2]:
      bA0 cond = nt2::gt(x, nt2::Two<A0>());
      while(nt2::any(cond))
      {
        x =  selsub(cond, x, nt2::One<A0>());
        result = seladd(cond, result,  nt2::rec(x));
        cond = nt2::gt(x, nt2::Two<A0>());
      }
      // If x < 1 use shift to > 1:
      cond = nt2::lt(x, nt2::One<A0>());
      if(nt2::any(cond))
      {
        result = if_else(cond,  -nt2::rec(x), result);
        x =  seladd(cond, x, nt2::One<A0>());
      }
      A0 r2 = ifnotadd(test, result, details::digamma_kernel<A0>::digamma_1_2(x));
      return nt2::if_else(test, r1, r2);
    }
  };
} }

#endif
