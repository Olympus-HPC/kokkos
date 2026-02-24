#include <Kokkos_Macros.hpp>
#if defined(KOKKOS_ENABLE_JIT)
#include "proteus/JitInterface.hpp"
#endif

#ifndef KOKKOS_JIT_HPP
#define KOKKOS_JIT_HPP

namespace Kokkos
{
namespace internal
{
namespace jit
{

template<typename Lambda>
inline void register_lambda(const Lambda& lambda)
{
#if defined KOKKOS_ENABLE_JIT
  proteus::register_lambda(lambda);
#endif
}

template<typename T>
inline auto jit_variable(T arg)
{
#if defined KOKKOS_ENABLE_JIT
  return proteus::jit_variable(std::forward<T>(arg));
#else
  return std::forward<T>(arg);
#endif
}


#if defined KOKKOS_ENABLE_JIT
// This macro accepts a list of integers as its arguments, corresponding to the
// 1-indexed arguments for which to specialize a function's IR.
#define KOKKOS_JIT_COMPILE_ARGS(...) __attribute__((annotate("jit", __VA_ARGS__)))
#define KOKKOS_JIT_COMPILE           __attribute__((annotate("jit")))
#else
// When JIT is not enabled, simply pass through.
#define KOKKOS_JIT_COMPILE_ARGS(...)
#define KOKKOS_JIT_COMPILE
#endif

}  // namespace jit
}  // namespace internal
}  // namespace RAJA

#endif
