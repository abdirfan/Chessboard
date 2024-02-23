// Name:Abdullah Irfan
// UIN:656593997
// File Name: chessboard.h
// Project 1: Containers and iterators in C++
// Description: In this C++ programming project, we have a chessboard container and an iterator to navigate it. The chessboard is an 8x8 grid, representing a 
// standard chessboard for a game. Each square on the chessboard can be occupied by a chess piece, which has attributes of color, piece type, and position. 
// The color can be either Black or White, and the piece type can be one of the following: Rook, Knight, Bishop, Queen, King, or Pawn. Enums are suggested for 
// representing colors and piece types.

#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>
using namespace std;

// Define separate containers for Color and Piece using enums
enum Color {
    White, Black, noColor
};
enum Piece {
    Rook, Knight, Bishop, King, Queen, Pawn, noPiece
};

// A class representing a single square on the chessboard
class Square {
private:
    Color color;
    Piece piece;
    bool occupied;

public:
    // Default constructor for an unoccupied square
    Square() {
        occupied = false;
        color = noColor;
        piece = noPiece;
    }

    // Constructor for an occupied square with specified Color and Piece
    Square(Color c, Piece p) {
        occupied = true;
        color = c;
        piece = p;
    }

    // A method to retrieve the occupation status, Color, and Piece of the square
    int get(bool& o, Color& c, Piece& p) {
        o = occupied;
        c = color;
        p = piece;
        return 1;
    }

    // Getters for individual properties of the square
    Piece getPiece() {
        return piece;
    }
    bool isOccupied() {
        return occupied;
    }
    Color getColor() {
        return color;
    }

    // A method to provide a printable representation of the square
    string print();
};

// Forward declaration of the ChessboardIterator class
class ChessboardIterator;

// A class representing a chessboard containing squares
class Chessboard {
    // Make the container iterator friendly
    typedef ChessboardIterator iterator;

private:
    Square chessboard[8][8]; // 8x8 array of squares representing the chessboard

public:
    friend class ChessboardIterator;

    // Default constructor for the Chessboard class
    Chessboard() {} // Square does all the initialization

    // Return a square at coordinates (x, y) from the chessboard
    Square square(int x, int y) {
        return chessboard[x][y];
    }

    // Define the beginning iterator for the chessboard
    ChessboardIterator begin();
    
    // Define the end iterator for the chessboard
    ChessboardIterator end();

    // Place a piece on a square at coordinates (x, y) in the chessboard
    int place(int x, int y, Color c, Piece p) {
        // Check for valid coordinates
        if (x < 0 || x > 7) return -1;
        if (y < 0 || y > 7) return -2;
        
        bool oXY;
        Color cXY;
        Piece pXY;
        chessboard[x][y].get(oXY, cXY, pXY);
        
        // Check if the square is already occupied
        if (oXY) return -3;

        // Check for valid Color and Piece values
        if (c < 0 || c > 1) return -4;
        if (p < 0 || p > 5) return -5;
        
        Square s(c, p);
        chessboard[x][y] = s; // Place the piece on the square
        return 1;
    }

    // Get the Color and Piece of a square at coordinates (x, y)
    int get(int x, int y, Color& c, Piece& p) {
        // Check for valid coordinates
        if (x < 0 || x > 7) return -1;
        if (y < 0 || y > 7) return -2;
        
        bool oXY;
        Color cXY;
        Piece pXY;
        chessboard[x][y].get(oXY, cXY, pXY);
        
        // Check if the square is unoccupied
        if (!oXY) return -3;

        c = cXY;
        p = pXY;
        return 1;
    }

