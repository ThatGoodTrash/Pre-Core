/**
 * A header file with min macro definitions.
 * @file minmacro.h
 */

#ifndef _MINMACRO_H_
#define _MINMACRO_H_

#ifdef min
#undef min
#endif

#define min(a, b) (a < b ? a : b)

#endif
