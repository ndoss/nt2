/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_IS_ITERATOR_HPP_INCLUDED
#define NT2_SDK_META_IS_ITERATOR_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>

namespace nt2 { namespace meta
{
  template<class T, class Enable=void>
  struct  is_iterator
        : boost::mpl::false_  {};

  template<class T, class Enable>
  struct  is_iterator<T*,Enable>
        : boost::mpl::true_   {};

  template<class T, class Enable>
  struct  is_iterator<const T*,Enable>
        : boost::mpl::true_   {};

  template<class T>
  struct  is_iterator < T
                      , typename
                        enable_if_type< typename T::iterator_category >::type
                      >
        : boost::mpl::true_ {};
} }

#endif
