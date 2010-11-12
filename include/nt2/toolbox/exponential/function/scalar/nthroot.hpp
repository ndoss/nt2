//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_NTHROOT_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_NTHROOT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/rec.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<nthroot_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::is_integral<A1>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute nthroot(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<nthroot_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typedef typename boost::result_of<meta::floating(A0)>::type type;
      if (!a1) return One<type>();
      type a1b = a1; 
      type y = signnz(a0)*nt2::pow(nt2::abs(a0),rec(a1b));
      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      if (a0) y -= (nt2::pow(y, a1b) - a0) / (a1* nt2::pow(y,minusone(a1b)));
      return y;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type; 
      return nt2::nthroot(type(a0),a1);
    }
  };
} }


      
#endif
