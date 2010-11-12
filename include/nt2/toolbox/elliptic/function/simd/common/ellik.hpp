//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIK_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIK_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<ellik_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ellik(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<ellik_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (float,double,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  float)
    {
      A0 phi = nt2::abs(a0);
      A0 m = a1;
      A0 a = One<A0>();
      A0 b = oneminus(m);

      b = sqrt(b);
      A0 c = sqrt(m);
      A0 d = One<A0>();
      A0 t = tan(phi);
      A0 mod = ceil(phi/Pi<A0>());
      while( any(abs(c) > abs(a)*Eps<A0>()) )
      {
        A0 temp = b/a;
        phi = phi + atan(t*temp) + mod*Pi<A0>();
        mod = ceil(phi/Pi<A0>());
        t = oneplus(temp)/(rec(t)-temp*t);
        c = average(a,-b);
        temp = sqrt(a*b);
        a = average(a,b);
        b = temp;
        d += d;
      }
      A0 temp = (atan(t) + mod * Pi<A0>())/(d * a);
      temp = b_xor(temp, bitofsign(a0));
      return b_or(b_or(is_ltz(a1), gt(a1, One<A0>())), temp);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, double)
    {
      return map(functor<ellik_>(), a0, a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::ellik(tofloat(a0), tofloat(a1));

    }
  };
} }

      
#endif
