// Name:Abdullah Irfan
// UIN:656593997
// File Name: main.cpp
// Project 1: Containers and iterators in C++
// Description: In this C++ programming project, we have a chessboard container and an iterator to navigate it. The chessboard is an 8x8 grid, representing a 
// standard chessboard for a game. Each square on the chessboard can be occupied by a chess piece, which has attributes of color, piece type, and position. 
// The color can be either Black or White, and the piece type can be one of the following: Rook, Knight, Bishop, Queen, King, or Pawn. Enums are suggested for 
// representing colors and piece types.

#include "chessboard.h"
#include <iostream>
using namespace std;

Color get_illegal_color() {
    Color cs[] = { Black, White };
    int min_c = (int)Black;
    for (Color j : cs)
        min_c = (min_c > (int)j) ? j : min_c;
    return (Color)(min_c - 1);
}


int main() {
    //freopen("output.txt", "w", stdout);

    Chessboard cb;
    int out = 1;
    Color illegal_col = get_illegal_color();

    cout << "\n<<< place() >>>\n\n";
    cout << cb.place(4, 5, White, Knight) << endl; // 1
    cout << cb.place(6, 7, Black, Rook) << endl; // 1
    cout << cb.place(3, 2, White, Knight) << endl; // 1
    cout << cb.place(-9, 0, White, Knight) << endl; // -1
    cout << cb.place(4, 6, Black, Pawn) << endl; // 1
    cout << cb.place(0, 1, illegal_col, Knight) << endl; // -4
    cout << cb.place(3, 2, Black, Queen) << endl; // -3

    cb.print();

    Color c;
    Piece p;

    cout << "\n<<< get() >>>\n\n";
    cout << cb.get(3, 2, c, p) << endl; // 1
    cout << ((c == White) && (p == Knight)) << endl;
    cout << cb.get(33, 3, c, p) << endl; // -1
    cout << cb.get(1, 22, c, p) << endl; // -2
    cout << cb.get(4, 6, c, p) << endl; // 1
    cout << ((c == Black) && (p == Pawn)) << endl;

    cb.print();


    cout << "\n<<< move() >>>\n\n";
    cout << cb.move(3, 2, 1, 3) << endl; // 1

    cb.print();

    cout << cb.move(1, 3, 2, 5) << endl; // 1

    cb.print();

    cout << cb.move(4, 6, 4, 7) << endl; // -7

    cb.print();

    cout << cb.move(4, 5, 3, 7) << endl; // 1

    cb.print();

    cout << cb.move(2, 5, 3, 7) << endl; // -6

    cb.print();

    return 0;
}