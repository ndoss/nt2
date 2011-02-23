//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - exp2/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
/// modified by jt the 23/02/2011
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/toolbox/exponential/include/exp2.hpp>
// specific includes for arity 1 tests
#include <nt2/include/functions/exp2.hpp>
#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/abs.hpp>
extern "C" { long double cephes_exp2l(long double); }

NT2_TEST_CASE_TPL ( exp2_real__1,  NT2_REAL_TYPES)
{
  using nt2::exp2;
  using nt2::tag::exp2_;
  #include <nt2/include/functions/sqr.hpp>
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<exp2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(exp2(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Minf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Mone<T>()), nt2::Half<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::One<T>()), nt2::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    #include <nt2/include/functions/sqr.hpp>
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::exp2(a0),cephes_exp2l(a0),0.5);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::exp2(a0)),r_t(a0),3);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::sqr(a0)),2*log2(nt2::abs(a0)),3);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for real_

NT2_TEST_CASE_TPL ( exp2_unsigned_int__1,  NT2_UNSIGNED_TYPES)
{
  using nt2::exp2;
  using nt2::tag::exp2_;
  #include <nt2/include/functions/sqr.hpp>
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<exp2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(exp2(nt2::One<T>()), nt2::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    #include <nt2/include/functions/sqr.hpp>
    NT2_CREATE_BUF(tab_a0,T, NR, 0, 10);
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::exp2(a0),cephes_exp2l(a0),0.5);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::exp2(a0)),r_t(a0),3);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::sqr(a0)),2*log2(nt2::abs(a0)),3);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( exp2_signed_int__1,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::exp2;
  using nt2::tag::exp2_;
  #include <nt2/include/functions/sqr.hpp>
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<exp2_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;


  // specific values tests
  NT2_TEST_ULP_EQUAL(exp2(nt2::Mone<T>()), nt2::Half<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::One<T>()), nt2::Two<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(exp2(nt2::Zero<T>()), nt2::One<r_t>(), 0);
  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    #include <nt2/include/functions/sqr.hpp>
    NT2_CREATE_BUF(tab_a0,T, NR, -10, 10);
    double ulp0 = 0.0, ulpd = 0.0;
    T a0;
    for (int j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        NT2_TEST_ULP_EQUAL( nt2::exp2(a0),cephes_exp2l(a0),0.5);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::exp2(a0)),r_t(a0),3);
        ulp0=nt2::max(ulpd,ulp0);
        NT2_TEST_ULP_EQUAL( nt2::log2(nt2::sqr(a0)),2*log2(nt2::abs(a0)),3);
        ulp0=nt2::max(ulpd,ulp0);
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for signed_int_