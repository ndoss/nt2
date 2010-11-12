//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_CRLIBM_FUNCTION_COSH_RU_HPP_INCLUDED
#define NT2_TOOLBOX_CRLIBM_FUNCTION_COSH_RU_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/crlibm/include.hpp>

namespace nt2 { namespace crlibm
  {	       
    struct cosh_ru_ {};
    NT2_FUNCTION_IMPLEMENTATION(crlibm::cosh_ru_, cosh_ru, 1)
  }
}
 
#include <nt2/toolbox/crlibm/function/scalar/cosh_ru.hpp>
// #include NT2_CRLIBM_INCLUDE(cosh_ru.hpp) 

 
#endif
