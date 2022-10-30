#ifndef Chesslib
#define Chesslib
#include <Arduino.h>
//---------BLACKS------------
#define BLACKPAWN "BP"
#define BLACKKNIGHT "BN"
#define BLACKROCK "BR"
#define BLACKBISHOP "BS"
#define BLACKQUEEN "BQ"
#define BLACKKING "BK"
//---------WHITES------------
#define WHITEPAWN "WP"
#define WHITEKNIGHT "WN"
#define WHITEROCK "WR"
#define WHITEBISHOP "WS"
#define WHITEQUEEN "WQ"
#define WHITEKING "WK"
//--------Positions---------
#define POSITIONS "87654321"
#define POSITIONS2 "abcdefgh"

void print_board(int board[][8]); //Imprime el tablero de una manera legible
void print_piece(int piece); //Optimizable con un arbol binario real
void convert_to_nomenclature(int diugit1, int digit2);//Converto to chess nomenclature
void convert_from_nomenclature(int cords[], char char1, char char2);//And viceversa

/*Chesslib*/
bool move_piece_manager(int board[][8], int orig[], int dest[], bool *turn, bool *enpasant, int enpasant_cords[]);//this funtion will manage how to move the pieces and if they are a legal move
void move_piece(int board[][8], int orig[2], int dest[2], int piece);//move a piece
void inputsanitize(int board[][8], bool *turn, bool *enpasant, int enpasant_cords[], bool *win);//sanitize the input for the move comand
void norme(int board[][8], bool *win);

/*ChessNorm*/
bool check_wins(int board[][8]);
void make_queens(int board[][8]);

/*ChessMoveslib*/
bool white_pawn_moves(int board[][8], int orig[], int dest[], int piece, bool *enpasant, int enpasant_cords[]);
bool black_pawn_moves(int board[][8], int orig[], int dest[], int piece, bool *enpasant, int enpasant_cords[]);
bool khight_moves(int board[][8], int orig[], int dest[], int piece);
bool rock_moves(int board[][8], int orig[], int dest[], int piece);
bool bishop_moves(int board[][8], int orig[], int dest[], int piece);
bool queen_moves(int board[][8], int orig[], int dest[], int piece);
bool king_moves(int board[][8], int orig[], int dest[], int piece);
bool enpasant_move(int board[][8], int orig[], int dest[], int piece, bool enpasant, int enpasant_cords[]);

/*Utilitys*/
void clean_buffer();
void copy_board_fun(int souce[][8], int copy[][8]);

/*Minmax*/
int set_score(int board[][8]);
int minimax(int board[][8], int depth, bool isMaxi, bool *enpasant, int enpasant_cords[], int best_move[]);
#endif
