//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_AVX_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_AVX_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/biggest_integer.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

////////////////////////////////////////////////////////////////////////////////
// AVX extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<> struct is_simd_specific<__m256 , tag::avx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m256d, tag::avx_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m256i, tag::avx_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<>
  struct as_simd<float, tag::avx_>
  {
    typedef __m256 type;
  };

  template<>
  struct as_simd<double, tag::avx_>
  {
    typedef __m256d type;
  };

  template<class T>
  struct as_simd<T, tag::avx_, typename enable_if_c< is_integral<T>::value && !is_same<T, bool>::value >::type>
  {
    typedef __m256i type;
  };

  template<class T>
  struct as_simd<logical<T>, tag::avx_>
    : as_simd<T, tag::avx_>
  {
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m256 ,X>  { typedef tag::avx_ type; };
  template<class X> struct extension_of<__m256d,X>  { typedef tag::avx_ type; };
  template<class X> struct extension_of<__m256i,X>  { typedef tag::avx_ type; };
} } }

#endif
