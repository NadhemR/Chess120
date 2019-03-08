/*	File: BitBoards.c
 *	Purpose:	Bit Board manipulations
	Functions:	PopBit -> Returns the index of the least significant bit before setting it to zero (from Chess Engine Wiki)
				CountBits -> Counts the number of bits in a bit board (from Chess Engine Wiki)
				PrintBitBoard -> Prints the bit board to the command window
 */


#include "Definitions.h"
#include "MacrosAndGlobals.h"

// Const bit table for PopBit routine (from Chess Engine Wiki)
const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

int PopBit(UNS64 *bb) {

	UNS64 b = *bb ^ (*bb - 1);
	unsigned int fold = (unsigned)((b & 0xffffffff) ^ (b >> 32));
	*bb &= (*bb - 1);

	return BitTable[(fold * 0x783a9b23) >> 26];
}

int CountBits(UNS64 bb) {

	int r;
	for (r = 0; bb; r++, bb &= bb - 1);

	return r;
}

void PrintBitBoard(UNS64 bb) {

	UNS64 shiftMe = 1ULL;	// Unsigned 64 bit 1 aka. 00...001

	int rank, file;
	int sq120, sq64;

	printf("\n");

	// Cycle through ranks and files to print bit board
	for (rank = RANK_8; rank >= RANK_1; rank--) {
		for (file = FILE_A; file <= FILE_H; file++) {
			sq120 = FR2VRT(file, rank);
			sq64 = VRT2CHS(sq120);

			// Print an X on the bits that are set or - otherwise
			if ((shiftMe << sq64) & bb)
				printf("X");
			else
				printf("-");
		}

		printf("\n");
	}

	return;
}