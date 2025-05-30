//===-- include/flang/Runtime/transformational.h ----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Defines the API for the type-independent transformational intrinsic functions
// that rearrange data in arrays: CSHIFT, EOSHIFT, PACK, RESHAPE, SPREAD,
// TRANSPOSE, and UNPACK.
// These are naive allocating implementations; optimized forms that manipulate
// pointer descriptors or that supply functional views of arrays remain to
// be defined and may instead be part of lowering (see docs/ArrayComposition.md)
// for details).

#ifndef FORTRAN_RUNTIME_TRANSFORMATIONAL_H_
#define FORTRAN_RUNTIME_TRANSFORMATIONAL_H_

#include "flang/Common/float128.h"
#include "flang/Runtime/cpp-type.h"
#include "flang/Runtime/entry-names.h"
#include <cinttypes>

namespace Fortran::runtime {

class Descriptor;

extern "C" {

void RTDECL(Reshape)(Descriptor &result, const Descriptor &source,
    const Descriptor &shape, const Descriptor *pad = nullptr,
    const Descriptor *order = nullptr, const char *sourceFile = nullptr,
    int line = 0);

void RTDECL(BesselJn_2)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn2, float bn2_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJn_3)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn2, float bn2_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJn_4)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn2, float bn2_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJn_8)(Descriptor &result, int32_t n1, int32_t n2, double x,
    double bn2, double bn2_1, const char *sourceFile = nullptr, int line = 0);

#if HAS_FLOAT80
void RTDECL(BesselJn_10)(Descriptor &result, int32_t n1, int32_t n2,
    CppTypeFor<TypeCategory::Real, 10> x,
    CppTypeFor<TypeCategory::Real, 10> bn2,
    CppTypeFor<TypeCategory::Real, 10> bn2_1, const char *sourceFile = nullptr,
    int line = 0);
#endif

#if HAS_LDBL128 || HAS_FLOAT128
void RTDECL(BesselJn_16)(Descriptor &result, int32_t n1, int32_t n2,
    CppFloat128Type x, CppFloat128Type bn2, CppFloat128Type bn2_1,
    const char *sourceFile = nullptr, int line = 0);
#endif

void RTDECL(BesselJnX0_2)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJnX0_3)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJnX0_4)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselJnX0_8)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

#if HAS_FLOAT80
void RTDECL(BesselJnX0_10)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);
#endif

#if HAS_LDBL128 || HAS_FLOAT128
void RTDECL(BesselJnX0_16)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);
#endif

void RTDECL(BesselYn_2)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn1, float bn1_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYn_3)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn1, float bn1_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYn_4)(Descriptor &result, int32_t n1, int32_t n2, float x,
    float bn1, float bn1_1, const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYn_8)(Descriptor &result, int32_t n1, int32_t n2, double x,
    double bn1, double bn1_1, const char *sourceFile = nullptr, int line = 0);

#if HAS_FLOAT80
void RTDECL(BesselYn_10)(Descriptor &result, int32_t n1, int32_t n2,
    CppTypeFor<TypeCategory::Real, 10> x,
    CppTypeFor<TypeCategory::Real, 10> bn1,
    CppTypeFor<TypeCategory::Real, 10> bn1_1, const char *sourceFile = nullptr,
    int line = 0);
#endif

#if HAS_LDBL128 || HAS_FLOAT128
void RTDECL(BesselYn_16)(Descriptor &result, int32_t n1, int32_t n2,
    CppFloat128Type x, CppFloat128Type bn1, CppFloat128Type bn1_1,
    const char *sourceFile = nullptr, int line = 0);
#endif

void RTDECL(BesselYnX0_2)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYnX0_3)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYnX0_4)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(BesselYnX0_8)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);

#if HAS_FLOAT80
void RTDECL(BesselYnX0_10)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);
#endif

#if HAS_LDBL128 || HAS_FLOAT128
void RTDECL(BesselYnX0_16)(Descriptor &result, int32_t n1, int32_t n2,
    const char *sourceFile = nullptr, int line = 0);
#endif

void RTDECL(Cshift)(Descriptor &result, const Descriptor &source,
    const Descriptor &shift, int dim = 1, const char *sourceFile = nullptr,
    int line = 0);
void RTDECL(CshiftVector)(Descriptor &result, const Descriptor &source,
    std::int64_t shift, const char *sourceFile = nullptr, int line = 0);

void RTDECL(Eoshift)(Descriptor &result, const Descriptor &source,
    const Descriptor &shift, const Descriptor *boundary = nullptr, int dim = 1,
    const char *sourceFile = nullptr, int line = 0);
void RTDECL(EoshiftVector)(Descriptor &result, const Descriptor &source,
    std::int64_t shift, const Descriptor *boundary = nullptr,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(Pack)(Descriptor &result, const Descriptor &source,
    const Descriptor &mask, const Descriptor *vector = nullptr,
    const char *sourceFile = nullptr, int line = 0);

/// Produce a shallow copy of the \p source in \p result.
/// The \p source may have any type and rank.
/// Unless \p source is unallocated, the \p result will
/// be allocated using the same shape and dynamic type,
/// and will contain the same top-level values as the \p source.
/// The \p result will have the default lower bounds, if it is an array.
/// As the name suggests, it is different from the Assign runtime,
/// because it does not perform recursive assign actions
/// for the components of the derived types.
void RTDECL(ShallowCopy)(Descriptor &result, const Descriptor &source,
    const char *sourceFile = nullptr, int line = 0);

/// Same as ShallowCopy, where the caller provides a pre-allocated
/// \p result. The \p source and \p result must be conforming:
///   * Same rank.
///   * Same extents.
///   * Same size and type of elements (including the type parameters).
/// If \p result is an array, its lower bounds are not affected.
void RTDECL(ShallowCopyDirect)(const Descriptor &result,
    const Descriptor &source, const char *sourceFile = nullptr, int line = 0);

void RTDECL(Spread)(Descriptor &result, const Descriptor &source, int dim,
    std::int64_t ncopies, const char *sourceFile = nullptr, int line = 0);

void RTDECL(Transpose)(Descriptor &result, const Descriptor &matrix,
    const char *sourceFile = nullptr, int line = 0);

void RTDECL(Unpack)(Descriptor &result, const Descriptor &vector,
    const Descriptor &mask, const Descriptor &field,
    const char *sourceFile = nullptr, int line = 0);

} // extern "C"
} // namespace Fortran::runtime
#endif // FORTRAN_RUNTIME_TRANSFORMATIONAL_H_
