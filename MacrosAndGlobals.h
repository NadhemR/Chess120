/*	File: MacrosAndGlobals.h
 *	Purpose:	Define all macros used in the program
				Define all external global variables
 */

#ifndef MCRGLB_H
#define MCRGLB_H

#include "Definitions.h"

	/* MACROS */
// Board conversions
#define FR2VRT(f,r) ((21 + (f)) + ((r) * 10))	// Converts file and rank to virtual board index
#define CHS2VRT(pos) (CHS64ToVRT120[(pos)])		// Convert chess index to virtual index
#define VRT2CHS(pos) (VRT120ToCHS64[(pos)])		// Convert virtual index to chess index
#define VRT2F(pos) (VRT120ToFILE[(pos)])		// Convert virtual index to file position
#define VRT2R(pos) (VRT120ToRANK[(pos)])		// Convert virtual index to rank position

// Bit board operations
#define POP(bb) PopBit((&bb))					// Pops least significant bit (see BitBoards.c for details)
#define CNT(bb) CountBits(bb)					// Counts number of set bits
#define CLRBIT(bb,sq64) ((bb) &= ClearMask[(sq64)])	// Clears bit at index
#define SETBIT(bb,sq64) ((bb) |= SetMask[(sq64)])	// Sets bit at index

// Hash Key generation
#define RAND_64	((UNS64)rand() | \
				((UNS64)rand() << 15) | \
				((UNS64)rand() << 30) | \
				((UNS64)rand() << 45) | \
				(((UNS64)rand() & 0xf) << 60))	// Generate random 64 bit hash-key

// Piece type tracking
#define BIG(piece) PieceBIG[(piece)]		// Large piece flag
#define MJR(piece) PieceMJR[(piece)]		// Major piece flag
#define MNR(piece) PieceMNR[(piece)]		// Minor piece flag
#define VAL(piece) PieceVAL[(piece)]		// Piece value
#define COLOR(piece) PieceCOL[(piece)]		// Piece color

	/* GLOBALS */
// Board conversions
extern int VRT120ToCHS64[VRTBRD_SZ];		// VRT to CHS conversion array
extern int CHS64ToVRT120[CHSBRD_SZ];		// CHS to VRT conversion array
extern int VRT120ToFILE[VRTBRD_SZ];			// VRT to File conversion array
extern int VRT120ToRANK[VRTBRD_SZ];			// VRT to Rank conversion array

// Bit board operations
extern UNS64 SetMask[CHSBRD_SZ];			// Index specific bit setting array
extern UNS64 ClearMask[CHSBRD_SZ];			// Index specific bit clearing array

// Hash Key generation
extern UNS64 PieceKeys[PIECES_NUM + 1][VRTBRD_SZ];	// Hash Key for 13 pieces over 120 squares
extern UNS64 SideKey;				// Hash Key for side to play
extern UNS64 CastleKeys[16];		// Hash Keys for the 16 possible castle conditions

// Board referencing (See Data.c)
extern char PieceChar[];			// Character string for pieces ex. PieceChar[wPAWN] = P
extern char SideChar[];				// Character string for side to play
extern char RankChar[];				// Character string for rank
extern char FileChar[];				// Character string for file

// Piece type tracking
extern int PieceBIG[PIECES_NUM + 1];	// Array of large piece flags ex. PieceBig[wPAWN] = FALSE
extern int PieceMJR[PIECES_NUM + 1];	// Array of major piece flags
extern int PieceMNR[PIECES_NUM + 1];	// Array of minor piece flags
extern int PieceVAL[PIECES_NUM + 1];	// Array of piece values
extern int PieceCOL[PIECES_NUM + 1];	// Array of piece colors

#endif // !MCRGLB_H