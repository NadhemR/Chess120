#ifndef DEFS_H
#define DEFS_H

typedef unsigned long long UNS64;		// Defined an unsigned 64 bit int

#define GAMENAME "Chess120"				// Name of program
#define BRD_SZ 120						// Size of board array

#define MAXGAMEMOVES 2048				// Maximum number of moves for the game

// Define Boolean Conditions
enum { FALSE, TRUE };

// Enumerate all of the available chess pieces (ranging 1 to 12) and the lack of a piece (state value of 0) 
enum {EMPTY, wPAWN, wROOK, wKNIGHT, wBISHOP, wQUEEN, wKING, bPAWN, bROOK, bKNIGHT, bBISHOP, bQUEEN, bKING};

// Enumerate piece color
enum {WHITE, BLACK, BOTH};

// Enumerate the bertical chess board files (ranging A to H) and any no_file states (FILE_NONE)
// Similarely also enumerate the horizantal ranks (ranging from 1 to 8) and a no_rank state (RANK_NONE)
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};

// Enumerate the virtual board position indices (ex A-1 or C-5) and one state for out of board (OUT)
// The virtual board is a 10x12 box enumerated from left to right, top to bottom (ranging 0 to 119)
// The chess board is the centre 8x8 section of the virtual board, the rest is OUT of board for move checks
enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8,
	OUT
};

// For King castling rules on both King and Queen sides
// Enumerated refereing to a 4 bit sequence
enum {wKING_CA = 1, wQUEEN_CA = 2, bKING_CA = 4, bQUEEN_CA = 8};

// Define our board structure
typedef struct {
	// Track board
	int pieces[BRD_SZ];		// To track piece loactions on the virtual board
	UNS64 pawns[3];			// 3 array elements to represent pawns of WHITE, BLACK, and BOTH
							// Each array element is 64 bits, each bit represents a board square
							// The 8x8 board is represented by 8 sequences of 8 bits, one for each board rank

	// Track pieces
	int pieceNum[13];		// Number of pieces on the board for each piece
	int bigPieceNum[3];		// Number of non-pawn pieces on the board by color
	int majorPieceNum[3];	// Number of Rooks and Queens on the board by color
	int minorPieceNum[3];	// Number of Knights and Bishops on the board by color
	int KingPos[2];			// To record positions of White and Black Kings

	// Track play and history
	int side;				// Current side to play
	int ply;				// To store number of half-moves for search
	int histPly;			// Total number of half-moves so far

	// Track rules
	int enPassant;			// To test for En Passant rule conditions
	int fiftyMove;			// To test for Fifty Move rule conditions
	int castleConditions;	// To check Castling conditions using 4 bit sequence code

	// 
	UNS64 posKey;				// ...

} BOARD_STRUCT;

// Define move history structure
//...



#endif
