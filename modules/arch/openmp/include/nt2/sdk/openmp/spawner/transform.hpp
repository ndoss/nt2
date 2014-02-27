//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_SPAWNER_TRANSFORM_HPP_INCLUDED
#define NT2_SDK_OPENMP_SPAWNER_TRANSFORM_HPP_INCLUDED

#if defined(_OPENMP) && _OPENMP >= 201307 /* OpenMP 4.0 */

#include <omp.h>
#include <nt2/sdk/shared_memory/spawner.hpp>
#include <nt2/sdk/openmp/future/future.hpp>

#include <vector>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

namespace nt2
{
  namespace tag
    {
      struct transform_;
      template<class T> struct openmp_;
    }

  template<class Site>
  struct spawner< tag::transform_, tag::openmp_<Site> >
  {

    spawner() {}

    template<typename Worker>
    void operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain)
    {

      typedef typename tag::openmp_<Site> Arch;

// #ifndef BOOST_NO_EXCEPTIONS
//       boost::exception_ptr exception;
// #endif
//      std::size_t leftover = size % grain;
//      std::size_t nblocks  = size/grain;
//      #pragma omp parallel
//      {
//        // Dispatch group of blocks over each threads
//        #pragma omp for schedule(static)
//        for(std::size_t n=0;n<nblocks;++n)
//        {
// #ifndef BOOST_NO_EXCEPTIONS
//          try
//          {
// #endif
//            std::size_t chunk = (n<nblocks-1) ? grain : grain+leftover;
//            // Call operation
//            w(begin+n*grain,chunk);
// #ifndef BOOST_NO_EXCEPTIONS
//          }
//          catch(...)
//          {
//            #pragma omp critical
//            exception = boost::current_exception();
//          }
// #endif
//        }
//     }

        typedef typename
        nt2::make_future< Arch,int >::type future;

        std::size_t nblocks  = size/grain;
        std::size_t ibound   = nblocks * grain;
        std::size_t leftover = size % grain;

#ifndef BOOST_NO_EXCEPTIONS
        boost::exception_ptr exception;

        try
        {
#endif
            #pragma omp parallel
            #pragma omp single
            {
                std::vector< future > barrier;
                barrier.reserve(nblocks+1);

                for(std::size_t n=0;n<nblocks;++n)
                {
                    std::size_t chunk = (n<nblocks-1) ? grain : grain+leftover;
                    // Call operation
                    barrier.push_back ( async<Arch>(w, begin+n*grain, chunk) );
                }

                for(std::size_t n=0;n<nblocks;++n)
                {
                    // Call operation
                    barrier[n].get();
                }
            }

#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
            exception = boost::current_exception();
        }
#endif
      }
   };
}

#endif
#endif
