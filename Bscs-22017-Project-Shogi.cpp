#include<windows.h>
#include<iomanip>
#include<conio.h>
#include<cmath>
#include<fstream>
#include<string>
#include<iostream>


enum color { white, black };

using namespace std;


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct position
{
	int ri, ci;
};
void init(char**& B, int& dim, string  pnames[], int& turn)
{
	string type;
	int mode = 0;
	do
	{
		cout << "enter 1 to continue previous game " << endl;
		cout << "enter 2 to start new game " << endl;
		cin >> mode;
	} while (mode != 1 && mode != 2);
	if (mode == 1)
	{
		type = "copy.txt";
	}
	if (mode == 2)
	{
		type = "Text.txt";
	}
	ifstream rdr(type);
	if (!rdr)
	{
		cout << "can't read , check name " << endl;
		exit(1);
	}
	rdr >> dim;
	B = new char* [dim];
	for (int ri = 0; ri < dim; ri++)
	{
		B[ri] = new char[dim];
	}
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			rdr >> B[ri][ci];
		}
	}
	cout << "Players are : " << endl;
	for (int r = 0; r < 2; r++)
	{
		cout << "Player " << r + 1 << " name ^_^ =>";
		string a;
		cin >> a;
		pnames[r] = a;
	}
	turn = white;
}
void printboard(char** B, int& dim)
{
	//system("cls");
	//cout << "<==================>" << endl << endl;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			cout << B[ri][ci];
		}
		cout << endl;
	}
	//cout << endl << "<===================>" << endl << endl;
}
void drawpawn(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawking(int r, int c)
{
	gotoRowCol(r - 3, c - 3);
	cout << char(-37) << "  " << char(-37) << "  " << char(-37);
	gotoRowCol(r - 2, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawlance(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawknight(int r, int c)
{
	gotoRowCol(r - 2, c - 1);
	cout << char(-37) << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << " " << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 2);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 1);
	cout << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);

}
void drawsg(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawgg(int r, int c)
{
	gotoRowCol(r - 2, c - 2);
	cout << char(-37) << "   " << char(-37);
	gotoRowCol(r - 1, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawbishop(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c);
	cout << char(-37);
	gotoRowCol(r + 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 2, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 3, c - 3);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}
void drawrook(int r, int c)
{
	gotoRowCol(r - 2, c);
	cout << char(-37);
	gotoRowCol(r - 1, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r, c - 1);
	cout << char(-37) << char(-37) << char(-37);
	gotoRowCol(r + 1, c);
	cout << char(-37);
	gotoRowCol(r + 2, c - 2);
	cout << char(-37) << char(-37) << char(-37) << char(-37) << char(-37);
}

void drawbox(int sr, int sc, int brow, int bcol, int color, int sec_color, char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				switch (sym) {
				case 'p':
					SetClr(12);
					drawpawn(sr + r, sc + c);
					break;
				case 'a':
					SetClr(4);
					drawpawn(sr + r, sc + c);
					break;
				case 'P':
					SetClr(9);
					drawpawn(sr + r, sc + c);
					break;
				case 'A':
					SetClr(1);
					drawpawn(sr + r, sc + c);
					break;
				case 'L':
					SetClr(9);
					drawlance(sr + r, sc + c);
					break;
				case 'E':
					SetClr(1);
					drawlance(sr + r, sc + c);
					break;
				case 'l':
					SetClr(12);
					drawlance(sr + r, sc + c);
					break;
				case 'e':
					SetClr(4);
					drawlance(sr + r, sc + c);
					break;
				case 'n':
					SetClr(12);
					drawknight(sr + r, sc + c);
					break;
				case 'f':
					SetClr(4);
					drawknight(sr + r, sc + c);
					break;
				case 'N':
					SetClr(9);
					drawknight(sr + r, sc + c);
					break;
				case 'F':
					SetClr(1);
					drawknight(sr + r, sc + c);
					break;
				case 's':
					SetClr(12);
					drawsg(sr + r, sc + c);
					break;
				case 'h':
					SetClr(4);
					drawsg(sr + r, sc + c);
					break;
				case 'S':
					SetClr(9);
					drawsg(sr + r, sc + c);
					break;
				case 'H':
					SetClr(1);
					drawsg(sr + r, sc + c);
					break;
				case 'k':
					SetClr(12);
					drawking(sr + r, sc + c);
					break;
				case 'j':
					SetClr(4);
					drawking(sr + r, sc + c);
					break;
				case 'K':
					SetClr(9);
					drawking(sr + r, sc + c);
					break;
				case 'J':
					SetClr(1);
					drawking(sr + r, sc + c);
					break;
				case 'g':
					SetClr(12);
					drawgg(sr + r, sc + c);
					break;
				case 'i':
					SetClr(4);
					drawgg(sr + r, sc + c);
					break;
				case 'G':
					SetClr(9);
					drawgg(sr + r, sc + c);
					break;
				case 'I':
					SetClr(1);
					drawgg(sr + r, sc + c);
					break;
				case 'B':
					SetClr(9);
					drawbishop(sr + r, sc + c);
					break;
				case 'C':
					SetClr(1);
					drawbishop(sr + r, sc + c);
					break;
				case 'b':
					SetClr(12);
					drawbishop(sr + r, sc + c);
					break;
				case 'c':
					SetClr(4);
					drawbishop(sr + r, sc + c);
					break;
				case 'R':
					SetClr(9);
					drawrook(sr + r, sc + c);
					break;
				case 'D':
					SetClr(1);
					drawrook(sr + r, sc + c);
					break;
				case 'r':
					SetClr(12);
					drawrook(sr + r, sc + c);
					break;
				case 'd':
					SetClr(4);
					drawrook(sr + r, sc + c);
					break;
				}
				SetClr(sec_color);
			}
			else {
				if (r == 0 || c == 0 || r == brow - 1 || c == bcol - 1) {

					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}
	}
}

void printbox(int dim, int bRows, int bCols, char**& B)
{
	system("cls");
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			drawbox(ri * bRows, ci * bCols, bRows, bCols, 15,3, B[ri][ci]);
		}
	}
}

