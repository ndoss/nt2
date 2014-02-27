//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_HPX_SPAWNER_TRANSFORM_HPP_INCLUDED
#define NT2_SDK_HPX_SPAWNER_TRANSFORM_HPP_INCLUDED

#if defined(NT2_USE_HPX)

#include <nt2/sdk/shared_memory.hpp>
#include <nt2/sdk/shared_memory/spawner.hpp>
#include <nt2/sdk/hpx/settings/specific_data.hpp>
#include <nt2/sdk/shared_memory/details/aggregate_futures.hpp>

#include <nt2/sdk/hpx/future/future.hpp>
#include <nt2/sdk/hpx/future/when_all.hpp>
#include <hpx/lcos/wait_all.hpp>

#include <nt2/sdk/shared_memory/details/then_worker.hpp>
#include <nt2/sdk/shared_memory/details/proto_data_with_futures.hpp>
#include <nt2/sdk/shared_memory/settings/container_has_futures.hpp>

#include <vector>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif


namespace nt2
{
    namespace tag
    {
        struct transform_;
    }

    template<class Site>
    struct spawner< tag::transform_, tag::hpx_<Site> >
    {

        spawner() {}

        template<typename Worker>
        void operator()(Worker & w, std::size_t begin, std::size_t size, std::size_t grain_out)
        {
            typedef typename tag::hpx_<Site> Arch;

             typedef typename
             nt2::make_future< Arch ,int >::type future;

            std::size_t nblocks  = size/grain_out;
            std::size_t leftover = size % grain_out;
            std::size_t grain_in;

            details::container_has_futures<Arch> &
              out_specifics( boost::proto::value(w.out_).specifics() );

            details::container_has_futures<Arch> tmp;

            tmp.grain_ = grain_out;
            tmp.futures_.reserve(nblocks);

            details::aggregate_futures aggregate_f;

            #ifndef BOOST_NO_EXCEPTIONS
            boost::exception_ptr exception;

            try
            {
            #endif


            for(std::size_t n=0;n<nblocks;++n)
            {
                std::size_t chunk = (n<nblocks-1) ? grain_out : grain_out+leftover;

                details::proto_data_with_futures<future
                  ,details::container_has_futures<Arch>
                > data_in(n*grain_out,chunk,out_specifics);

                aggregate_f(w.in_,0,data_in);

                if(data_in.futures_.empty())
                {
                    // Call operation
                    tmp.futures_.push_back (
                      async<Arch>(Worker(w), begin+n*grain_out, chunk)
                    );
                }

                else
                {
                    // Call operation
                    tmp.futures_.push_back(
                      hpx::when_all(boost::move(data_in.futures_))
                        .then(details::then_worker<Worker>
                           (Worker(w),begin+n*grain_out, chunk)
                         )
                    );
                }
            }

            out_specifics.swap(tmp);

            #ifndef BOOST_NO_EXCEPTIONS
            }
            catch(...)
            {
                exception = boost::current_exception();
            }
            #endif


     //      typedef typename
     //      nt2::make_future< Arch,int >::type future;

     //      std::size_t leftover = size % grain_out;
     //      std::size_t nblocks  = size/grain_out;

     //      std::vector< future > barrier;
     //      barrier.reserve(nblocks);

     //      #ifndef BOOST_NO_EXCEPTIONS
     //      boost::exception_ptr exception;

     //      try
     //      {
     //      #endif

     //      for(std::size_t n=0;n<nblocks;++n)
     //      {
     //        std::size_t chunk = (n<nblocks-1) ? grain_out : grain_out+leftover;
     //        // Call operation
     //        barrier.push_back ( async<Arch>(w, begin+n*grain_out, chunk) );
     //      }

     //      for(std::size_t n=0;n<nblocks;++n)
     //      {
     //          // Call operation
     //          barrier[n].get();
     //      }

     //      // hpx::wait_all(barrier);

     //      #ifndef BOOST_NO_EXCEPTIONS
     //      }
     //      catch(...)
     //      {
     //          exception = boost::current_exception();
     //      }
     //      #endif

        }
    };
}

#endif
#endif
