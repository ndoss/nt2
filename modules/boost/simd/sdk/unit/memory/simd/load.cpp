//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_arithmetic.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"

#define NT2_TEST_LOAD(r, data, elem) BOOST_PP_CAT(nt2_test_run_, data)<T, elem>::call();
#define NT2_TEST_APPLY(r, data, elem) data<elem>

template<class T, class U>
struct nt2_test_run_load
{
  static void call(bool offset = false)
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::logical;
    using boost::simd::native;
    using boost::simd::pack;

    typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

    load_runner< U          , native<T,ext_t>           >(offset);
    load_runner< logical<U> , native<logical<T>,ext_t>  >(offset);
    load_runner< U          , pack<T>                   >(offset);
  }
};

NT2_TEST_CASE_TPL( load,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load, BOOST_SIMD_TYPES)
}

template<class T, class U>
struct nt2_test_run_load_offset
{
  static void call() { nt2_test_run_load<T,U>::call(true); }
};

NT2_TEST_CASE_TPL( load_offset,  BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_offset, BOOST_SIMD_TYPES)
}

template<class T, class U, std::size_t N>
struct nt2_test_run_load_gather
{
  static void call()
  {
    std::cout << "With U = " << nt2::type_id<U>() << std::endl;
    using boost::simd::load;
    using boost::simd::tag::load_;
    using boost::simd::native;
    using boost::simd::meta::cardinal_of;
    typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

    typedef native<T,ext_t>                                       vT;
    typedef typename boost::dispatch::meta::
            make_integer< N, unsigned>::type                      iT;

    typedef typename boost::simd::meta
                          ::vector_of<iT,cardinal_of<vT>::value>::type viT;
    typedef typename
            boost::dispatch::
            meta::call<load_(U*,viT,boost::dispatch::meta::as_<vT>)>::type r_t;

    srand(time(NULL));

    NT2_TEST( (boost::is_same<vT,r_t>::value) );

    U data[ cardinal_of<vT>::value*3 ];
    for(size_t i=0;i<cardinal_of<vT>::value*3;++i)
      data[i] = i%2 ? U(1+i) : -U(1+i);

    viT index;
    for(size_t i=0;i<cardinal_of<viT>::value;++i)
      index[i] = rand() % (cardinal_of<vT>::value*3);

    r_t v = boost::simd::load<vT>(&data[0], index);

    for(size_t j=0;j<cardinal_of<vT>::value;++j)
    {
      NT2_TEST_EQUAL(v[j] , static_cast<T>(data[index[j]]));
    }
  }
};

template<class T, class U>
struct nt2_test_run_load_gather32 : nt2_test_run_load_gather<T,U,4>
{};

template<class T, class U>
struct nt2_test_run_load_gather64 : nt2_test_run_load_gather<T,U,8>
{};

NT2_TEST_CASE_TPL( load_gather32, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather32, BOOST_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather32_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather32
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}

NT2_TEST_CASE_TPL( load_gather64, BOOST_SIMD_SIMD_TYPES)
{
  BOOST_PP_SEQ_FOR_EACH(NT2_TEST_LOAD, load_gather64, BOOST_SIMD_SIMD_TYPES)
}

NT2_TEST_CASE_TPL ( load_gather64_logical
                  , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                          , boost::simd::logical
                                          , BOOST_SIMD_SIMD_TYPES
                                          )
                  )
{
  BOOST_PP_SEQ_FOR_EACH ( NT2_TEST_LOAD
                        , load_gather64
                        , BOOST_PP_SEQ_TRANSFORM( NT2_TEST_APPLY
                                                , boost::simd::logical
                                                , BOOST_SIMD_TYPES
                                                )
                        )
}

NT2_TEST_CASE( load_sequence )
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  load_runner< foo, native<foo,ext_t> >();
  load_runner< foo, native<foo,ext_t> >(true);
}

NT2_TEST_CASE( load_sequence_of_pointers )
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::int16_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<foo, ext_t> seq_t;
  static const size_t sz = cardinal_of< seq_t >::value;

  char     cdata[ sz ];
  float    fdata[ sz ];
  int16_t  ddata[ sz ];

  for(size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    ddata[i] = int16_t(1+i);
  }

  seq_t v = load<seq_t>(boost::fusion::make_vector(&ddata[0], &fdata[0], &cdata[0]), 0);

  for(size_t i=0;i<sz;++i)
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[i] , ddata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[i] , fdata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[i] , cdata[i]);
  }
}

NT2_TEST_CASE(tuple_native_isomorphism)
{
  using boost::fusion::vector;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::uint8_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  X;

  typedef vector<uint8_t, uint8_t, uint8_t> pixel;
  typedef vector<native<float,X>, native<float,X>, native<float,X> > simd_pixel;
  typedef native< vector<float,float,float> ,X> simd_pixel2;

  pixel data[simd_pixel2::static_size];

  for(int i=0;i<simd_pixel2::static_size;++i) data[i]= pixel(65+i,i+66,i+67);

  simd_pixel rgb = load<simd_pixel>(&data[0]);
  simd_pixel2 rgb2 = load<simd_pixel2>(&data[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(rgb),boost::fusion::at_c<0>(rgb2));
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(rgb),boost::fusion::at_c<1>(rgb2));
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(rgb),boost::fusion::at_c<2>(rgb2));
}
