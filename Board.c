/*	File: Board.c
 *	Purpose:	Board setup
	Functions:	ResetBoard -> Resets the board structure to default values
				ParseFEN -> Parses the FEN code string and sets board structure accordingly
				PrintBoard -> Prints chess board to the command window
 */

#include "Definitions.h"
#include "MacrosAndGlobals.h"
#include "Functions.h"

void ResetBoard(BOARD_STRUCT *brd) {
	
	int index;

	// Set whole grid to OFFBRD
	for (index = 0; index < VRTBRD_SZ; index++)
		brd->pieces[index] = OFFBRD;

	// Set CHS grid to EMPTY
	for (index = 0; index < CHSBRD_SZ; index++)
		brd->pieces[CHS2VRT(index)] = EMPTY;
	
	// Set pieceNum to 0
	for (index = 0; index <= PIECES_NUM; index++)
		brd->pieceNum[index] = 0;

	// Set piece counters to 0
	for (index = 0; index < COLORS_NUM; index++) {
		brd->bigPieceNum[index] = 0;
		brd->mjrPieceNum[index] = 0;
		brd->mnrPieceNum[index] = 0;
		brd->material[index] = 0;		// ****** I added this line
	}

	// ***** Make sure i actually do need three and not just 2 like above
	for (index = 0; index < COLORS_NUM + 1; index++)
		brd->pawns[index] = 0ULL;

	// Set king positions to OFFBRD
	brd->kingPos[WHITE] = OFFBRD;
	brd->kingPos[BLACK] = OFFBRD;

	// Set default game start conditions
	brd->side = BOTH;
	brd->ply = 0;
	brd->histPly = 0;

	// Set default game rule counters
	brd->enPassant = OFFBRD;
	brd->fiftyMove = 0;
	brd->castlePerms = 0;

	// Zero the position key
	brd->posKey = 0ULL;

	// *************** I should add smth for pieceList setting to 0 initially

	return;
}

int ParseFEN(char *fen, BOARD_STRUCT *brd) {

	// Pointer error checking
	ASSERT(fen != NULL);
	ASSERT(brd != NULL);

	int count, index;
	int rank = RANK_8;
	int file = FILE_A;
	int piece = EMPTY;

	// Reset board before setting-up
	ResetBoard(brd);
	
	// Cycle through board layout characters
	for (; (rank >= RANK_1) && *fen; fen++) {
		count = 1;		// Insures file always incremented by at least 1

		// Parse string for board layout
		switch (*fen) {
			case 'p':	piece = bPAWN; break;
			case 'r':	piece = bROOK; break;
			case 'n':	piece = bKNIGHT; break;
			case 'b':	piece = bBISHOP; break;
			case 'k':	piece = bKING; break;
			case 'q':	piece = bQUEEN; break;
			case 'P':	piece = wPAWN; break;
			case 'R':	piece = wROOK; break;
			case 'N':	piece = wKNIGHT; break;
			case 'B':	piece = wBISHOP; break;
			case 'K':	piece = wKING; break;
			case 'Q':	piece = wQUEEN; break;

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				piece = EMPTY;
				count = *fen - '0';		// Convert to int and store
				break;

			case '/':
			case ' ':
				rank--;
				file = FILE_A;
				fen++;
				continue;
			
			default:
				printf("FEN error \n");
				return -1;
		}

		// Update board accordingly
		for (index = 0; index < count; index++) {			
			
			if (piece != EMPTY)
				brd->pieces[FR2VRT(file, rank)] = piece;	// Update piece location

			file++;		// Increment file according to spaces (always at least 1)
		}
	}

	// Set the side to move
	ASSERT(*fen == 'w' || *fen == 'b');
	brd->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;	// Skip space and move to next flag

	// Set castle permissions
	for (index = 0; index < 4; index++, fen++) {
		if (*fen == ' ')
			break;

		switch (*fen) {
			case 'K':	brd->castlePerms |= wKING_CA; break;
			case 'Q':	brd->castlePerms |= wQUEEN_CA; break;
			case 'k':	brd->castlePerms |= bKING_CA; break;
			case 'q':	brd->castlePerms |= bQUEEN_CA; break;
			default: break;
		}
	}
		// Check if within bounds
	ASSERT(brd->castlePerms >= 0 && brd->castlePerms <= 15);

	// Set En Passant square
	fen++;
	if (*fen != '-') {
		file = fen[0] - 'a';	// Convert file letter to an int
		rank = fen[1] - '1';	// Convert rank number to an int

		// Check if within bounds
		ASSERT(file >= FILE_A && file <= FILE_H);
		ASSERT(rank >= RANK_1 && rank <= RANK_8);

		brd->enPassant = FR2VRT(file, rank);
	}

	// Generate the Hash Key
	brd->posKey = GeneratePosKey(brd);

	return 0;
}

