//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sinh.hpp>
#include <nt2/exponential/constants.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mzero.hpp>

NT2_TEST_CASE_TPL ( sinh_real__1_0, NT2_SIMD_REAL_TYPES)
{

  using nt2::sinh;
  using nt2::tag::sinh_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                cT;
  typedef native<T,ext_t>                vT;
  typedef native<cT,ext_t>              cvT;
  typedef typename nt2::meta::call<sinh_(cvT)>::type r_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::One<cvT>()  ),              nt2::splat<cvT>(nt2::sinh(nt2::One<cT>()))  , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::Zero<cvT>() ),              nt2::splat<cvT>(nt2::sinh(nt2::Zero<cT>())) , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::Mzero<cvT>()),              nt2::splat<cvT>(nt2::sinh(nt2::Mzero<cT>())), 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::splat<cvT>(cT(0.5, -0.5))), nt2::splat<cvT>(nt2::sinh(cT(0.5, -0.5)))   , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::splat<cvT>(cT(1, 1))),      nt2::splat<cvT>(nt2::sinh(cT(1, 1)))        , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::splat<cvT>(cT(1, 10))),     nt2::splat<cvT>(nt2::sinh(cT(1, 10)))       , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::splat<cvT>(cT(10, 10))),    nt2::splat<cvT>(nt2::sinh(cT(10, 10)))      , 1.0);
  NT2_TEST_ULP_EQUAL(nt2::sinh(nt2::splat<cvT>(cT(10, 1))),     nt2::splat<cvT>(nt2::sinh(cT(10, 1)))       , 1.0);
} // end of test for floating_

