//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_input_iterator.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/memory/dynarray.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <vector>

NT2_TEST_CASE_TPL(types, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::aligned_input_iterator;
  using boost::simd::pack;

  NT2_TEST_TYPE_IS( typename iterator_traits< aligned_input_iterator<T*> >::value_type
                  , (pack<T>)
                  );
}

NT2_TEST_CASE_TPL(distance, BOOST_SIMD_TYPES)
{
  using boost::simd::aligned_input_iterator;
  using boost::simd::aligned_input_begin;
  using boost::simd::aligned_input_end;
  using boost::simd::allocator;
  using boost::simd::pack;

  std::vector<T, allocator<T> > data(pack<T>::static_size*3);

  typedef typename std::vector<T, allocator<T> >::iterator it_t;

  aligned_input_iterator<it_t> b = aligned_input_begin(data.begin());
  aligned_input_iterator<it_t> e = aligned_input_end(data.end());

  NT2_TEST_EQUAL( std::distance(b,e), 3);
}

NT2_TEST_CASE_TPL(aligned_constraint, BOOST_SIMD_TYPES)
{
  using boost::simd::aligned_input_iterator;
  using boost::simd::aligned_input_begin;
  using boost::simd::aligned_input_end;
  using boost::simd::allocator;
  using boost::simd::pack;

  std::vector<T, allocator<T> > data(pack<T>::static_size*3);

  typedef typename std::vector<T, allocator<T> >::iterator it_t;

  NT2_TEST_ASSERT( aligned_input_begin(data.begin()+1) );
  NT2_TEST_ASSERT( aligned_input_end(data.end()-1)     );
}

NT2_TEST_CASE_TPL(iteration, BOOST_SIMD_TYPES)
{
  using boost::simd::aligned_input_iterator;
  using boost::simd::aligned_input_begin;
  using boost::simd::aligned_input_end;
  using boost::simd::allocator;
  using boost::simd::dynarray;
  using boost::simd::pack;
  using boost::simd::splat;

  dynarray< pack<T> >           ref(3);
  std::vector<T, allocator<T> > data(pack<T>::static_size*3);

  typedef typename std::vector<T, allocator<T> >::iterator it_t;

  for(std::size_t i=0;i<data.size();i++)
    data[i] = i/pack<T>::static_size+1;

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = splat< pack<T> >(i+1);

  aligned_input_iterator<it_t> b = aligned_input_begin(data.begin());

  NT2_TEST_EQUAL( *b++, ref[0] );
  NT2_TEST_EQUAL( *b++, ref[1] );
  NT2_TEST_EQUAL( *b++, ref[2] );
}
