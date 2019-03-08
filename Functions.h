/*	File: Functions.h
 *	Purpose:	Define all external program functions
 */

#ifndef FNCT_H
#define FNCT_H

#include "Definitions.h"

	// From Initialization.c
extern void AllInitialize(void);

	// From BitBoard.c
extern void PrintBitBoard(UNS64 bb);
extern int PopBit(UNS64 *bb);
extern int CountBits(UNS64 bb);

	// From HashKey.c
extern UNS64 GeneratePosKey(const BOARD_STRUCT *brd);

	// From Board.c
extern void ResetBoard(BOARD_STRUCT *brd);
extern int ParseFEN(char *fen, BOARD_STRUCT *brd);
extern void PrintBoard(const BOARD_STRUCT *brd);
extern void UpdatePieceCounters(BOARD_STRUCT *brd);
extern int CheckBoard(const BOARD_STRUCT *brd);

#endif // !FNCT_H