#ifndef MCRGLB_H
#define MCRGLB_H

#include "Definitions.h"

/* MACROS */

	// Board onversions
#define FR2VRT(f,r) ((21 + (f)) + ((r) * 10))	// Converts chess board numbers to virtual board numbers (from file and rank)
#define CHS2VRT(pos) (CHS64ToVRT120[pos])		// Convert from chess to virtual
#define VRT2CHS(pos) (VRT120ToCHS64[pos])		// Convert from virtual to chess

	// Bit board operations
#define POP(bb) PopBit(&bb)
#define CNT(bb) CountBits(bb)
#define CLRBIT(bb,sq64) ((bb) &= ClearMask[(sq64)])
#define SETBIT(bb,sq64) ((bb) |= SetMask[(sq64)])

	/* GLOBALS */

extern int VRT120ToCHS64[VRTBRD_SZ];		// Array to convert from the virtual board to the chess board
extern int CHS64ToVRT120[CHSBRD_SZ];		// Array to convert from the chess board to the virtual board			

extern UNS64 SetMask[CHSBRD_SZ];
extern UNS64 ClearMask[CHSBRD_SZ];

#endif // !MCRGLB_H