void PrintBoard(const BOARD_STRUCT *brd) {

	int sq120, file, rank, piece;
	printf("\n Game Board:\n\n");

	// Print ranks and pieces
	for (rank = RANK_8; rank >= RANK_1; rank--) {
		printf(" %-2c", RankChar[rank]);
		
		for (file = FILE_A; file <= FILE_H; file++) {
			sq120 = FR2VRT(file, rank);
			piece = brd->pieces[sq120];
			printf("%3c", PieceChar[piece]);
		}

		printf("\n");
	}
	
	// Print files
	printf("\n   ");
	for (file = FILE_A; file <= FILE_H; file++)
		printf("%3c", FileChar[file]);
	
	// Print side to play
	printf("\n\n");
	printf("Side: %c\n", SideChar[brd->side]);
	printf("En Passant: %d\n", brd->enPassant);

	// Print Castle Permissions
	printf("Casstle Permission: %c%c%c%c\n",
			(brd->castlePerms & wKING_CA) ?		'K' : '-',
			(brd->castlePerms & wQUEEN_CA) ?	'Q' : '-',
			(brd->castlePerms & bKING_CA) ?		'k' : '-',
			(brd->castlePerms & bQUEEN_CA) ?	'q' : '-');

	// Print unique Hash Key
	printf("Position Key: %llX\n", brd->posKey);
	printf("\n");

	return;
}

// ************* To be reviewed and commented
void UpdatePieceCounters(BOARD_STRUCT *brd) {
	
	// ************** can get rid of sq120 and use index instead actually here
	int piece, sq120, index, color;

	for (index = 0; index < VRTBRD_SZ; index++) {
		sq120 = index;
		piece = brd->pieces[index];

		if (piece != OFFBRD && piece != EMPTY) {
			color = COLOR(piece);

			if (BIG(piece))
				brd->bigPieceNum[color]++;
			if (MJR(piece))
				brd->mjrPieceNum[color]++;
			if (MNR(piece))
				brd->mnrPieceNum[color]++;

			brd->material[color] += VAL(piece);

			brd->pieceList[piece][brd->pieceNum[piece]] = sq120;
			brd->pieceNum[piece]++;

			if (piece == wKING)
				brd->kingPos[WHITE] = sq120;
			else if (piece == bKING)
				brd->kingPos[BLACK] = sq120;

			if (piece == wPAWN) {
				SETBIT(brd->pawns[WHITE], VRT2CHS(sq120));
				SETBIT(brd->pawns[BOTH], VRT2CHS(sq120));
			} else if (piece == bPAWN) {
				SETBIT(brd->pawns[BLACK], VRT2CHS(sq120));
				SETBIT(brd->pawns[BOTH], VRT2CHS(sq120));
			}
		}
	}
	
	return;
}