void drawbox1(int sr, int sc, int brow, int bcol, int color) 
{
	for (int r = 0; r < brow; r++) 
	{
		for (int c = 0; c < bcol; c++)
		{
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				continue;
			}
			else 
			{
				if (r == 0 || c == 0 || r == brow - 1 || c == bcol - 1) 
				{

					SetClr(color);
					gotoRowCol(sr + r, sc + c);
					cout << char(-37);
				}
			}
		}
	}

}
void drawbox2(int sr, int sc, int brow, int bcol, int color, int sec_color, char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				switch (sym) {
				case 'p':
					SetClr(12);
					drawpawn(sr + r, sc + c);
					break;
				case 'P':
					SetClr(9);
					drawpawn(sr + r, sc + c);
					break;
				case 'L':
					SetClr(9);
					drawlance(sr + r, sc + c);
					break;
				case 'l':
					SetClr(12);
					drawlance(sr + r, sc + c);
					break;
				case 'n':
					SetClr(12);
					drawknight(sr + r, sc + c);
					break;
				case 'N':
					SetClr(9);
					drawknight(sr + r, sc + c);
					break;
				case 's':
					SetClr(12);
					drawsg(sr + r, sc + c);
					break;
				case 'S':
					SetClr(9);
					drawsg(sr + r, sc + c);
					break;
				case 'k':
					SetClr(12);
					drawking(sr + r, sc + c);
					break;
				case 'K':
					SetClr(9);
					drawking(sr + r, sc + c);
					break;
				case 'g':
					SetClr(12);
					drawgg(sr + r, sc + c);
					break;
				case 'G':
					SetClr(9);
					drawgg(sr + r, sc + c);
					break;
				case 'B':
					SetClr(9);
					drawbishop(sr + r, sc + c);
					break;
				case 'b':
					SetClr(12);
					drawbishop(sr + r, sc + c);
					break;
				case 'R':
					SetClr(9);
					drawrook(sr + r, sc + c);
					break;
				case 'r':
					SetClr(12);
					drawrook(sr + r, sc + c);
					break;
				}
				SetClr(sec_color);
			}
			else {
				continue;
			}
		}
	}
}
void drawbox3(int sr, int sc, int brow, int bcol, int color, int sec_color, char sym) {
	for (int r = 0; r < brow; r++) {
		for (int c = 0; c < bcol; c++) {
			if (r == ceil((brow - 1) / 2) && c == ceil((bcol - 1) / 2))
			{
				SetClr(sec_color);
				gotoRowCol(sr + r, sc + c);
				switch (sym) {
				case 'p':
					SetClr(12);
					drawpawn(sr + r, sc + c);
					break;
				case 'P':
					SetClr(9);
					drawpawn(sr + r, sc + c);
					break;
				case 'L':
					SetClr(9);
					drawlance(sr + r, sc + c);
					break;
				case 'l':
					SetClr(12);
					drawlance(sr + r, sc + c);
					break;
				case 'n':
					SetClr(12);
					drawknight(sr + r, sc + c);
					break;
				case 'N':
					SetClr(9);
					drawknight(sr + r, sc + c);
					break;
				case 's':
					SetClr(12);
					drawsg(sr + r, sc + c);
					break;
				case 'S':
					SetClr(9);
					drawsg(sr + r, sc + c);
					break;
				case 'k':
					SetClr(12);
					drawking(sr + r, sc + c);
					break;
				case 'K':
					SetClr(9);
					drawking(sr + r, sc + c);
					break;
				case 'g':
					SetClr(12);
					drawgg(sr + r, sc + c);
					break;
				case 'G':
					SetClr(9);
					drawgg(sr + r, sc + c);
					break;
				case 'B':
					SetClr(9);
					drawbishop(sr + r, sc + c);
					break;
				case 'b':
					SetClr(12);
					drawbishop(sr + r, sc + c);
					break;
				case 'R':
					SetClr(9);
					drawrook(sr + r, sc + c);
					break;
				case 'r':
					SetClr(12);
					drawrook(sr + r, sc + c);
					break;
				}
				SetClr(sec_color);
			}
			else {
				continue;
			}
		}
	}
}

