/**
 * !file omp_utils.h
 * \brief OpenMP utilities
 */

#ifndef OMP_UTILS_H
#define OMP_UTILS_H

#ifdef USEOPENMP
#include <omp.h>
#endif // USEOPENMP

namespace NBody
{

#ifdef USEOPENMP
int get_available_threads()
{
	int nthreads;
	#pragma omp parallel
	#pragma omp single
	{
		nthreads = omp_get_num_threads();
	}
	return nthreads;
}
#else
int get_available_threads()
{
	return 1;
}
#endif // USEOPENMP

#ifdef USEOPENMP
/// Returns whether OpenMP nesting is enabled or not
static bool _omp_get_nested()
{
#if _OPENMP >= 200805
	return omp_get_max_active_levels() > 1;
#else
	return omp_get_nested();
#endif
}

/// Set OpenMP to enabled (or not) nested parallelism
static void _omp_set_nested(bool enable)
{
	static constexpr int MAX_OPENMP_ACTIVE_LEVELS = 20;
#if _OPENMP >= 200805
	omp_set_max_active_levels(enable ? MAX_OPENMP_ACTIVE_LEVELS : 1);
#else
	omp_set_nested(int(enable));
#endif
}
#endif // USEOPENMP

}

#endif // OMP_UTILS_H