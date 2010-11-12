//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLPK_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLPK_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/is_ltz.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<ellpk_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_floating_point<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ellpk(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<ellpk_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (float,double))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  float)
    {
       A0 z =	horner< NT2_HORNER_COEFF(float, 11,
					 (0x3910af7e, 
					  0x3b15705e, 
					  0x3c02a58c, 
					  0x3c218458, 
					  0x3be146d1, 
					  0x3bcacd2e, 
					  0x3c100737, 
					  0x3c74beb4, 
					  0x3cfd02d9, 
					  0x3dc5c860, 
					  0x3fb17218
					  ) ) > (a0)
	    -log(a0)*horner< NT2_HORNER_COEFF(float, 11,
					     (0x37f6b0fa, 
					      0x3a6fa5e6, 
					      0x3bc2a939, 
					      0x3c7db504, 
					      0x3cc3dcb9, 
					      0x3cf6bf35, 
					      0x3d191914, 
					      0x3d47ffe8, 
					      0x3d900000, 
					      0x3e000000, 
					      0x3f000000
					      ) ) > (a0);
         return select(is_nez(a0), b_or(b_or(is_ltz(a0),
			  gt(a0, One<A0>())), z), Inf<A0>());
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, double)
    {
      A0 z =	horner< NT2_HORNER_COEFF(double, 11,
					 (
					  0x3f2215efc8230a6dll, 
					  0x3f62ae0bc8b87afall, 
					  0x3f8054b18cadb000ll, 
					  0x3f84308b0e9b854fll, 
					  0x3f7c28da13d45e88ll, 
					  0x3f7959a5cfd45b0cll, 
					  0x3f8200e6e2fae761ll, 
					  0x3f8e97d672352414ll, 
					  0x3f9fa05b1905c419ll, 
					  0x3fb8b90bfbea387cll, 
					  0x3ff62e42fefa39efll
					  ) ) > (a0)
	    -log(a0)*horner< NT2_HORNER_COEFF(double, 11,
					     (
					      0x3efed61f30e56ff3ll, 
					      0x3f4df4bcbee9b2c2ll, 
					      0x3f7855271dd88f27ll, 
					      0x3f8fb6a073d2d3f0ll, 
					      0x3f987b9729ca99fbll, 
					      0x3f9ed7e6a0857bd9ll, 
					      0x3fa323227b179faall, 
					      0x3fa8fffcf8d1c38dll, 
					      0x3fb1fffffeb22f00ll, 
					      0x3fbfffffffffdba4ll, 
					      0x3fe0000000000000ll					      
					      ) ) > (a0);
    
        return select(is_nez(a0), b_or(b_or(is_ltz(a0),
			 gt(a0, One<A0>())), z), Inf<A0>());
    }
  };
} }

      
#endif