void printbox1(int dim, int brow, int bcol, char** B, string pname, string pname1, char**& a, char**& d, int& i, int& j) {
	for (int r = brow - 2; r < brow; r++) 
	{
		for (int c = bcol + 3; c < bcol + 20; c++) 
		{
			drawbox1(r * brow, c * bcol, brow, bcol, 7);
		}
	}
	int x = 0;
	for (int r = brow - 2; r < brow; r++) {
		for (int c = bcol + 3; c < bcol +i+4; c++,x++) {
			if ((r % 2) == 0) {}
			else {
				if (x <= i) {
					drawbox2(r * brow, c * bcol, brow, bcol, 7, 9, a[0][x]);
				}
			}
		}
	}

	for (int r = brow - 2; r < brow; r++) {
		int y = 0;
		for (int c = bcol + 3; c < bcol  +j+ 4; c++,y++) {
			if ((r % 2) == 0) {
				if (y <= j) {
					drawbox2(r * brow, c * bcol, brow, bcol, 7, 5, d[0][y]);
				}
			}
			else {}
		}
	}

}
void printbox(int dim, int brow, int bcol, char** b, string pname, string pname1, char**& a, char**& d) 
{
	system("cls");
	for (int r = 0; r < brow; r++) 
	{
		for (int c = 0; c < bcol; c++) 
		{
			drawbox(r * brow, c * bcol, brow, bcol, 15, 3, b[r][c]);
			if (r == 7 && c == bcol - 1) 
			{
				cout << "   " << pname << " captured pieces: " << endl;
			}
			if (r == 8 && c == bcol - 1) 
			{
				cout << "   " << pname1 << " captured pieces: " << endl;
			}
		}
	}
}

void trnmsg(string a)
{
	cout << a << " 's turn" << endl;
}

void slcpos(position& p, int dim)
{
	//cout << "give coordinates (A-1:I-9) : " << endl;
	//char c;
	//int d;
	//cin >> c >> d;    // A,a;
	//c = toupper(c);
	//p.ri = d - 1;
	//p.ci = c - 'A';
	int x, y;
	getRowColbyLeftClick(x, y);
	p.ri = x / dim;
	p.ci = y / dim;
}

bool iswhitepc(char& sym)
{
	return sym >= 'A' && sym <= 'Z';
}
bool isblackpc(char& sym)
{
	return sym >= 'a' && sym <= 'z';
}
bool ismypc(char sym, int& turn)
{
	if (turn == black)
	{
		return isblackpc(sym);
	}
	else
		return iswhitepc(sym);
}

bool isvalidsr(char**& B, int& dim, position& sc, int& turn)
{
	if (sc.ri < 0 || sc.ri > dim || sc.ci < 0 || sc.ci > dim)
	{
		return false;
	}
	return ismypc(B[sc.ri][sc.ci], turn);
}
bool isvalidds(char**& B, int& dim, position& ds, int& turn)
{
	if (ds.ri < 0 || ds.ri > dim || ds.ci < 0 || ds.ci > dim)
	{
		return false;
	}
	return !ismypc(B[ds.ri][ds.ci], turn);
}

void updtboard(char**& B, position& sc, position& ds)
{
	char p = B[sc.ri][sc.ci];
	B[ds.ri][ds.ci] = p;
	B[sc.ri][sc.ci] = '-';
}

void nakliboardupdate(char ** & N,int & dim,char **&B, position & sc, position & ds)
{
	N = new char* [dim];
	for (int ri = 0; ri < dim; ri++)
	{
		N[ri] = new char[dim];
	}
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			N[ri][ci]= B[ri][ci];
		}
	}
	char p = N[sc.ri][sc.ci];
	N[ds.ri][ds.ci] = p;
	N[sc.ri][sc.ci] = '-';
}
void delnakli(char**& N,int &dim)
{
	for (int i = 0; i < dim; i++)
	{
		delete[]N[i];
	}
	delete[]N;
}

void turnch(int& turn)
{
	turn = (turn + 1) % 2;
}

