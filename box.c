#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

void __attribute__ ((constructor)) ctor() { printf("\033[2J"); }
void __attribute__ ((destructor))  dtor() { printf("\033[?25h"); }

#define TLC L"┌"
#define TRC L"┐"
#define BLC L"└"
#define BRC L"┘"
#define H L"─"
#define V L"│"
#define LT L"├"
#define RT L"┤"
#define DT L"┴"
#define UT L"┬"
#define CROSS L"┼"

#define REP0(X)
#define REP1(X) X
#define REP2(X) REP1(X) X
#define REP3(X) REP2(X) X
#define REP4(X) REP3(X) X
#define REP5(X) REP4(X) X
#define REP6(X) REP5(X) X
#define REP7(X) REP6(X) X
#define REP8(X) REP7(X) X
#define REP9(X) REP8(X) X
#define REP10(X) REP9(X) X

#define REP(TENS,ONES,X) \
  REP##TENS(REP10(X)) \
  REP##ONES(X)

#define REP32(X) REP(3, 2, X)
#define REP33(X) REP32(X) X

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

void gotoxy(int x, int y) {
	printf("%c[%d;%df", 0x1B, y, x);
}

int cellx(int col) {
	return 32 * col + 3;
}

int celly(int row) {
	return 32 * row + 4;
}



void draw_hline_top() {
	wprintf(TLC); // Top left
	
	for (int i=0; i<6; ++i) { // Middle
		if (i == 0) printf(COLOR_RED);
		wprintf(REP(3, 2, H));
		if (i == 0) printf(COLOR_RESET);
		if (i != 5) wprintf(UT);
	}
	wprintf(TRC); //Top right
}

void draw_primitive_box() {
	// First, draw main lines
	REP7(
		wprintf(REP6(REP33(H)) "\n");
		REP5(
			REP7(wprintf(V REP32(" "));)
			printf("\n");
			)
		)
	wprintf(REP6(REP33(H)) "\n");

	// Corners
	gotoxy(0,0);
	wprintf(TLC);
	gotoxy(32*6+7, 0);
	wprintf(TRC);
	gotoxy(0, 5*7+8);
	wprintf(BLC);
	gotoxy(32*6+7, 5*7+8);
	wprintf(BRC);

	// Crosses
	for (int y=0; y<6; y++) {
		gotoxy(0, y*6+7);
		wprintf(LT);
		gotoxy(32*6+7, y*6+7);
		wprintf(RT);
	}

}

int main(void)
{
    setlocale(LC_ALL, "");
    fwide(stdout, 1);
    gotoxy(0,0);
    // draw_hline_top();
    // printf("\n");
    // draw_primitive_box();
    printf(COLOR_BLUE);
    wprintf(TLC REP(0, 5, REP(3, 2, H) UT) REP(3, 2, H) TRC "\n");
    REP(0, 6,
    	REP(0, 5, wprintf(V REP(0, 5, REP(3,2, " ") V) REP(3, 2, " ") V "\n");)
    	wprintf(LT REP(0, 5, REP(3,2, H) CROSS) REP(3, 2, H) RT "\n");
    	)
    REP(0, 5, wprintf(V REP(0, 5, REP(3,2, " ") V) REP(3, 2, " ") V "\n");)
    wprintf(BLC REP(0, 5, REP(3,2, H) DT) REP(3, 2, H) BRC "\n");
    printf(COLOR_RESET);

    gotoxy(cellx(0), celly(0));
    printf("This is in 0,0");
    gotoxy(cellx(1), celly(1));
    printf("This is in 1,1");
    gotoxy(0,100);
    getchar();


    return EXIT_SUCCESS;
}

