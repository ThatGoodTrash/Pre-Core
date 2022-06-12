/**
 * A header file with another min macro definitions.
 * @file othermacro.h
 */

#ifndef _OTHERMACRO_H_
#define _OTHERMACRO_H_

#ifdef min
#undef min
#endif

#define min(a, b) (a < b ? b : a)

#endif