bool ishori(position sc, position ds)
{
	return (sc.ri == ds.ri);
}
bool isver(position sc, position ds)
{
	return (sc.ci == ds.ci);
}
bool isdig(position sc, position ds)
{
	return((abs(ds.ri - sc.ri)) == (abs(ds.ci - sc.ci)));
}
bool ishoripathclr(char** B,position sc, position ds)
{
	if (sc.ci < ds.ci)
	{
		for (int c = sc.ci + 1; c < ds.ci; c++)
		{
			if (B[sc.ri][c] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (int c = ds.ci + 1; c < sc.ci; c++)
		{
			if (B[sc.ri][c] != '-')
			{
				return false;
			}
		}
		return true;
	}

}
bool ishoripathclr2(char** B,position sc, position ds)
{
	int rs, re;
	if (sc.ri < ds.ri)
	{
		rs = sc.ri + 1, re = ds.ri - 1;
	}
	else
	{
		rs = ds.ri + 1, re = sc.ri - 1;
	}
	for (int r = rs; r <= re; r++)
	{
		if (B[r][sc.ci] != '-')
		{
			return false;
		}
	}
	return true;
}
bool isverpthclr(char** B,position sc, position ds)
{
	if (sc.ri < ds.ri)
	{
		for (int r = sc.ri + 1; r < ds.ri; r++)
		{
			if (B[r][sc.ci] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (int r = ds.ri - 1; r < sc.ri; r--)
		{
			if (B[r][sc.ci] != '-')
			{
				return false;
			}
		}
		return true;
	}

}
bool isverpthclr2(char** B,position sc, position ds)
{
	int rs, re;
	if (sc.ri < ds.ri)
	{
		rs = sc.ri + 1, re = ds.ri - 1;
	}
	else
	{
		rs = ds.ri + 1, re = sc.ri - 1;
	}
	for (int r = rs; r <= re; r++)
	{
		if (B[r][sc.ci] != '-')
		{
			return false;
		}
	}
	return true;
}
bool isdigRL(char** B,position sc, position ds)
{
	if ((sc.ri < ds.ri) && (sc.ci < ds.ci))
	{
		for (int r = sc.ri + 1; r < ds.ri; r++)
		{
			for (int c = sc.ci + 1; c < ds.ci; c++)
			{
				if (r == c)
				{
					if (B[r][c] != '-')
						return false;
				}
			}
		}
		return true;
	}
	else
	{
		for (int r = ds.ri + 1; r < sc.ri; r++)
		{
			for (int c = ds.ci + 1; c < sc.ci; c++)
			{
				if (r == c)
				{
					if (B[r][c] != '-')
						return false;
				}
			}
		}
		return true;
	}
}
bool isdigLR(char** B,position sc, position ds)
{
	if ((sc.ri < ds.ri) && (sc.ci < ds.ci))
	{
		for (int r = sc.ri + 1; r < ds.ri; r++)
		{
			for (int c = ds.ci + 1; c < sc.ci; c++)
			{
				if ((abs(ds.ri - sc.ri)) == (abs(ds.ci - sc.ci)))
				{
					if (B[r][c] != '-')
						return false;
				}
			}
		}
		return true;
	}
	else
	{
		for (int r = ds.ri + 1; r < sc.ri; r++)
		{
			for (int c = sc.ci + 1; c < ds.ci; c++)
			{
				if ((abs(ds.ri - sc.ri)) == (abs(ds.ci - sc.ci)))
				{
					if (B[r][c] != '-')
						return false;
				}
			}
		}
		return true;
	}
}
bool isdigpthclrLTR(char** B, position sc, position ds)
{
	if (sc.ri < ds.ri)
	{
		int dr = ds.ri - sc.ri;
		for (int i = 1; i < dr; i++)
		{
			if (B[sc.ri + i][sc.ci + i] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		int dr = sc.ri - ds.ri;
		for (int i = 1; i < dr; i++)
		{
			if (B[sc.ri - i][sc.ci - i] != '-')
			{
				return false;
			}
		}
		return true;
	}
}
bool isdigpthclrRTL(char** B, position sc, position ds)
{
	if (sc.ri < ds.ri)
	{
		int dr = ds.ri - sc.ri;
		for (int i = 1; i < dr; i++)
		{
			if (B[sc.ri + i][sc.ci - i] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		int dr = sc.ri - ds.ri;
		for (int i = 1; i < dr; i++)
		{
			if (B[sc.ri - i][sc.ci = i] != '-')
			{
				return false;
			}
		}
		return true;
	}
}
bool dpcL2R(char** B, position Sc, position Dc)
{
	if (Sc.ri < Dc.ri)
	{
		for (int i = 1; i < Dc.ri - Sc.ri; i++)
		{
			if (B[Sc.ri + i][Sc.ci + i] != '-')
			{
				return false;
			}
		}

	}

	else
	{
		for (int i = 1; i < Sc.ri - Dc.ri; i++)
		{
			if (B[Dc.ri + i][Dc.ci + i] != '-')
			{
				return false;
			}
		}

	}

}
bool dpcR2L(char** B, position Sc, position Dc)
{
	if (Sc.ri < Dc.ri)
	{
		for (int i = 1; i < Dc.ri - Sc.ri; i++)
		{
			if (B[Sc.ri + i][Sc.ci - i] != '-')
			{
				return false;
			}
		}

	}

	else
	{
		for (int i = 1; i < Sc.ri - Dc.ri; i++)
		{
			if (B[Dc.ri - i][Dc.ci + i] != '-')
			{
				return false;
			}
		}

	}

}
bool isdigpthclr(char** B,position sc, position ds)
{
	return ((isdigRL(B, sc, ds)) || (isdigLR(B, sc, ds)));
}
bool isdigfrwd(char** B,position sc, position ds)
{
	int d = abs(sc.ri - ds.ri - 1);
	for (int i = 1; i < d; i++)
	{
		if (B[sc.ri - i][sc.ci - i] != '-')
			return false;
	}
	for (int i = 1; i < d; i++)
	{
		if (B[sc.ri - i][sc.ci + i] != '-')
			return false;
	}
	return true;
}
bool isdigR2Lpthclr(char** b, position sc, position ds) {
	int d;
	if (sc.ri < ds.ri) {
		d = ds.ri - sc.ri - 1;
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri + i][sc.ci - i] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		d = (sc.ri - ds.ri - 1);
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri - i][sc.ci + i] != '-') {
				return false;
			}
		}
		return true;
	}
}
bool isdigL2Rpthclr(char** b, position sc, position ds) {
	int d;
	if (sc.ri < ds.ri) {
		d = ds.ri - sc.ri - 1;
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri + i][sc.ci + i] != '-') {
				return false;
			}
		}
		return true;
	}
	else {
		d = (sc.ri - ds.ri - 1);
		for (int i = 1; i <= d; i++) {
			if (b[sc.ri - i][sc.ci - i] != '-') {
				return false;
			}
		}
		return true;
	}

}

bool rooklegality(char** B, position sc, position ds)
{
	return ((ishori(sc, ds) && ishoripathclr(B, sc, ds)) || (isver(sc, ds) && isverpthclr2(B, sc, ds)));
}
bool bishoplegality(char** B, position sc, position  ds)
{
	return (isdig(sc, ds) && (isdigL2Rpthclr(B, sc, ds) ||
		isdigR2Lpthclr(B, sc, ds)));
}
bool pawnlegality(char** B, position sc, position ds, int turn)
{
	int dr = abs(sc.ri - ds.ri);
	if (turn == white)
	{
		return (sc.ci == ds.ci) && dr <= 1 && (sc.ri > ds.ri) && (rooklegality(B, sc, ds));
	}
	else
	{
		return (sc.ci == ds.ci) && dr <= 1 && (sc.ri < ds.ri) && (rooklegality(B, sc, ds));
	}
}
bool queenlegality(char** B, position sc, position ds)
{
	return((rooklegality(B, sc, ds)) || (bishoplegality(B, sc, ds)));
}
bool kinglegality(char** B, position sc, position ds)
{
	int r = abs(sc.ri - ds.ri);
	int c = abs(sc.ci - ds.ci);
	return ((queenlegality(B, sc, ds)) && r <= 1 && c <= 1);
}
bool knightlegality(char** B, position sc, position ds, int turn)
{

	int dr = abs(sc.ri - ds.ri);
	int dc = abs(sc.ci - ds.ci);
	if (turn == white)
	{
		return dr == 2 && dc == 1 && (sc.ri > ds.ri);
	}
	else
	{
		return dr == 2 && dc == 1 && (sc.ri < ds.ri);
	}

}
bool lancelegality(char** B, position sc, position ds, int turn)
{

	if (turn == white)
	{
		return (sc.ci == ds.ci) && (sc.ri > ds.ri) && (rooklegality(B, sc, ds));
	}
	else
	{
		return (sc.ci == ds.ci) && (sc.ri < ds.ri) && (rooklegality(B, sc, ds));
	}
}
bool silverlegality(char** B, position sc, position ds, int turn)
{

	int dr = abs(sc.ri - ds.ri);
	int dc = abs(sc.ci - ds.ci);
	return(dr <= 1 && dc <= 1 && (pawnlegality(B, sc, ds, turn) || bishoplegality(B, sc, ds)));

}
bool generallegality(char** B, position sc, position ds, int turn)
{
	int dr = abs(sc.ri - ds.ri);
	int dc = abs(sc.ci - ds.ci);
	if (turn == white)
	{
		return dr <= 1 && dc <= 1 && (rooklegality(B, sc, ds) || ((sc.ri > ds.ri) && bishoplegality(B, sc, ds)));
	}
	else
	{
		return dr <= 1 && dc <= 1 && (rooklegality(B, sc, ds) || ((sc.ri < ds.ri) && bishoplegality(B, sc, ds)));
	}
}

bool islegalmove(char** B, position sc, position ds, int& dim, int& turn)
{
	switch (B[sc.ri][sc.ci])
	{
	case 'k':
	case 'j':
	case 'K':
	case 'J':
		return kinglegality(B, sc, ds);
		break;
	case 'a':
	case 'A':
	case 'h':
	case 'H':
	case 'f':
	case 'F':
	case 'e':
	case 'E':
	case 'g':
	case 'G':
	case 'i':
	case 'I':
		return generallegality(B, sc, ds, turn);
		break;
	case 'D':
	case 'd':
		return (kinglegality(B, sc, ds) && rooklegality(B, sc, ds));
		break;
	case 'c':
	case 'C':
		return (bishoplegality(B, sc, ds) && rooklegality(B, sc, ds));
		break;
	case 's':
	case 'S':
		return silverlegality(B, sc, ds, turn);
		break;
	case 'n':
	case 'N':
		return knightlegality(B, sc, ds, turn);
		break;
	case 'l':
	case 'L':
		return lancelegality(B, sc, ds, turn);
		break;
	case 'r':
	case 'R':
		return rooklegality(B, sc, ds);
		break;
	case 'b':
	case 'B':
		return bishoplegality(B, sc, ds);
		break;
	case 'p':
	case 'P':
		return pawnlegality(B, sc, ds, turn);
		break;
	}
}

bool** comp_high(char** B, position sc, int dim, int turn)
{
	bool** bmap = new bool* [dim];
	for (int r = 0; r < dim; r++)
	{
		bmap[r] = new bool[dim] {};
	}
	position ds;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			ds.ri = r;
			ds.ci = c;
			if ((isvalidds(B, dim, ds, turn)) && islegalmove(B, sc, ds, dim, turn))
			{
				bmap[r][c] = true;
			}
		}
	}
	return bmap;
}

