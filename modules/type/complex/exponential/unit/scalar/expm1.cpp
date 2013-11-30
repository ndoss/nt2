//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/expm1.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL ( expm1_real,  NT2_REAL_TYPES)
{
  using nt2::expm1;
  using nt2::tag::expm1_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<expm1_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
    NT2_TEST_ULP_EQUAL(expm1(nt2::Inf<cT>()), cT(nt2::Inf<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Minf<cT>()), cT(nt2::Mone<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Nan<cT>()), cT(nt2::Nan<T>()), 1.0);
#endif
    NT2_TEST_ULP_EQUAL(expm1(nt2::Mone<cT>()), cT(nt2::One<T>()/nt2::Exp_1<T>()-nt2::One<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::One<cT>()), cT(nt2::Exp_1<T>()-nt2::One<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Zero<cT>()), cT(nt2::Zero<T>()), 1.0);
}
