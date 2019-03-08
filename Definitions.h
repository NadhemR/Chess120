/*	File: Definitions.h
 *	Purpose:	Include the necessary standard library headers
				Define the various constant names used
				Define a shorthand name for a 64bit unsigned number
				Define structures for the chess board and for game history tracking
 */

#ifndef DEFS_H
#define DEFS_H

	/* NECESSARY HEADERS */
#include <stdio.h>
#include <stdlib.h>
#include "Assert.h"

	/* GENERAL CONSTANT DEFINITIONS */
#define GAMENAME "Chess120"			// Name of program
#define VRTBRD_SZ 120				// Size of virtual board (VRT)
#define CHSBRD_SZ 64				// Size of chess board (CHS)
#define MAXGAMEMOVES 2048			// Maximum number of moves for the game
#define PIECES_NUM 12				// Number of unique pieces
#define COLORS_NUM 2				// Number of unique colors
enum { FALSE, TRUE };				// Boolean conditions

// Start FEN code for regular chess game (see FEN on wiki for details)
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

	/* BOARD & PIECE INDEXING CONSTANT DEFINITIONS */
enum {WHITE, BLACK, BOTH};			// Piece Color

enum {EMPTY, wPAWN, wROOK, wKNIGHT,
		wBISHOP, wQUEEN, wKING,
		bPAWN, bROOK, bKNIGHT,
		bBISHOP, bQUEEN, bKING};	// Chess pieces

enum {FILE_A, FILE_B, FILE_C,
		FILE_D, FILE_E, FILE_F,
		FILE_G, FILE_H, FILE_NONE};	// Vertical board files

enum {RANK_1, RANK_2, RANK_3,
		RANK_4, RANK_5, RANK_6,
		RANK_7, RANK_8, RANK_NONE};	// Horizantal board ranks

// King Castling Permission flags using 4 bit sequance
	// ex. Black King-side castling refers to third bit 0100
enum {wKING_CA = 1, wQUEEN_CA = 2, bKING_CA = 4, bQUEEN_CA = 8};

// Chess board position indices in reference to virtual board
	// VRT board is 10x12 enumerated left to right, top to bottom (ranging 0 to 119)
	// CHS board is centre 8x8 section of VRT
enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8,
	OFFBRD
};

	/* TYPE DEFINITIONS */
typedef unsigned long long UNS64;	// Unsigned 64 bit int

// Structure to record previous move
typedef struct {

	int move;				// Holds previous move
	int castlePerms;		// Holds castle permissions
	int enPassant;			// Holds En Passant condition
	int fiftyMove;			// Holds Fifty Move condition
	UNS64 posKey;			// Holds previous position key

} UNDO_STRUCT;

// Structure with all board information
typedef struct {

		// Track pieces
	int pieces[VRTBRD_SZ];				// Piece loaction on the VRT ex. pieces[A2] = bPAWN
	int pieceNum[PIECES_NUM + 1];		// Number of unique pieces on BRD (+1 accounts for EMPTY index)
	int bigPieceNum[COLORS_NUM];		// Number of non-pawns on BRD by color
	int mjrPieceNum[COLORS_NUM];		// Number of Rooks, Queens, and Kings by color
	int mnrPieceNum[COLORS_NUM];		// Number of Knights and Bishops by color
	int kingPos[COLORS_NUM];			// Position of Kings
	UNS64 pawns[COLORS_NUM+1];			// Each bit represents a board square (0 to 63) from the 8x8 CHS board
	int pieceList[PIECES_NUM + 1][10];	// Track piece positions, up to 10 pieces ex. pieceList[wKNIGHT][0] = E1

		// Track play and history
	int material[COLORS_NUM];			// Material value for both sides
	int side;							// Current side to play
	int ply;							// Number of half-moves for search
	int histPly;						// Total number of half-moves played
	UNDO_STRUCT history[MAXGAMEMOVES];	// Struct array to hold game history
	UNS64 posKey;						// Position key unique to current layout

		// Track rules
	int castlePerms;					// Castling conditions using 4 bit sequence code
	int enPassant;						// En Passant square
	int fiftyMove;						// Fifty Move rule counter

} BOARD_STRUCT;


#endif