bool** comp_high1(char** B, position sc, int dim, int turn)
{
	bool** bmap = new bool* [dim];
	for (int r = 0; r < dim; r++)
	{
		bmap[r] = new bool[dim] {};
	}
	position ds;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (B[r][c] == '-')
			{
				bmap[r][c] = true;
			}
		}
	}
	return bmap;
}
void highlight(char** B, bool** map, int dim, int brow, int bcol)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (map[r][c] == true)
			{
				drawbox(r * brow, c * bcol, brow, bcol, 10,3, B[r][c]);
			}
		}
	}
}
void unhighlight(char** B, bool** map, int dim, int brow, int bcol)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (map[r][c] == true)
			{
				if ((r + c) % 2 == 0)
				{
					drawbox(r * brow, c * bcol, brow, bcol, 15,3, B[r][c]);
				}
				else
				{
					drawbox(r * brow, c * bcol, brow, bcol, 3,15, B[r][c]);
				}
			}
		}
	}
}
void findking(char** B,position &ds,int dim, int turn)
{
	//position ds;
	char ch;
		//, s;
	if (turn == white)
	{
		ch = 'K';
	}
	else
	{
		ch = 'k';
	}
	//turnch(turn);
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (ismypc(B[r][c], turn)
									&& (B[r][c]==ch))
										//|| (B[r][c]==s)))
			{
				ds.ri = r;
				ds.ci = c;
				//break;
				//return;
			}
		}
	}
	//turnch(turn);
	//return ;
}
void findking2(char** B, position& ds, int dim, int turn)
{
	switch (B[ds.ri][ds.ci])
	{
		case 'k':
		case 'K':

			for (int r = 0; r < dim; r++)
			{
				for (int c = 0; c < dim; c++)
				{
					if ((ismypc(B[r][c], turn)))
					{
						ds.ri = r;
						ds.ci = c;
						//break;
						//return;
					}
				}
			}
			//break;
	}
}
bool check(char** B, int dim, int turn)
{
	//int ds;
	//turnch(turn);
	position ds;
	findking(B,ds,dim,turn);
	turnch(turn);
	position sc;
	for (int r= 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			sc.ri = r;
			sc.ci = c;
			if ((isvalidsr(B,dim,sc,turn) && islegalmove(B, sc, ds, dim, turn)))
			{
				return true;
			}
		}
	}
	return false;
}
bool selfcheck(char** B, int dim, int turn)
{
	turnch(turn);
	return check(B, dim, turn);
}

