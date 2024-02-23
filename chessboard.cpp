// Name:Abdullah Irfan
// UIN:656593997
// File Name: chessboard.cpp
// Project 1: Containers and iterators in C++
// Description: In this C++ programming project, we have a chessboard container and an iterator to navigate it. The chessboard is an 8x8 grid, representing a 
// standard chessboard for a game. Each square on the chessboard can be occupied by a chess piece, which has attributes of color, piece type, and position. 
// The color can be either Black or White, and the piece type can be one of the following: Rook, Knight, Bishop, Queen, King, or Pawn. Enums are suggested for 
// representing colors and piece types.

#include "chessboard.h" // Include the header file for the Chessboard class

// Define the beginning iterator for the Chessboard
ChessboardIterator Chessboard::begin() {
    return ChessboardIterator(*this, 0);
}

// Define the end iterator for the Chessboard
ChessboardIterator Chessboard::end() {
    return ChessboardIterator(*this, 64);
}

// Print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
    // Start with the beginning iterator
    ChessboardIterator it = Chessboard::begin();
    int cnt = 1;
    vector<string> rows;
    
    // Iterate over the rows and columns of the chessboard
    for (int i = 0; i < 8; i++) {
        string str = "";
        for (int j = 0; j < 8; j++) {
            str += (*it).print(); // Get the printable representation of the square
            ++it;
        }
        rows.push_back(str);
    }

    // Print the rows in reverse order to display white at the bottom
    for (int i = 7; i >= 0; i--) {
        cout << rows[i] << endl;
    }
}

// Define a method to print the square's representation
string Square::print() {
    string res = "";

    // Append 'b' for Black, 'w' for White, or a space for no color
    if (color == Black) {
        res += 'b';
    }
    else if (color == White) {
        res += 'w';
    }
    else {
        res += ' ';
    }

    // Append a character representing the piece type or a dot for no piece
    switch (piece) {
    case Rook:
        res += "R";
        break;
    case Knight:
        res += "N";
        break;
    case Bishop:
        res += "B";
        break;
    case King:
        res += "K";
        break;
    case Queen:
        res += "Q";
        break;
    case Pawn:
        res += "P";
        break;
    case noPiece:
        res += ".";
        break;
    default:
        break;
    }
    res += " "; // Add a space between color and piece representation
    return res;
}

