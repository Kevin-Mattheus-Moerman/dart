/*
 * Copyright (c) 2017, Graphics Lab, Georgia Tech Research Corporation
 * Copyright (c) 2017, Personal Robotics Lab, Carnegie Mellon University
 * All rights reserved.
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_COMMON_DETAIL_CREATE_HPP_
#define DART_COMMON_DETAIL_CREATE_HPP_

#include <memory>
#include <Eigen/Core>
#include "dart/config.hpp"
#include "dart/common/Memory.hpp"

namespace dart {
namespace common {
namespace detail {

// Generic version
template <template <typename...> class Container, typename T, typename... Args>
struct CreateImpl
{
  static Container<T, Args...> run(Args&&... args)
  {
    return Container<T, Args...>(new T(std::forward<Args>(args)...));
  }
};

// Specialized for std::shared_ptr
template <typename T, typename... Args>
struct CreateImpl<std::shared_ptr, T, Args...>
{
  static std::shared_ptr<T> run(Args&&... args)
  {
    return MakeSharedImpl<T, Args...>::run(std::forward<Args>(args)...);
  }
};

// Specialized for std::unique_ptr
template <typename T, typename... Args>
struct CreateImpl<std::unique_ptr, T, Args...>
{
  static std::unique_ptr<T> run(Args&&... args)
  {
    return make_unique<T, Args...>(std::forward<Args>(args)...);
  }
};

} // namespace detail
} // namespace common
} // namespace dart

#endif // DART_COMMON_DETAIL_MEMORY_IMPL_HPP_
