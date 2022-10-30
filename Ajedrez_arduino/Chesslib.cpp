#include "Chesslib.h"


/*-----------------------Chesslib-----------------------*/
bool move_piece_manager(int board[][8], int orig[], int dest[], bool *turn, bool *enpasant, int enpasant_cords[])//this funtion will manage how to move the pieces and if they are a legal move
{
  bool ficha_movida = false;
  int piece = board[orig[1]][orig[0]];

  if (*enpasant == true && board[enpasant_cords[1]][enpasant_cords[0]] > 0 && *turn == true)
  {
    *enpasant = false;
  }
  else if (*enpasant == true && board[enpasant_cords[1]][enpasant_cords[0]] < 0 && *turn == false)
  {
    *enpasant = false;
  }

  if (piece > 0 && *turn == true)
  {
    if (board[dest[1]][dest[0]] > 0)
    {
      if (turn == true)
      {
        /*Serial.println("No puedes pisar tus propias fichas");*/
      }
    }
    else
    {
      if (piece < 5)
      {
        if (piece == 1)
        {
          ficha_movida = white_pawn_moves(board, orig, dest, piece, enpasant, enpasant_cords);
        }
        else if (piece == 3)
        {
          ficha_movida = khight_moves(board, orig, dest, piece);
        }
        else
        {
          ficha_movida = bishop_moves(board, orig, dest, piece);
        }
      }
      else
      {
        if (piece == 5)
        {
          ficha_movida = rock_moves(board, orig, dest, piece);
        }
        else if (piece == 10)
        {
          ficha_movida = queen_moves(board, orig, dest, piece);
        }
        else
        {
          ficha_movida = king_moves(board, orig, dest, piece);
        }
      }
    }
    if (ficha_movida == true)
    {
      *turn = false;
    }
  }
  else if (piece < 0 && *turn == false)
  {
    if (board[dest[1]][dest[0]] < 0)
    {
      /*Serial.println("No puedes pisar tus propias fichas");*/
    }
    else
    {
      if (piece > -5)
      {
        if (piece == -1)
        {
          ficha_movida = black_pawn_moves(board, orig, dest, piece, enpasant, enpasant_cords);
        }
        else if (piece == -3)
        {
          ficha_movida = khight_moves(board, orig, dest, piece);
        }
        else
        {
          ficha_movida = bishop_moves(board, orig, dest, piece);
        }
      }
      else
      {
        if (piece == -5)
        {
          ficha_movida = rock_moves(board, orig, dest, piece);
        }
        else if (piece == -10)
        {
          ficha_movida = queen_moves(board, orig, dest, piece);
        }
        else
        {
          ficha_movida = king_moves(board, orig, dest, piece);
        }
      }
    }
    if (ficha_movida == true)
    {
      *turn = true;
      return true;
    }
  }
  else
  {
    //Serial.print("No puedes mover fichas de tu rival\n");
  }
  return false;
}

void move_piece(int board[][8], int orig[2], int dest[2], int piece)
{
  board[orig[1]][orig[0]] = 0;
  board[dest[1]][dest[0]] = piece;
  Serial.print("Ficha movida de : ");
  convert_to_nomenclature(orig[0], orig[1]);
  Serial.print(" a : ");
  convert_to_nomenclature(dest[0], dest[1]);
  Serial.print("\n");
}

