/*	File: HashKey.c
 *	Purpose:	Generating a unique 64 bit key from current layout and conditions
				Key generation is completed by XOR(ing) the Hash Key with random 64bit condition keys
 */

#include "Definitions.h"
#include "MacrosAndGlobals.h"

UNS64 GeneratePosKey(const BOARD_STRUCT *brd) {
	
	UNS64 finalKey = 0ULL;
	int piece = EMPTY;
	int sq120;

	// Generate from pieces
	for (sq120 = 0; sq120 < VRTBRD_SZ; sq120++) {
		piece = brd->pieces[sq120];
		if (piece != OFFBRD && piece != EMPTY) {
			ASSERT(piece >= wPAWN && piece <= bKING);	// Insure within bounds
			finalKey ^= PieceKeys[piece][sq120];
		}
	}

	// Generate from side
	if (brd->side == WHITE)
		finalKey ^= SideKey;

	// Generate from En Passant square
	if (brd->enPassant != OFFBRD) {
		ASSERT(brd->enPassant >= 0 && brd->enPassant < VRTBRD_SZ);	// Insure within bounds
		finalKey ^= PieceKeys[EMPTY][brd->enPassant];	// Using the 0 index since not used for pieces
	}

	// Generate from Castle Permissions
	ASSERT(brd->castlePerms >= 0 && brd->castlePerms <= 15);	// Insure within bounds
	finalKey ^= CastleKeys[brd->castlePerms];

	return finalKey;
}