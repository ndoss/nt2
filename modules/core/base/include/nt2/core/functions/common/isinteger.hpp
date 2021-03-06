//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISINTEGER_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISINTEGER_HPP_INCLUDED

#include <nt2/core/functions/isinteger.hpp>
#include <nt2/core/container/dsl/forward.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinteger_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const
    {
      typedef typename A0::value_type value_type;
      return isinteger(value_type());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinteger_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> > )
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const
    {
      return false;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isinteger_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> > )
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const
    {
      return true;
    }
  };

} }

#endif