void inputsanitize(int board[][8], bool *turn, bool *enpasant, int enpasant_cords[], bool *win)
{
  char str[4];
  char chareaded;
  int cont = 0;
  int orig[2];
  int dest[2];
  if (Serial.available() > 0)
  {
    if (Serial.available() - 1 != 4)
    {
      Serial.println("El comando esta mal, tiene o muy pocos o muchos caracteres");
      clean_buffer();
    }
    else
    {
      while (Serial.available() - 1)
      {
        chareaded = Serial.read();
        /*Serial.print("Caracterleido : ");
          Serial.println(chareaded);*/
        if (chareaded >= 'a' && chareaded <= 'h')
        {
          str[cont] = chareaded;
          cont++;
        }
        else if (chareaded >= '1' && chareaded <= '8')
        {
          str[cont] = chareaded;
          cont++;
        }
        else
        {
          Serial.println("Codigo incorrecto, seleciona una casilla correcta, entre los limites de \"1 a 8\" y de \"a hasta h\" ");
          clean_buffer();
          break;
        }
      }
      clean_buffer();
      convert_from_nomenclature(orig, str[0], str[1]);
      if (board[orig[1]][orig[0]] == 0)
      {
        Serial.print("Seleciona una casilla que contenga una ficha, la casilla ");
        convert_to_nomenclature(orig[0], orig[1]);
        Serial.println(" no contiene una ficha");
      }
      else
      {
        convert_from_nomenclature(dest, str[2], str[3]);
        bool moved = move_piece_manager(board, orig, dest, turn, enpasant, enpasant_cords);
        norme(board, win);
        print_board(board);
        Serial.print("Turno del jugador: ");
        if (*turn == true)
        {
          Serial.print("BLANCO\n");
        }
        else
        {
          Serial.print("NEGRO\n");
        }
      }
    }
  }
}

void norme(int board[][8], bool *win)
{
  *win = check_wins(board);
  make_queens(board);
}

/*---------------------ChessNorm-------------------------*/
bool check_wins(int board[][8])
{
  int suma_negativa = 0;
  int suma_positiva = 0;
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      if (board[j][i] > 0)
      {
        suma_positiva += board[j][i];
      }
      else if (board[j][i] < 0)
      {
        suma_negativa += abs(board[j][i]);
      }
    }
  }
  if (suma_negativa < 1000)
  {
    Serial.print("Las BLANCAS ganan\n");
    return true;
  }
  else if (suma_positiva < 1000)
  {
    Serial.print("Las NEGRAS ganan\n");
    return true;
  }
  return false;
}

void make_queens(int board[][8])
{
  for (int i = 0; i < 8; i++)
  {
    if (abs(board[0][i]) == 1)
    {
      if (board[0][i] > 0)
      {
        board[0][i] = 10;
      }
      else
      {
        board[0][i] = -10;
      }
    }
  }
  for (int i = 0; i < 8; i++)
  {
    if (abs(board[7][i]) == 1)
    {
      if (board[7][i] > 0)
      {
        board[7][i] = 10;
      }
      else
      {
        board[7][i] = -10;
      }
    }
  }
}



















/*------------------------ChessMoveslib-------------------------*/
bool white_pawn_moves(int board[][8], int orig[], int dest[], int piece, bool *enpasant, int enpasant_cords[])
{
  //falta el movimiento frances, pero en serio eso lo usa alguien? quiero decir, es frances. . .
  if (orig[1] == (dest[1] + 1))
  {
    if (board[dest[1]][dest[0]] == 0 && orig[0] == dest[0])
    {
      move_piece(board, orig, dest, piece);
    }
    else if ((orig[0] == (dest[0] + 1)) && ((board[dest[1]][dest[0]] != 0)))
    {
      move_piece(board, orig, dest, piece);
    }
    else if ((orig[0] == (dest[0] - 1)) && (board[dest[1]][dest[0]] != 0))
    {
      move_piece(board, orig, dest, piece);
    }
    else if (*enpasant == true)
    {
      Serial.print("Entro en enpasant\n");
      return enpasant_move(board, orig, dest, piece, enpasant, enpasant_cords);
    }
    else
    {
      Serial.print("No se puede mover el peon a la casilla de destino\n");
      return false;
    }
  }
  else if (orig[1] == (dest[1] + 2))
  {
    if (board[dest[1]][dest[0]] == 0 && orig[0] == dest[0] && board[(dest[1] + 1)][dest[0]] == 0 && orig[1] == 6)
    {
      move_piece(board, orig, dest, piece);
      *enpasant = true;
      enpasant_cords[0] = dest[0];
      enpasant_cords[1] = dest[1];
      /*
        Serial.print("En pasant?: ");
        Serial.println(*enpasant);
        Serial.print("Posición: ");
        convert_to_nomenclature(enpasant_cords[0], enpasant_cords[1]);
        Serial.print("\n");
      */
    }
    else
    {
      Serial.print("Hay piezas entre destino y origen\n");
      return false;
    }
  }
  else
  {
    Serial.print("No se puede mover el peon a la casilla de destino\n");
    return false;
  }
  return true;
}

