/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_META_MAKE_ALIGNED_HPP_INCLUDED
#define NT2_SDK_MEMORY_META_MAKE_ALIGNED_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/config/bootstrap.hpp>

////////////////////////////////////////////////////////////////////////////////
// Intrinsic platform dependant alignment attribute
////////////////////////////////////////////////////////////////////////////////
#if (defined(BOOST_MSVC))
#define NT2_ALIGN_ON(x)  __declspec(align(x))
#elif (defined(__GNUC__))
#define NT2_ALIGN_ON(x)  __attribute__(( __aligned__((x)) ))
#else
#error nt2::aligned - No Supported alignment attribute
#endif

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Qualify a type with the proper alignement attribute
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct make_aligned
  {
    typedef T NT2_ALIGN_ON(NT2_CONFIG_ALIGNMENT) type;
  };
} }

#undef M0
#undef M1
#undef M2

#endif