void cap1(char**& B, position ds, char**& a, int& i) 
{
	if (a[0][i] != '\0') {
		i++;
	}
	if (B[ds.ri][ds.ci] != '-') {
		a[0][i] = B[ds.ri][ds.ci];
		i++;
	}
	i--;
}
void cap2(char**& B, position ds, char**& b, int& j) 
{
	if (b[0][j] != '\0') {
		j++;
	}
	if (B[ds.ri][ds.ci] != '-') {
		b[0][j] = B[ds.ri][ds.ci];
		j++;
	}
	j--;
}

bool ismypcdrop(char sym, int turn)
{
	if (turn == white)
	{
		return iswhitepc(sym);
	}
	if (turn == black)
	{
		return isblackpc(sym);
	}
}
void save(char**& B, int& dim)
{
	ofstream wrt("copy.txt");
	wrt << dim;
	wrt << endl;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			wrt << B[r][c];
		}
		wrt << endl;
	}
}
void savecapture(char** &a, char**& b,int &i, int &j)
{
	ofstream capture("cap.txt");
	for (int r = 0; r < i; r++)
	{
		capture << a[0][i];
	}
	capture << endl;
	for (int r = 0; r < j; r++)
	{
		capture << b[0][j];
	}
	capture << endl;
}
void undo(char**& B, position& sc, position& ds,char**&a, int &i, char **&b, int& j,int turn)
{
	char c = B[ds.ri][ds.ci];
	B[sc.ri][sc.ci] = c;
	B[ds.ri][ds.ci] = '-';
	if (turn == white && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4))
	{
		char d = a[0][i];
		B[ds.ri][ds.ci] = d;
		a[0][i] = '-';
		i--;
	}
	if (turn == black && (j == 0 || j == 1 || j == 2 || j == 3 || j == 4))
	{
		char e = b[0][j];
		B[ds.ri][ds.ci] = e;
		b[0][j] = '-';
		j--;
	}
}
void promotion(char**& B, position& sc, int turn) {
	if (turn == white) {
		if (sc.ri == 0 || sc.ri == 1 || sc.ri == 2) {
			if (B[sc.ri][sc.ci] == 'P') {
				B[sc.ri][sc.ci] = 'A';
			}
			if (B[sc.ri][sc.ci] == 'B') {
				B[sc.ri][sc.ci] = 'C';
			}
			if (B[sc.ri][sc.ci] == 'R') {
				B[sc.ri][sc.ci] = 'D';
			}
			if (B[sc.ri][sc.ci] == 'L') {
				B[sc.ri][sc.ci] = 'E';
			}
			if (B[sc.ri][sc.ci] == 'N') {
				B[sc.ri][sc.ci] = 'F';
			}
			if (B[sc.ri][sc.ci] == 'S') {
				B[sc.ri][sc.ci] = 'H';
			}
			if (B[sc.ri][sc.ci] == 'G') {
				B[sc.ri][sc.ci] = 'I';
			}
			if (B[sc.ri][sc.ci] == 'K') {
				B[sc.ri][sc.ci] = 'J';
			}
		}
	}
	if (turn == black) {
		if (sc.ri == 6 || sc.ri == 7 || sc.ri == 8) {
			if (B[sc.ri][sc.ci] == 'p') {
				B[sc.ri][sc.ci] = 'a';
			}
			if (B[sc.ri][sc.ci] == 'b') {
				B[sc.ri][sc.ci] = 'c';
			}
			if (B[sc.ri][sc.ci] == 'r') {
				B[sc.ri][sc.ci] = 'd';
			}
			if (B[sc.ri][sc.ci] == 'l') {
				B[sc.ri][sc.ci] = 'e';
			}
			if (B[sc.ri][sc.ci] == 'n') {
				B[sc.ri][sc.ci] = 'f';
			}
			if (B[sc.ri][sc.ci] == 's') {
				B[sc.ri][sc.ci] = 'h';
			}
			if (B[sc.ri][sc.ci] == 'g') {
				B[sc.ri][sc.ci] = 'i';
			}
			if (B[sc.ri][sc.ci] == 'k') {
				B[sc.ri][sc.ci] = 'j';
			}
		}
	}
}