bool black_pawn_moves(int board[][8], int orig[], int dest[], int piece, bool *enpasant, int enpasant_cords[])
{
  if (orig[1] == (dest[1] - 1))
  {
    if (board[dest[1]][dest[0]] == 0 && orig[0] == dest[0])
    {
      move_piece(board, orig, dest, piece);
    }
    else if ((orig[0] == (dest[0] - 1)) && (board[dest[1]][dest[0]] != 0))
    {
      move_piece(board, orig, dest, piece);
    }
    else if ((orig[0] == (dest[0] + 1)) && (board[dest[1]][dest[0]] != 0))
    {
      move_piece(board, orig, dest, piece);
    }
    else if (*enpasant == true)
    {
      Serial.print("Entro en enpasant\n");
      return enpasant_move(board, orig, dest, piece, enpasant, enpasant_cords);
    }
    else
    {
      return false;
    }
  }
  else if (orig[1] == (dest[1] - 2))
  {
    if (board[dest[1]][dest[0]] == 0 && orig[0] == dest[0] && board[(dest[1] - 1)][dest[0]] == 0 && orig[1] == 1)
    {
      move_piece(board, orig, dest, piece);
      *enpasant = true;
      enpasant_cords[0] = dest[0];
      enpasant_cords[1] = dest[1];
    }
    else
    {
      Serial.print("Hay piezas entre destino y origen\n");
      return false;
    }
  }
  else
  {
    Serial.print("No se puede mover el peon a la casilla de destino\n");
    return false;
  }
  return true;
}