// ************* To be reviewed and commented
int CheckBoard(const BOARD_STRUCT *brd) {

	int pieceNumTemp[PIECES_NUM + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int bigPieceNumTemp[COLORS_NUM] = {0, 0};
	int mjrPieceNumTemp[COLORS_NUM] = {0, 0};
	int mnrPieceNumTemp[COLORS_NUM] = {0, 0};
	int materialTemp[COLORS_NUM] = {0, 0};

	int sq64, pieceTemp, pieceNumIndex, sq120, color, bitCount;

	UNS64 pawnsTemp[COLORS_NUM + 1] = {0ULL, 0ULL, 0ULL};

	pawnsTemp[WHITE] = brd->pawns[WHITE];
	pawnsTemp[BLACK] = brd->pawns[BLACK];
	pawnsTemp[BOTH] = brd->pawns[BOTH];

	// Check pieces, pieceNum, and pieceList all match
	for (pieceTemp = wPAWN; pieceTemp <= bKING; pieceTemp++) {
		for (pieceNumIndex = 0; pieceNumIndex < brd->pieceNum[pieceTemp]; pieceNumIndex++) {
			sq120 = brd->pieceList[pieceTemp][pieceNumIndex];
			ASSERT(brd->pieces[sq120] == pieceTemp);
		}
	}

	// Check pieceNum, bigPieceNum, mjrPieceNum, mnrPieceNum, and material
	for (sq64 = 0; sq64 < CHSBRD_SZ; sq64++) {
		sq120 = CHS2VRT(sq64);
		pieceTemp = brd->pieces[sq120];
		pieceNumTemp[pieceTemp]++;
		color = COLOR(pieceTemp);

		if (BIG(pieceTemp))
			bigPieceNumTemp[color]++;
		if (MNR(pieceTemp))
			mnrPieceNumTemp[color]++;
		if (MJR(pieceTemp))
			mjrPieceNumTemp[color]++;

		materialTemp[color] += VAL(pieceTemp);
	}

	for (pieceTemp = wPAWN; pieceTemp <= bKING; pieceTemp++)
		ASSERT(pieceNumTemp[pieceTemp] == brd->pieceNum[pieceTemp]);

	ASSERT(materialTemp[WHITE] == brd->material[WHITE] &&
			materialTemp[BLACK] == brd->material[BLACK]);

	ASSERT(mnrPieceNumTemp[WHITE] == brd->mnrPieceNum[WHITE] &&
			mnrPieceNumTemp[BLACK] == brd->mnrPieceNum[BLACK]);

	ASSERT(mjrPieceNumTemp[WHITE] == brd->mjrPieceNum[WHITE] &&
			mjrPieceNumTemp[BLACK] == brd->mjrPieceNum[BLACK]);

	ASSERT(bigPieceNumTemp[WHITE] == brd->bigPieceNum[WHITE] &&
			bigPieceNumTemp[BLACK] == brd->bigPieceNum[BLACK]);

	// Check pawn bitboard counts
	bitCount = CNT(pawnsTemp[WHITE]);
	ASSERT(bitCount == brd->pieceNum[wPAWN]);
	bitCount = CNT(pawnsTemp[BLACK]);
	ASSERT(bitCount == brd->pieceNum[bPAWN]);
	bitCount = CNT(pawnsTemp[BOTH]);
	ASSERT(bitCount == (brd->pieceNum[bPAWN] + brd->pieceNum[wPAWN]));

	// Check pawn bitboards squares
	while (pawnsTemp[WHITE]) {
		sq64 = POP(pawnsTemp[WHITE]);
		ASSERT(brd->pieces[CHS2VRT(sq64)] == wPAWN);
	}

	while (pawnsTemp[BLACK]) {
		sq64 = POP(pawnsTemp[BLACK]);
		ASSERT(brd->pieces[CHS2VRT(sq64)] == bPAWN);
	}

	while (pawnsTemp[BOTH]) {
		sq64 = POP(pawnsTemp[BOTH]);
		ASSERT((brd->pieces[CHS2VRT(sq64)] == bPAWN) || (brd->pieces[CHS2VRT(sq64)] == wPAWN));
	}

	// Check side
	ASSERT(brd->side == WHITE || brd->side == BLACK);

	// Check HAsh Key
	ASSERT(GeneratePosKey(brd) == brd->posKey);

	// Check En Passant square
	ASSERT(brd->enPassant == OFFBRD || (VRT2R(brd->enPassant) == RANK_6 && brd->side == WHITE)
			|| (VRT2R(brd->enPassant) == RANK_3 && brd->side == BLACK));

	// Check King positions
	ASSERT(brd->pieces[brd->kingPos[WHITE]] == wKING);
	ASSERT(brd->pieces[brd->kingPos[BLACK]] == bKING);

	return TRUE;
}