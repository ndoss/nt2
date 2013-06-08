//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/if_else_allbits.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/is_not_greater.hpp>
#include <nt2/include/functions/simd/bitwise_andnot.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/split.hpp>
#include <nt2/include/functions/simd/group.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/include/constants/_180.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/is_upgradable.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace details { namespace internal
{
  // This class exposes the public static member:
  // reduce:                to provide range reduction
  //
  // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
  // meaning that the cosa function will (for example) define respectively
  // x-->cos(x)          (radian_tag),
  // x-->cos(pi*x)       (pi_tag)
  // x-->cos((pi/180)*x) (degree_tag)
  //

  // trigonometric reduction strategies to the [-pi/4, pi/4] range.
  // these reductions are used in the accurate and fast
  // trigonometric functions with different policies

  template<class A0, class mode>
  struct trig_reduction < A0, radian_tag,  tag::simd_type, mode, float>
  {
    typedef typename meta::as_logical<A0>::type              bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;

    typedef typename boost::simd::meta::is_upgradable_on_ext<A0>::type conversion_allowed;
    static inline bA0 is_0_pio4_reduced(const A0&a0) { return boost::simd::is_ngt(a0, Pio_4<A0>()); }
    static inline bA0 is_0_mpi_reduced (const A0&a0) { return boost::simd::is_ngt(a0,single_constant<A0,0x43490fdb>()); }
    static inline bA0 is_0_20pi_reduced(const A0&a0) { return boost::simd::is_ngt(a0,single_constant<A0,0x427b53d1>()); }
    static inline bA0 is_0_pio2_reduced(const A0&a0) { return boost::simd::is_ngt(a0,Pio_2<A0>()); }
    static inline bA0 is_0_dmpi_reduced(const A0&a0) { return boost::simd::is_ngt(a0,single_constant<A0,0x49490fdb>()); }  //2^18pp

    static inline bA0 cot_invalid(const A0&) { return nt2::False<bA0>(); }
    static inline bA0 tan_invalid(const A0&) { return nt2::False<bA0>(); }
    static inline int_type reduce(const A0& x, A0& xr){ return inner_reduce(x, xr); }
  private:
    static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr)
    {
      // x is always positive here
      A0 xx = x_n;
      if (mode::clipped)
      {
        if (mode::range == r_0_pio4)      xx = if_else_nan(is_0_pio4_reduced(xx), xx);
        else if (mode::range == r_0_20pi) xx = if_else_nan(is_0_20pi_reduced(xx), xx);
        else if (mode::range == r_0_mpi)  xx = if_else_nan(is_0_mpi_reduced(xx),  xx);
        else if (mode::range == r_0_dmpi) xx = if_else_nan(is_0_dmpi_reduced(xx), xx);
      }
     switch (mode::start)
      {
      case  r_0_pio4 :
        if(nt2::all(is_0_pio4_reduced(xx)) || mode::range == r_0_pio4)
        {
          xr = xx; return Zero<int_type>();
        }
      case r_0_pio2 :
        if(nt2::all(is_0_pio2_reduced(xx)))
        {
          return rem_pio2_straight(xx, xr);
        }
      case  r_0_20pi :
        if(nt2::all(is_0_20pi_reduced(xx)) || mode::range == r_0_20pi)
        {
          return rem_pio2_cephes(xx, xr);
        }
      case  r_0_mpi :
        if(nt2::all(is_0_mpi_reduced(xx)) || mode::range == r_0_mpi)
        {
          return rem_pio2_medium(xx, xr);
        }
      case  r_0_dmpi :
        if(nt2::all(is_0_dmpi_reduced(xx)) || mode::range == r_0_dmpi)
        {
          return inner_reduce_big(xx, xr, conversion_allowed());
        }
      case  r_0_inf :
        return inner_reduce_big(xx, xr, conversion_allowed());
      }
    }

    static inline int_type inner_reduce_big(const A0& x, A0& xr, boost::mpl::true_)
    {
      // all of x are in [0, 2^18*pi],  conversion to double is used to reduce
      typedef typename meta::upgrade<A0>::type uA0;
      typedef typename meta::upgrade<int_type>::type uint_type;
      typedef trig_reduction< uA0, radian_tag,  tag::simd_type, mode, double> aux_reduction;
      uA0 ux1, ux2, uxr1, uxr2;
      nt2::split(x, ux1, ux2);
      uint_type n1 = aux_reduction::reduce(ux1, uxr1);
      uint_type n2 = aux_reduction::reduce(ux2, uxr2);
      xr = nt2::group(uxr1, uxr2);
      nt2::split(xr, ux1, ux2);
      return nt2::group(n1, n2);
    }

    static inline int_type inner_reduce_big(const A0& x, A0& xr, boost::mpl::false_)
    {
      // all of x are in [0, inf],  standard big_ way
      return nt2::rem_pio2(x, xr);
    }

  };


  template<class A0>
  struct trig_reduction<A0,degree_tag, tag::simd_type,big_, float>
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;
    typedef typename meta::as_logical<A0>::type              bA0;

    static inline bA0 cot_invalid(const A0& x) { return nt2::logical_and(nt2::is_nez(x), nt2::is_flint(x/_180<A0>())); }
    static inline bA0 tan_invalid(const A0& x) { return nt2::is_flint((x-nt2::_90<A0>())/nt2::_180<A0>()); }

    static inline int_type reduce(const typename A0::native_type x_n, A0& xr)
    {
      const A0 x = x_n;
      A0 xi = nt2::round2even(x*single_constant<A0,0x3c360b61>()); //  1.111111111111111e-02f
      A0 x2 = x - xi * nt2::_90<A0>();//90.0f
      xr =  x2*single_constant<A0,0x3c8efa35>(); //0.0174532925199432957692f
      return nt2::toint(xi);
    }
  };

  // TODO put a medium_ case with a fast_round2even ?
  template < class A0>
  struct trig_reduction < A0, pi_tag,  tag::simd_type, big_, float>
  {
    typedef typename meta::as_integer<A0, signed>::type int_type;
    typedef typename meta::as_logical<A0>::type              bA0;

    static inline bA0 cot_invalid(const A0& x) { return nt2::logical_and(nt2::is_nez(x), nt2::is_flint(x)); }
    static inline bA0 tan_invalid(const A0& x) { return nt2::is_flint(x-nt2::Half<A0>()) ; }

    static inline int_type reduce(const typename A0::native_type x_n,  A0& xr)
    {
      const A0 x = x_n;
      A0 xi = nt2::round2even(x*nt2::Two<A0>());
      A0 x2 = x - xi * nt2::Half<A0>();
      xr = x2*nt2::Pi<A0>();
      return nt2::toint(xi);
    }
  };
}
}
}

#endif