bool khight_moves(int board[][8], int orig[], int dest[], int piece)
{
  if (orig[1] == (dest[1] + 2)) //se puede simplificar en una ecuación me he dado cuenta tarde :/
  {
    if (dest[0] == (orig[0] + 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
    else if (dest[0] == (orig[0] - 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
  }
  else if (orig[1] == (dest[1] - 2))
  {
    if (dest[0] == (orig[0] + 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
    else if (dest[0] == (orig[0] - 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
  }
  else if (orig[0] == (dest[0] + 2))
  {
    if (dest[1] == (orig[1] + 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
    else if (dest[1] == (orig[1] - 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
  }
  else if (orig[0] == (dest[0] - 2))
  {
    if (dest[1] == (orig[1] + 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
    else if (dest[1] == (orig[1] - 1))
    {
      move_piece(board, orig, dest, piece);
      return true;
    }
  }
  else
  {
    Serial.print("No puedes mover el caballo a esa casilla\n");
    return false;
  }
  return false;
}

bool rock_moves(int board[][8], int orig[], int dest[], int piece)
{
  bool errorflag = false;
  int diff;
  if (orig[1] == dest[1])
  {
    diff = orig[0] - dest[0];
    if (diff < 0)
    {
      for (int i = (abs(diff) - 1); i > 1; i--)
      {
        if (board[(orig[1])][orig[0] + i] != 0)
        {
          /*
            Serial.println("Bucle 1");
            Serial.print("Valor de i: ");
            Serial.println(i);
            Serial.print("Objetivo: ");
            Serial.print(orig[0] + i);
            Serial.println(orig[1]);
            convert_to_nomenclature(orig[0] + i,(orig[1]));
            Serial.print("\n");
            Serial.print("Casilla a imprimir: ");
            Serial.print(board[orig[1]][(orig[0] + i)]);
            Serial.print("\n");
          */
          Serial.println("Hay piezas entre el destino y el origen");
          errorflag = true;
          break;
        }
      }
      if (errorflag == false)
      {
        move_piece(board, orig, dest, piece);
        return true;
      }
      return false;
    }
    else if (diff > 0)
    {
      for (int i = (abs(diff) - 1); i > 1; i--)
      {
        if (board[(orig[1])][orig[0] - i] != 0)
        {
          /*
            Serial.println("Bucle 2");
            Serial.print("Valor de i: ");
            Serial.println(i);
            Serial.print("Objetivo: ");
            Serial.print(orig[0] - i);
            Serial.println(orig[1]);
            convert_to_nomenclature(orig[0] - i,(orig[1]));
            Serial.print("\n");
            Serial.print("Casilla a imprimir: ");
            Serial.print(board[orig[1]][(orig[0] - i)]);
            Serial.print("\n");
          */
          Serial.println("Hay piezas entre el destino y el origen");
          errorflag = true;
          break;
        }
      }
      if (errorflag == false)
      {
        move_piece(board, orig, dest, piece);
        return true;
      }
      return false;
    }
  }
  else if (orig[0] == dest[0])
  {
    diff = orig[1] - dest[1];
    if (diff < 0)
    {
      for (int i = (abs(diff) - 1); i >= 1; i--)
      {
        if (board[(orig[1] + i)][orig[0]] != 0)
        {
          /*
            Serial.println("Bucle 3");
            Serial.print("Valor de i: ");
            Serial.println(i);
            Serial.print("Objetivo: ");
            Serial.print(orig[0]);
            Serial.println(orig[1] + i);
            convert_to_nomenclature(orig[0],(orig[1] + i));
            Serial.print("\n");
            Serial.print("Casilla a imprimir: ");
            Serial.print(board[orig[1] + i][(orig[0])]);
            Serial.print("\n");
          */
          Serial.println("Hay piezas entre el destino y el origen");
          errorflag = true;
          break;
        }
      }
      if (errorflag == false)
      {
        move_piece(board, orig, dest, piece);
        return true;
      }
      return false;
    }
    else if (diff > 0)
    {
      for (int i = (abs(diff) - 1); i >= 1; i--)
      {
        if (board[(orig[1] - i)][orig[0]] != 0)
        {
          /*
            Serial.println("Bucle 4");
            Serial.print("Valor de i: ");
            Serial.println(i);
            Serial.print("Objetivo: ");
            Serial.print(orig[0]);
            Serial.println(orig[1] - i);
            convert_to_nomenclature(orig[0],(orig[1] - i));
            Serial.print("\n");
            Serial.print("Casilla a imprimir: ");
            Serial.print(board[orig[1] - i][(orig[0])]);
            Serial.print("\n");
          */
          Serial.println("Hay piezas entre el destino y el origen");
          errorflag = true;
          break;
        }
      }
      if (errorflag == false)
      {
        move_piece(board, orig, dest, piece);
        return true;
      }
      return false;
    }
  }
  else
  {
    Serial.print("La torre no se puede mover en diagonal");
  }
  return false;
}

bool bishop_moves(int board[][8], int orig[], int dest[], int piece)
{
  bool errorflag = false;
  int isodd = orig[0] + orig[1];
  int destodd = dest[0] + dest[1];
  int diff = orig[0] - dest[0];
  int diff_1 = orig[1] - dest[1];
  Serial.print("diff: ");
  Serial.println(diff);
  if (isodd % 2 == 1)//Hay un error con el tablero por lo que los pares son los que equivales al modulo de 2 == 1, no 0
  {
    /*
      Serial.print("Condicion 1: ");
      Serial.print(orig[0] - diff);
      Serial.print(" igual a: ");
      Serial.println(dest[0]);
      Serial.print("Condicion 1: ");
      Serial.print(orig[1] - diff);
      Serial.print(" igual a: ");
      Serial.println(dest[1]);
    */
    if (destodd % 2 == 1 && (orig[0] - diff) == dest[0] && (orig[1] - diff_1) == dest[1])
    {
      //DEBUGGIN UTIL
      /*
        Serial.print("Valor de diff_0: ");
        Serial.println(diff);
        Serial.print("Valor de diff_1: ");
        Serial.println(diff_1);
      */
      if (diff < 0 && diff_1 < 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          /*
            Serial.print("Indice de la casilla a chekear: ");
            convert_to_nomenclature(orig[0] + i, orig[1] + i);
            Serial.print('\n');7
          */
          if (board[(orig[1] + i)][(orig[0] + i)] != 0)
          {
            /*
              Serial.println("Bucle 1");
              Serial.print("Valores de x e y: ");
              Serial.print(orig[0] + i);
              Serial.println(orig[1] + i);
              Serial.print("Numero odd? ");
              Serial.println(isodd + 1);
              Serial.println("Es par");
              Serial.print("Valor de la casilla: ");
              Serial.println(board[orig[1] + i][orig[0] + i]);
            */
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff > 0 && diff_1 > 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          /*
            Serial.print("Indice de la casilla a chekear: ");
            convert_to_nomenclature(orig[0] + i, orig[1] + i);
            Serial.print('\n');7
          */
          if (board[(orig[1] - i)][(orig[0] - i)] != 0)
          {
            /*
              Serial.println("Bucle 2");
              Serial.print("Valores de x e y: ");
              Serial.print(orig[0] + i);
              Serial.println(orig[1] + i);
              Serial.print("Numero odd? ");
              Serial.println(isodd + 1);
              Serial.println("Es par");
              Serial.print("Valor de la casilla: ");
              Serial.println(board[orig[1] + i][orig[0] + i]);
            */
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff > 0 && diff_1 < 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          if (board[(orig[1] + i)][(orig[0] - i)] != 0)
          {
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff < 0 && diff_1 > 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          if (board[(orig[1] - i)][(orig[0] + i)] != 0)
          {
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
    }
    else
    {
      Serial.print("No puedes mover un alfil a una casilla que no sea de su color\n");
    }
  }
  else if (isodd % 2 == 0)
  {
    /*
      Serial.print("Condicion 1: ");
      Serial.print(orig[0] - diff);
      Serial.print(" igual a: ");
      Serial.println(dest[0]);
      Serial.print("Condicion 1: ");
      Serial.print(orig[1] - diff);
      Serial.print(" igual a: ");
      Serial.println(dest[1]);
      Serial.print("Valor de diff_0: ");
      Serial.println(diff);
      Serial.print("Valor de diff_1: ");
      Serial.println(diff_1);
    */
    if (destodd % 2 == 0 && (orig[0] - diff) == dest[0] && (orig[1] - diff_1) == dest[1])
    {
      if (diff < 0 && diff_1 < 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          //DEBUGGIN UTIL
          /*
            Serial.print("Indice de la casilla a chekear: ");
            convert_to_nomenclature(orig[0] + i, orig[1] + i);
            Serial.print('\n');
          */
          if (board[(orig[1] + i)][(orig[0] + i)] != 0)
          {
            /*
              Serial.println("Bucle 1");
              Serial.print("Valores de x e y: ");
              Serial.print(orig[0] + i);
              Serial.println(orig[1] + i);
              Serial.print("Numero odd? ");
              Serial.println(isodd + 1);
              Serial.println("Es par");
              Serial.print("Valor de la casilla: ");
              Serial.println(board[orig[1] + i][orig[0] + i]);
            */
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff > 0 && diff_1 > 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          if (board[(orig[1] - i)][(orig[0] - i)] != 0)
          {
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff > 0 && diff_1 < 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          if (board[(orig[1] + i)][(orig[0] - i)] != 0)
          {
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
      else if (diff < 0 && diff_1 > 0)
      {
        for (int i = (abs(diff) - 1); i > 1; i--)
        {
          if (board[(orig[1] - i)][(orig[0] + i)] != 0)
          {
            errorflag = true;
            Serial.println("Hay piezas entre el destino y el origen");
            break;
          }
        }
        if (errorflag == false)
        {
          move_piece(board, orig, dest, piece);
        }
      }
    }
  }
  /*
    else
    {
    if (destodd % 2 == 0)
    {

    }
    else
    {
      Serial.print("No puedes mover un alfil a una casilla que no sea de su color\n");
    }
    Serial.print("Valores de x e y: ");
    Serial.print(orig[0]);
    Serial.println(orig[1]);
    Serial.print("Numero odd? ");
    Serial.println(isodd);
    Serial.println("Es impar");
    }
  */
  if (errorflag == false)
    return true;
  return false;
}

bool queen_moves(int board[][8], int orig[], int dest[], int piece)
{
  bool resultado;
  int diff_0 = orig[0] - dest[0];
  int diff_1 = orig[1] - dest[1];
  if (diff_0 == 0 || diff_1 == 0)
  {
    resultado = rock_moves(board, orig, dest, piece);
  }
  else
  {
    resultado = bishop_moves(board, orig, dest, piece);
  }
  return resultado;
}

bool king_moves(int board[][8], int orig[], int dest[], int piece)
{
  int diff_0 = orig[0] - dest[0];
  int diff_1 = orig[1] - dest[1];

  if ((abs(diff_0) == 1 || diff_0 == 0) && (diff_1 == 0 || abs(diff_1) == 1))
  {
    move_piece(board, orig, dest, piece);
    return true;
  }
  else
  {
    Serial.print("No puedes mover el rey hay, hay más de 1 casilla de diferencia\n");
  }
  return false;
}

bool enpasant_move(int board[][8], int orig[], int dest[], int piece, bool enpasant, int enpasant_cords[])
{
  if (enpasant == true)
  {
    if (enpasant_cords[0] == dest[0] && enpasant_cords[0] == orig[0] - 1)
    {
      board[enpasant_cords[1]][dest[0]] = 0;
      move_piece(board, orig, dest, piece);
      return true;
    }
    else if (enpasant_cords[0] == dest[0] && enpasant_cords[0] == orig[0] + 1)
    {
      board[enpasant_cords[1]][dest[0]] = 0;
      move_piece(board, orig, dest, piece);
      return true;
    }
    else
    {
      Serial.print("No puedes capturar al paso en esa casilla\n");
    }
  }
  else
  {
    Serial.print("Captura al paso no disponible\n");
  }
  return false;
}




















/*---------------------ChessLibSerialPrint----------------------*/
void print_board(int board[][8]) //Imprime el tablero de una manera legible
{
  Serial.println("----------------------------------");
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 9; i++)
    {
      if (i == 0)
      {
        Serial.print(POSITIONS[j]);
        Serial.print(" ");
      }
      else
      {
        Serial.print("|");
        print_piece(board[j][i - 1]);
        Serial.print("|");
      }
    }
    Serial.print("\n");
    Serial.println("----------------------------------");
  }
  Serial.println("   a   b   c   d   e   f   g   h");
}

void print_piece(int piece)
{
  if (piece > 0) {
    if (piece > 4)//No esta balanceado
    {
      if (piece == 1000)
        Serial.print(WHITEKING);
      else if (piece == 5)
        Serial.print(WHITEROCK);
      else
        Serial.print(WHITEQUEEN);
    }
    else if (piece < 4)
    {
      if (piece == 3)
        Serial.print(WHITEKNIGHT);
      else
        Serial.print(WHITEPAWN);
    }
    else
      Serial.print(WHITEBISHOP);
  }
  else if (piece < 0) {
    if (piece < -4)
    {
      if (piece == -1000)
        Serial.print(BLACKKING);
      else if (piece == -5)
        Serial.print(BLACKROCK);
      else
        Serial.print(BLACKQUEEN);
    }
    else if (piece > -4)
    {
      if (piece == -3)
        Serial.print(BLACKKNIGHT);
      else
        Serial.print(BLACKPAWN);
    }
    else
      Serial.print(BLACKBISHOP);
  }
  else
    Serial.print("  ");
}

void convert_to_nomenclature(int digit1, int digit2)
{
  Serial.print(POSITIONS2[digit1]);
  Serial.print(8 - (digit2));
}

void convert_from_nomenclature(int cords[], char char1, char char2)
{
  for (int i = 0; i < 8; i++)
  {
    if (POSITIONS2[i] == char1)
    {
      cords[0] = i;
    }
  }
  cords[1] = 8 - (char2 - 48);
}


/*--------------------Utilitys------------------------------*/
void clean_buffer()
//Due to flush not longer cleaning the data in the serial buffer,
//at least this is what the documentation says and what the HardwereSerial.cpp file says
{
  while (Serial.available() > 0)
  {
    Serial.read();
  }
}

void copy_board_fun(int source[][8], int copy[][8])//copy the board in an alternative board, to check for "checks"
{
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      copy[j][i] = source[j][i];
    }
  }
}


/*---------------------MinMax------------------------------*/
int set_score(int board[][8])
{
  int score = 0;
  for (int j = 0; j < 8; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      score += board[j][i];
    }
  }
}

int minimax(int board[][8], int depth, bool isMaxi, bool *enpasant, int enpasant_cords[], int best_move[])
{
  bool moved = false;
  int piece;
  int piece_eaten;
  int orig[2] = {0, 0};
  int dest[2] = {0, 0};
  int bestScore = 0;
  int score;
  bool isEndState = check_wins(board);
  if (isEndState == true)
  {
    score = set_score(board);
    return score; 
  }
  if (isMaxi == true)
  {
    bestScore = -10000;
    for (int l = 0; l < 8; l++)
    {
      orig[0] = l;
      for (int k = 0; k < 8; k++)
      {
        orig[1] = k;
        for (int j = 0; j < 8; j++)
        {
          dest[0] = j;
          for (int i = 0; i < 8; i++)
          {
            dest[1] = i;
            if (depth < 3)
            {
              piece_eaten = board[dest[1]][dest[0]];
              moved = move_piece_manager(board, orig, dest, &isMaxi, enpasant, enpasant_cords);
              score = minimax(board, depth + 1, false, enpasant, enpasant_cords, best_move);
              if (moved == true)
              {
                piece = board[dest[1]][dest[0]];
                board[dest[1]][dest[0]] = piece_eaten;
                board[orig[1]][orig[0]] = piece;
              }
            }
            if (score > bestScore)
            {
              bestScore = score;
              best_move[0] = l;
              best_move[1] = k;
              best_move[2] = j;
              best_move[3] = i;
            }
          }
        }
      }
    }
    return bestScore;
  }
  else if (isMaxi == false)
  {
    bestScore = 10000;
    for (int l = 0; l < 8; l++)
    {
      orig[0] = l;
      for (int k = 0; k < 8; k++)
      {
        orig[1] = k;
        for (int j = 0; j < 8; j++)
        {
          dest[0] = j;
          for (int i = 0; i < 8; i++)
          {
            if (depth < 3)
            {
              piece_eaten = board[dest[1]][dest[0]];
              moved = move_piece_manager(board, orig, dest, &isMaxi, enpasant, enpasant_cords);
              score = minimax(board, depth + 1, true, enpasant, enpasant_cords, best_move);
              if (moved == true)
              {
                piece = board[dest[1]][dest[0]];
                board[dest[1]][dest[0]] = piece_eaten;
                board[orig[1]][orig[0]] = piece;
              } 
            }
            if (score < bestScore)
            {
              bestScore = score;
              best_move[0] = l;
              best_move[1] = k;
              best_move[2] = j;
              best_move[3] = i;
            }
          }
        }
      }
    }
    return bestScore;
  }
}
