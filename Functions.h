#ifndef FNCT_H
#define FNCT_H

#include "Definitions.h"

/* FUNCTIONS */

	// Initialization.c
extern void AllInitialize(void);

	// BitBoard.c
extern void PrintBitBoard(UNS64 bb);
extern int PopBit(UNS64 *bb);
extern int CountBits(UNS64 bb);

#endif // !FNCT_H