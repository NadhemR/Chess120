/*	File: Initialization.c
 *	Purpose:	Initialization routines
	Functions:	InitializeHashKeys -> Initialize random 64bit Keys for piece locations, side, and castle
				InitializeBitMasks -> Initialize masks for clearing and setting bits in a 64bit int
				InitializeBoardConversion -> Initialize Global variables used for board conversions
				AllInitialize -> Calls all initialization routines
 */

#include "Definitions.h"
#include "MacrosAndGlobals.h"

// Board conversion variables
int VRT120ToCHS64[VRTBRD_SZ];
int CHS64ToVRT120[CHSBRD_SZ];
int VRT120ToFILE[VRTBRD_SZ];
int VRT120ToRANK[VRTBRD_SZ];

// Bit manipulation variables
UNS64 SetMask[CHSBRD_SZ];
UNS64 ClearMask[CHSBRD_SZ];

// Key variables
UNS64 PieceKeys[PIECES_NUM+1][VRTBRD_SZ];
UNS64 SideKey;
UNS64 CastleKeys[16];

void InitializeHashKeys() {
	
	int i, j;

	// Random keys for the 13x120 piece array
	for (i = 0; i < 13; i++)
		for (j = 0; j < 120; j++)
			PieceKeys[i][j] = RAND_64;

	// Random side key
	SideKey = RAND_64;

	// Random keys for the 16 castle conditions
	for (i = 0; i < 16; i++)
		CastleKeys[i] = RAND_64;

	return;
}

void InitializeBitMasks() {
	
	int index;
	
	// ******** Is this rly necessary?
	// Initializa all masks to zero
	for (index = 0; index < CHSBRD_SZ; index++) {
		SetMask[index] = 0ULL;
		ClearMask[index] = 0ULL;
	}

	// Initialize masks according to array index
	for (index = 0; index < CHSBRD_SZ; index++) {
		SetMask[index] = (1ULL << index);		// Set mask
		ClearMask[index] = ~SetMask[index];		// Complement for clear mask
	}

	return;
}

void InitializeBoardConversion() {

	int index, file, rank;
	int sq120 = A1;
	int sq64 = 0;

	// Initializing VRT to CHS conversion arrays to the out of bound 65 as fail safe
	// Initializing VRT to File and Rank conversion arrays as out of bound
	for (index = 0; index < VRTBRD_SZ; index++) {
		VRT120ToCHS64[index] = 65;
		VRT120ToFILE[index] = FILE_NONE;
		VRT120ToRANK[index] = RANK_NONE;
	}

	// Hmmm this one is actually unecessary right???
	// **********************************************
	// Initializing CHS to VRT conversion array values to the out of bound 120 as fail safe
	for (index = 0; index < CHSBRD_SZ; index++)
		CHS64ToVRT120[index] = 120;

	// Setting up all in bound conversions
	for (rank = RANK_1; rank <= RANK_8; rank++) {
		for (file = FILE_A; file <= FILE_H; file++) {
			sq120 = FR2VRT(file, rank);

			CHS64ToVRT120[sq64] = sq120;
			VRT120ToCHS64[sq120] = sq64;

			VRT120ToFILE[sq120] = file;
			VRT120ToRANK[sq120] = rank;

			sq64++;
		}
	}

	return;
}

void AllInitialize() {

	InitializeBoardConversion();
	InitializeBitMasks();
	InitializeHashKeys();

	return;
}