//--------LIBRARIS----------
#include "Chesslib.h"

int board[8][8] = {
  -5, -3, -4, -10, -1000, -4, -3, -5,
  -1, -1, -1, -1, -1, -1, -1, -1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1,
  5, 3, 4, 10, 1000, 4, 3, 5
  };

int copy_board[8][8] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

bool win = false;
bool turn = true;
bool enpasant = false;
int enpasant_cords[2] = {0, 0};
bool check_flag = false;
int best_move[4] = {0, 0, 0, 0};
int orig[2];
int dest[2];

typedef struct State
{
  int score;
  bool turn;
  int depht;
  int **board_state;
};

void setup() {
  Serial.begin(9600);
  print_board(board);
}

void loop()
{
  if (win == false)
  {
    if (turn == true)
    {
      inputsanitize(board, &turn, &enpasant, enpasant_cords, &win);
    }
    else if(turn == false)
    {
      minimax(board, 0, false, &enpasant, enpasant_cords, best_move);
      orig[0] = best_move[0];
      orig[1] = best_move[1];
      dest[0] = best_move[2];
      dest[1] = best_move[3];
      move_piece_manager(board, orig, dest, &turn, &enpasant, enpasant_cords);
      turn = true;
      print_board(board);
    }
  }
  delay(500);
}

/* TODO LIST
 *  
 *  -Jaque OK
 *  -En pasant OK
 *  -Jaque mate OK//Se aplican restriciones.
 *  -Coronación OK
 *  -Reyna: OK
 *  -Rey: OK
 *  -Movimiento de las piezas: OK
 *  -Tablas: by repetition FUCK
 *  -Tablas: Agrement FUCK
 *  -Comandos: (Map, tablas, mostrar solo casillas blancas/negras, etc) MORE FUCK
 *  -MinMax Kinda OK
 *  -Alphabeta pruning /need to be coded
 *  -Less intensive posible moves funtions /ned to be coded
 *  -Initial moves /need to be coded
 *  -Optimize the movement funtions /need to be coded
 *  -Enroque largo y corto /need to be coded
 *  -Sistema de turnos OK
 *  
 */