bool isvalidscdrop(char ** c,int dim, position sc,int turn)
{
	if (sc.ri < dim - 2 || sc.ri >= dim || sc.ci < dim + 3 || sc.ci >= dim + 18)
	{
		return false;
	}
	return true;
}
bool isvaliddsdrop(char**& B, int& dim, position& ds, int& turn)
{
	if (ds.ri < 0 || ds.ri >= dim || ds.ci < 0 || ds.ci >= dim)
	{
		return false;
	}
	turn = black;
	if (!ismypc(B[ds.ri][ds.ci], turn))
	{
		turn = white;
		if (!ismypc(B[ds.ri][ds.ci], turn))
		{
			return true;
		}
	}
	//return false;
}



void slcpos1(position& p, int dim)
{
	//cout << "give coordinates (A-1:I-9) : " << endl;
	//char c;
	//int d;
	//cin >> c >> d;    // A,a;
	//c = toupper(c);
	//p.ri = d - 1;
	//p.ci = c - 'A';
	int x, y;
	getRowColbyLeftClick(x, y);
	p.ri = x / dim;
	p.ci = y / dim+9;
}
void updateboard2(char**& B, char**& a, position& sc, position& ds)
{
	int di = sc.ci - 21;
	char p = a[0][di];
	p = toupper(p);
	B[ds.ri][ds.ci] = p;
	a[0][di] = '-';
}

void updateboard1(char**& B, char**& b, position& sc, position& ds)
{
	int di = sc.ci - 21;
	char p = b[0][di];
	p = tolower(p);
	B[ds.ri][ds.ci] = p;
	b[0][di] = '-';
}



