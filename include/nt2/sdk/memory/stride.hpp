/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_STRIDE_HPP_INCLUDED
#define NT2_SDK_MEMORY_STRIDE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Padding strategies and related functors
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/padding.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

////////////////////////////////////////////////////////////////////////////////
// Functor tags
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  struct stride_  {};

  //////////////////////////////////////////////////////////////////////////////
  // We only compute stride on a Fusion Sequence
  //////////////////////////////////////////////////////////////////////////////
  template<class Category, class Info>
  struct  validate< stride_, Category, Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
      : boost::fusion::traits::is_sequence<typename meta::strip<A0>::type>
    {};
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // stride_ category is given by the fact the sequence is correct
  //////////////////////////////////////////////////////////////////////////////
  template<class Info, class A0,class A1,class A2>
  struct  categorize<functors::stride_,Info,A0,A1,A2>
        : boost::mpl::if_<  boost::fusion::traits
                            ::is_sequence<typename meta::strip<A0>::type>
                          , tag::fusion_(typename meta::strip<A1>::type)
                          , tag::unknown
                          >
        {};
} }

namespace nt2
{
  template<int N, class S,class P> inline
  typename  nt2::meta
          ::enable_call < functors::stride_ ( S const&
                                            , P const&
                                            , boost::mpl::long_<N> const&
                                            )
                        >::type
  stride(S const& s, P const& p)
  {
    functors::functor<functors::stride_> callee;
    return callee(s,p,boost::mpl::long_<N>());
  }
}

#endif
