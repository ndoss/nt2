//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLPE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLPE_HPP_INCLUDED
#include <nt2/elliptic/functions/ellpe.hpp>
#include <boost/math/special_functions.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/sdk/error/policies.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/eps.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION_GEN( nt2::tag::ellpe_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::ellpe(result_type(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_GEN( nt2::tag::ellpe_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type type;
      if (a0>nt2::One<A0>()||(nt2::is_ltz(a0))) return nt2::Nan<type>();
      if (nt2::is_eqz(a0))  return nt2::One<type>();
      if (a0 == nt2::One<A0>()) return nt2::Pio_2<type>();
      return boost::math::ellint_2(nt2::sqrt(nt2::oneminus(type(a0))), nt2_policy());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_GEN( nt2::tag::ellpe_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (a0>nt2::One<A0>()||(is_ltz(a0))) return nt2::Nan<A0>();
      if (nt2::is_eqz(a0))  return nt2::One<A0>();
      if (a0 == nt2::One<A0>()) return nt2::Pio_2<A0>();
      A0 tmp1 = nt2::horner< NT2_HORNER_COEFF(float, 11,
                              (0x392102f5,
                               0x3b246c1b,
                               0x3c0e578f,
                               0x3c2fe240,
                               0x3bfebca9,
                               0x3bf882cf,
                               0x3c3d8b3f,
                               0x3cb2d89a,
                               0x3d68ac90,
                               0x3ee2e430,
                               0x3f800000) ) > (a0);
      A0 tmp2 = nt2::horner< NT2_HORNER_COEFF(float, 10,
                                    (0x38098de4,
                                     0x3a84557e,
                                     0x3bd53114,
                                     0x3c8a54f6,
                                     0x3cd67118,
                                     0x3d0925e1,
                                     0x3d2ef92b,
                                     0x3d6fffe9,
                                     0x3dc00000,
                                     0x3e800000
                                     ) ) > (a0);
      return tmp1-nt2::log(a0)*a0*tmp2;
    }
  };
} }


#endif
