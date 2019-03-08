#include "Definitions.h"
#include "MacrosAndGlobals.h"
#include "Functions.h"

#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"

int main(void) {

	AllInitialize();

	printf("Files\n");

	for (int index = 0; index < VRTBRD_SZ; index++) {
		if (index % 10 == 0 && index != 0)
			printf("\n");
		printf("%4d", VRT2F(index));
	}

	printf("\n\n\nRanks\n");

	for (int index = 0; index < VRTBRD_SZ; index++) {
		if (index % 10 == 0 && index != 0)
			printf("\n");
		printf("%4d", VRT2R(index));
	}

	/*
	BOARD_STRUCT Board;

	ParseFEN(START_FEN, &Board);
	PrintBoard(&Board);

	printf("\n\n\n");

	ParseFEN(FEN1, &Board);
	PrintBoard(&Board);

	printf("\n\n\n");

	ParseFEN(FEN2, &Board);
	PrintBoard(&Board);

	printf("\n\n\n");

	ParseFEN(FEN3, &Board);
	PrintBoard(&Board);

	*/

	printf("\n\n\n");

	system("PAUSE");
	return 0;
}