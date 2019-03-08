/*	File: Data.c
 *	Purpose:	...
 */

#include "Definitions.h"
#include "MacrosAndGlobals.h"

/***** Maybe make constants *****/
// Board referencing strings
char PieceChar[] = ".PRNBQKprnbqk";
char SideChar[] = "wb-";
char RankChar[] = "12345678";
char FileChar[] = "abcdefgh";

// Piece type tracking
int PieceBIG[PIECES_NUM + 1] = {FALSE, FALSE, TRUE, TRUE,
									TRUE, TRUE, TRUE,
									FALSE, TRUE, TRUE,
									TRUE, TRUE, TRUE};
int PieceMJR[PIECES_NUM + 1] = { FALSE, FALSE, TRUE, FALSE,
									FALSE, TRUE, TRUE,
									FALSE, TRUE, FALSE,
									FALSE, TRUE, TRUE };
int PieceMNR[PIECES_NUM + 1] = { FALSE, FALSE, FALSE, TRUE,
									TRUE, FALSE, FALSE,
									FALSE, FALSE, TRUE,
									TRUE, FALSE, FALSE };
int PieceVAL[PIECES_NUM + 1] = { 0, 100, 550, 325,
									325, 1000, 50000,
									100, 550, 325,
									325, 1000, 50000 };
int PieceCOL[PIECES_NUM + 1] = { BOTH, WHITE, WHITE, WHITE,
									WHITE, WHITE, WHITE,
									BLACK, BLACK, BLACK,
									BLACK, BLACK, BLACK };