    // Check if a knight can move from (x1, y1) to (x2, y2)
    bool knightMove(int x1, int y1, int x2, int y2) {
        int movesX[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
        int movesY[] = { 2, -2, 2, -2, 1, -1, 1, -1 };
        
        for (int i = 0; i < 8; i++) {
            if (x1 + movesX[i] == x2 && y1 + movesY[i] == y2) return true;
        }
        
        return false;
    }

    // Move a piece from (fromX, fromY) to (toX, toY) on the chessboard
    int move(int fromX, int fromY, int toX, int toY) {
        // Check for valid source and destination coordinates
        if (fromX < 0 || fromX > 7) return -1;
        if (fromY < 0 || fromY > 7) return -2;
        if (toX < 0 || toX > 7) return -3;
        if (toY < 0 || toY > 7) return -4;

        bool fromOcc;
        Color fromC;
        Piece fromP;
        chessboard[fromX][fromY].get(fromOcc, fromC, fromP);
        
        // Check if the source square is occupied
        if (!fromOcc) return -5;

        bool toOcc;
        Color toC;
        Piece toP;
        chessboard[toX][toY].get(toOcc, toC, toP);
        
        // Check if the destination square is occupied by a piece of the same color
        if (toOcc && toC == fromC) return -6;

        // Define valid move logic for different piece types
        vector<pair<int, int>> validMoves;
        int deltaX, deltaY;
        int direction;

        switch (fromP) {
        case Rook:
            // Check if the move is along a straight line (horizontal or vertical)
            if (fromX != toX && fromY != toY) {
                return -7;
            }
            if (fromX == toX) {
                int step = (fromY < toY) ? 1 : -1;
                for (int y = fromY + step; y != toY; y += step) {
                    if (chessboard[fromX][y].isOccupied()) {
                        return -7; // There's a piece in the way
                    }
                }
            }
            else {
                int step = (fromX < toX) ? 1 : -1;
                for (int x = fromX + step; x != toX; x += step) {
                    if (chessboard[x][fromY].isOccupied()) {
                        return -7; // There's a piece in the way
                    }
                }
            }
            return true; // Path is clear
            break;
        case Knight:
            deltaX = abs(fromX - toX);
            deltaY = abs(fromY - toY);
            if (!(deltaX == 2 && deltaY == 1) && !(deltaX == 1 && deltaY == 2)) {
                return -7; // Knight can move to the target square
            }
            break;
        case Bishop:
            deltaX = abs(fromX - toX);
            deltaY = abs(fromY - toY);
            if (deltaX == deltaY) {
                int xStep = (fromX < toX) ? 1 : -1;
                int yStep = (fromY < toY) ? 1 : -1;
                for (int x = fromX + xStep, y = fromY + yStep; x != toX; x += xStep, y += yStep) {
                    if (chessboard[x][y].isOccupied()) {
                        return -7; // There's a piece in the way
                    }
                }
            }
            else {
                return -7; // Invalid move for a Bishop
            }
            break;
        case King:
            deltaX = abs(fromX - toX);
            deltaY = abs(fromY - toY);
            if (deltaX > 1 || deltaY > 1) {
                return -7; // King can move to the target square
            }
            break;
        case Queen:
            deltaX = abs(fromX - toX);
            deltaY = abs(fromY - toY);
            if (deltaX == deltaY) {
                // Diagonal move, check for obstacles
                int xStep = (fromX < toX) ? 1 : (fromX > toX) ? -1 : 0;
                int yStep = (fromY < toY) ? 1 : (fromY > toY) ? -1 : 0;
                for (int x = fromX + xStep, y = fromY + yStep; x != toX; x += xStep, y += yStep) {
                    if (chessboard[x][y].isOccupied()) {
                        return -7; // There's a piece in the way
                    }
                }
            }
            else if (fromX == toX || fromY == toY) {
                // Horizontal or vertical move, check for obstacles
                int step = (deltaX == 0) ? ((fromY < toY) ? 1 : -1) : ((fromX < toX) ? 1 : -1);
                for (int x = fromX + step; x != toX || fromY + step != toY; x += step) {
                    if (chessboard[(deltaX == 0) ? fromX : x][fromY + step].isOccupied()) {
                        return -7; // There's a piece in the way
                    }
                }
            }
            else {
                return -7; // Invalid move for a Queen
            }
            break;
        case Pawn:
            deltaX = toX - fromX;
            deltaY = toY - fromY;

            // Determine the direction based on the color of the Pawn
            direction = (fromC == White) ? 1 : -1;

            if (deltaX == 0 && deltaY == direction) {
                if (!chessboard[toX][toY].isOccupied()) {
                    goto valid; // Pawn can move one square forward if the target square is empty
                }
            }
            else if (deltaX == 0 && deltaY == 2 * direction && fromY == (fromC == White ? 1 : 6)) {
                if (!chessboard[toX][toY].isOccupied()) {
                    goto valid; // Pawn can move two squares forward from its starting position if the target square is empty
                }
            }
            else if (abs(deltaX) == 1 && deltaY == direction) {
                if (chessboard[toX][toY].isOccupied()) {
                    goto valid; // Pawn can capture diagonally
                }
            }
            return -7; // Invalid move for a Pawn
        default:
            break;
        }

    valid:

        chessboard[toX][toY] = Square(fromC, fromP);
        chessboard[fromX][fromY] = Square();
        return 1;
    }

    // Print the chessboard
    void print();
};

// A class representing an iterator for the Chessboard class
class ChessboardIterator {
private:
    int position; // A number in [0..63]
    Chessboard chessboard;

public:
    // Constructor for ChessboardIterator
    ChessboardIterator(Chessboard& board, int pos) {
        position = pos;
        chessboard = board; // Store the reference to the chessboard
    }

    // Get the x and y coordinates corresponding to the iterator position
    void xy(int& x, int& y) {
        x = position % 8;
        y = position / 8;
    }

    // Overloaded dereference operator (*) to return the square at the iterator position
    Square operator*() {
        int x, y;
        xy(x, y);
        return chessboard.chessboard[x][y];
    }

    // Overloaded pre-increment operator (++) to move to the next position
    ChessboardIterator& operator++() {
        position++;
        return *this;
    }

    // Overloaded inequality operator (!=) to support iteration
    int operator!=(const ChessboardIterator& a) const {
        return this->position != a.position;
    }
};
