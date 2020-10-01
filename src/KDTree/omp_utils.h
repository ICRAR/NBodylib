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

}

#endif // OMP_UTILS_H