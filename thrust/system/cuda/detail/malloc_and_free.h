/*
 *  Copyright 2008-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/system/cuda/detail/tag.h>
#include <thrust/detail/type_traits/pointer_traits.h>
#include <thrust/system/cuda/detail/guarded_cuda_runtime_api.h>
#include <thrust/system/system_error.h>
#include <thrust/system/cuda_error.h>
#include <thrust/system/detail/bad_alloc.h>

namespace thrust
{
namespace system
{
namespace cuda
{
namespace detail
{


// note that malloc returns a raw pointer to avoid
// depending on the heavyweight thrust/system/cuda/memory.h header
inline void *malloc(tag, std::size_t n)
{
  void *result = 0;

  cudaError_t error = cudaMalloc(reinterpret_cast<void**>(&result), n);

  if(error)
  {
    throw thrust::system::detail::bad_alloc(thrust::system::cuda_category().message(error).c_str());
  } // end if

  return result;
} // end malloc()


template<typename Pointer>
inline void free(tag, Pointer ptr)
{
  cudaError_t error = cudaFree(thrust::detail::raw_pointer_cast(ptr));

  if(error)
  {
    throw thrust::system_error(error, thrust::cuda_category());
  } // end error
} // end free()


} // end detail
} // end cuda
} // end system
} // end thrust