int main()
{
	char** B;
	char** N;
	position p1;
	position p2;
	int dim;
	const int p = 5;
	string pnames[p];
	string str;
	int turn;
	init(B, dim, pnames, turn);															//printboard(B, dim);
	/*cout << (void*)&B[0];
	cout << (void*)&B[1];
	cout << (void*)&B[2];
	cout << (void*)&B[3];
	cout << (void*)&B[0][0];*/
	system("cls");
	printbox(dim, dim, dim, B);
	int i = 0;int j = 0;
	char** C;
	char** a;
	char** b;
	a = new char* [0];
	a[0] = new char[10] {};
	b = new char* [0];
	b[0] = new char[10] {};
	/*
	ifstream rdr{ "Text.txt" };
	ofstream out{ "copy.txt" };
	while (!rdr.eof())
	{
		getline(rdr, str);
		out << str << "\n";
	}*/
	_getch();
	cout << endl;
	bool** map;
	bool** drop;
	char inp;
	while (true)
	{
		do
		{
			do
			{
				cout << endl<<endl<<endl<<endl<<endl<<endl<<endl << endl << endl<<endl<<endl<<endl;
				trnmsg(pnames[turn]);
				do
				{
					do
					{
						slcpos(p1, dim);                                //cout << "enter source" << endl;
					} while (!isvalidsr(B, dim, p1, turn));
					promotion(B, p1, turn);
					map = comp_high(B, p1, dim, turn);
					highlight(B, map, dim, dim, dim);
					slcpos(p2, dim);                                    //cout << "enter destination" << endl;
					unhighlight(B, map, dim, dim, dim);
				} while (!isvalidds(B, dim, p2, turn));  
			} while (!map[p2.ri][p2.ci]);   
		} while (selfcheck(B, dim, turn));

		if (turn == white)
		{
			cap1(B, p2, a, i);
			printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
			/*if (i != 0)
			{
				int k; char c;
				cout << "\n\n\n\ndo you want to drop a piece" << endl;
				cout << "enter 1 to drop or 2 to not to drop " << endl;
				cin >> k;
				if (k == 1) {
					do{
						do {
							cout << "which piece you want to drop " << endl;
							cin >> c;
						} while (dropsearch(B, a, c));
						cout << "enter destination" << endl;
						slcpos(p2, dim);
					} while (!isvaliddrop(B, dim, p2, turn));
					dropupdate(B, a, c, p2);
				}
			}*/
		}
		if (turn == black)
		{
			cap2(B, p2, b, j);
			printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
		}
		updtboard(B, p1, p2);
		printbox(dim, dim, dim, B, pnames[0], pnames[1], a, b);
		printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
		/*if (a[0][0] != '\0' || b[0][0] != '\0')
		{
			char n;
			cout << "\n\n\n\n\n\n\n\n\ndo you want to drop a piece (y/n)?" << endl;
			cin >> n;
			switch(n)
			{
				case 'n':
					break;
				case 'N':
					break;
				case 'y':
				case 'Y':
					if (turn == white)
					{
						do {
							do {
								slcpos1(p1, dim);
							} while (!isvalidscdrop(B, dim, p1, turn));
							drop = comp_high1(B, p1, dim, turn);
							highlight(B, drop, dim, dim, dim);
							slcpos(p2, dim);
							unhighlight(B, drop, dim, dim, dim);
						} while (!isvaliddsdrop(B, dim, p2, turn));
						updateboard2(B, a, p1, p2);
						printbox(dim, dim, dim, B, pnames[0], pnames[1], a, b);
						printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
						i--;
					}
					if (turn == black)
					{
						do {
							do {
								slcpos1(p1, dim);
							} while (!isvalidscdrop(B, dim, p1, turn));
							drop = comp_high1(B, p1, dim, turn);
							highlight(B, drop, dim, dim, dim);
							slcpos(p2, dim);
							unhighlight(B, drop, dim, dim, dim);
						} while (!isvaliddsdrop(B, dim, p2, turn));
						updateboard1(B, b, p1, p2);
						printbox(dim, dim, dim, B, pnames[0], pnames[1], a, b);
						printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
						j--;
					}
					break;
				default :
					cout << "\n\n\n\n\nyou have entered wrong choice" << endl;
			}
		}*/
		
		if (check(B, dim, turn))
		{
			cout << "\n\n\ncheck hai " << endl;
			Sleep(1000);
			system("cls");
			printbox(dim, dim, dim, B);
		}
		/*cout << "\n\n\n\n\ndo you want to undo your move ?" << endl;
		int o;
		cout << "enter 1 to undo " << endl;
		cout << "enter 2 to continue" << endl;
		cin >> o;
		if (o == 1)
		{
			undo(B, p1, p2,a,i,b,j,turn);
			printbox(dim, dim, dim, B, pnames[0], pnames[1], a, b);
			printbox1(dim, dim, dim, B, pnames[0], pnames[1], a, b, i, j);
			turnch(turn);
		}
		else{}*/
		save(B, dim);
		turnch(turn);
		cout << endl;
	}
	return 0;
}
