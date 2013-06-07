//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/operator/functions/unaligned_store.hpp>
#include <boost/simd/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/iterator.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_, (A0)(A1)(A2)
                            , (unspecified_<A0>)
                              (iterator_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::unaligned_store_, tag::cpu_
                                    , (A0)(A1)
                                    , (unspecified_<A0>)
                                      (iterator_< unspecified_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return *a1 = a0;
    }
  };

  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                                   , (A0)(A1)(A2)
                                   , (fusion_sequence_<A0>)
                                     (fusion_sequence_<A1>)
                                     (scalar_< integer_<A2> >)
                                   )
  {
    typedef A0 result_type;

    inline result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::tag::unaligned_store_
                                       , A0
                                       , A1
                                       , A2
                                       >(a0, a1, a2)
                      );
      return a0;
    }
  };

  /// Handles unaligned_store( seq, seq'*)
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::unaligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (fusion_sequence_<A0>)
                                      (iterator_< fusion_sequence_<A1> >)
                                    )
  {
    typedef void result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      meta::iterate<N>( details::extractor<A0,A1>(a0,a1) );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::unaligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (iterator_< fusion_sequence_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      meta::iterate<N>( details::extractor<A0,A1,A2>(a0,a1,a2) );
    }
  };
} } }

#endif