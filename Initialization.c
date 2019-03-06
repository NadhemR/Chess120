#include "Definitions.h"
#include "MacrosAndGlobals.h"

// Define board variables
int VRT120ToCHS64[VRTBRD_SZ];		// Array to convert from the virtual board to the chess board
int CHS64ToVRT120[CHSBRD_SZ];		// Array to convert from the chess board to the virtual board	

// Define bit manipulation variables
UNS64 SetMask[CHSBRD_SZ];
UNS64 ClearMask[CHSBRD_SZ];

// ..
void InitBitMasks() {
	int index;
	
	// Initializa all to zero
	for (index = 0; index < CHSBRD_SZ; index++) {
		SetMask[index] = 0ULL;
		ClearMask[index] = 0ULL;
	}

	for (index = 0; index < CHSBRD_SZ; index++) {
		SetMask[index] = (1ULL << index);	// Set mask
		ClearMask[index] = ~SetMask[index];	// Complement
	}
}

// Initializes Global variables used for board convertions
void InitializeBoardConversion() {

	int index, file, rank;
	int square120 = A1;
	int square64 = 0;

	// Setting all 120 to 64 conversion array values to the out of bound 65 as fail safe
	for (index = 0; index < VRTBRD_SZ; index++)
		VRT120ToCHS64[index] = 65;

	// Hmmm this one is actually unecessary right???
	// **********************************************
	// Setting all 64 to 120 conversion array values to the out of bound 120 as fail safe
	for (index = 0; index < CHSBRD_SZ; index++)
		CHS64ToVRT120[index] = 120;

	// Setting up all in bound conversions by cycling through ranks and files
	for (rank = RANK_1; rank <= RANK_8; rank++) {
		for (file = FILE_A; file <= FILE_H; file++) {
			square120 = FR2VRT(file, rank);
			CHS64ToVRT120[square64] = square120;
			VRT120ToCHS64[square120] = square64;
			square64++;
		}
	}

	return;
}

void AllInitialize() {

	InitializeBoardConversion();
	InitBitMasks();

	return;
}