//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_MHALF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_MHALF_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/constant/register.hpp>
#include <boost/simd/constant/hierarchy.hpp>


namespace boost { namespace simd
{
  namespace tag
  {
   /*!
     @brief Mhalf generic tag

     Represents the Mhalf constant in generic contexts.

     @par Models:
        Hierarchy
   **/
    BOOST_SIMD_CONSTANT_REGISTER( Mhalf, double, 0
                                , 0xBF000000, 0xBFE0000000000000ULL
                                );
  }
  /*!
    Generates value -\f$\frac12\f$

    @par Semantic:

    @code
    T r = Mhalf<T>();
    @endcode

    is similar to:

    @code
    T r = -T(1)/T(2);
    @endcode
  **/
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mhalf, Mhalf)
} }

#include <boost/simd/constant/common.hpp>

#endif
