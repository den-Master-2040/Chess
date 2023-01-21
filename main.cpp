#include <iostream>
#include <stdio.h>
using namespace  std;

void hod(int figure, int user_hod); //главная функция, вызывающая функцию хода конкретной фигуры.
void print_chess_map();             //вывод
void peshka_hod(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
void hod_ladya(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
bool proverka_ladya(int figure_i, int figure_j, int user_hod_i, int user_hod_j); //проверка,может ли сходить ладья - пустота ли впереди
void hod_konb(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
int chess_map[8][8] =
        {
                {2, 3, 4, 5, 6, 4, 3, 2},
                {1, 1, 1, 1, 1, 1, 1, 1},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {7, 7, 7, 7, 7, 7, 7, 7},
                {8, 9,10,11,12,10, 9, 8}
        };
int main() {
    auto figure = 00;
    auto user_hod = 00;

    while(user_hod != -99)
    {
        print_chess_map();
        cout <<"Первым числом введите фигуру, которую хотите передвинуть, а второй - куда передвинуть.";
        cin >> figure;
        cin >> user_hod;
        hod(figure,user_hod);
        //system("clear");
    }

    return 0;
}

void hod(int figure, int user_hod)
{
    //получаем координаты
    int figure_i = figure / 10;
    int figure_j = figure % 10;
    int user_hod_i = user_hod /10;
    int user_hod_j = user_hod % 10;

    /*  ПЕШКА   */
    if(chess_map[figure_i][figure_j] == 1)                //если игрок выбрал пешку за белых
        peshka_hod( figure_i, figure_j, user_hod_i, user_hod_j, 1);

    if(chess_map[figure_i][figure_j] == 7)                //если игрок выбрал пешку за черных
        peshka_hod( figure_i, figure_j, user_hod_i, user_hod_j, -1);
    /*  СЛОН   */
    if(chess_map[figure_i][figure_j] == 2)                //если игрок выбрал слона за белых
        hod_ladya( figure_i, figure_j, user_hod_i, user_hod_j, 1);

    if(chess_map[figure_i][figure_j] == 8)                //если игрок выбрал слона за черных
        hod_ladya( figure_i, figure_j, user_hod_i, user_hod_j, -1);
    /*  КОНЬ   */
    if(chess_map[figure_i][figure_j] == 3)                //если игрок выбрал слона за белых
        hod_konb( figure_i, figure_j, user_hod_i, user_hod_j, 1);

    if(chess_map[figure_i][figure_j] == 9)                //если игрок выбрал слона за черных
        hod_konb( figure_i, figure_j, user_hod_i, user_hod_j, -1);
}

void print_chess_map()
{
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            cout << chess_map[i][j] << "\t";
        cout << endl;
    }
}

void peshka_hod(int figure_i, int figure_j,
                int user_hod_i, int user_hod_j, int player)
{
    //ход на пустую клетку
    if(figure_i + player == user_hod_i &&
       chess_map[user_hod_i][user_hod_j] == 0)           //если он сделал шаг вниз на пустую клетку
    {
        swap(chess_map[figure_i][figure_j],
             chess_map[user_hod_i][user_hod_j]);   //меняем местами, то есть делаем ход
    }
    //ход с атакой
    else if (figure_i + player == user_hod_i &&                      //если ход делается вниз
             (figure_j + 1 == user_hod_j||figure_j - 1 == user_hod_j )&& //при этом вправо или влево
             chess_map[user_hod_i][user_hod_j] != 0)            //и не на пустую клетку
    {
        swap(chess_map[figure_i][figure_j],
             chess_map[user_hod_i][user_hod_j]); //значит мы делаем атаку
        chess_map[figure_i][figure_j] = 0;           // уничтожаем вражескую фигуру
    }
    //проверка на край доски
    if(player == 1)
    //если пешка дошла до края доски, она должна стать ладьёй.
    {
        if (user_hod_i == 7) chess_map[user_hod_i][user_hod_j] = 5;
    }
    else if(user_hod_i == 0) chess_map[user_hod_i][user_hod_j] = 11;
}

void hod_ladya(int figure_i, int figure_j,
                int user_hod_i, int user_hod_j, int player)
{
    if((figure_i == user_hod_i || figure_j == user_hod_j) && proverka_ladya(figure_i, figure_j,
            user_hod_i, user_hod_j)) {
        swap(chess_map[figure_i][figure_j],
             chess_map[user_hod_i][user_hod_j]);   //меняем местами, то есть делаем ход
        if (chess_map[user_hod_i][user_hod_j] != 0)//если он сделал шаг не на пустую клетку
        {
            chess_map[figure_i][figure_j] = 0;
        }

    }
}

bool proverka_ladya(int figure_i, int figure_j,
                    int user_hod_i, int user_hod_j)
{
    if(figure_i != user_hod_i)
    {
        if (figure_i < user_hod_i)
        for (int i =figure_i + 1; i < user_hod_i; i++) {
            if (chess_map[i][figure_j] != 0) return false;
        }
        if (figure_i > user_hod_i)
            for (int i =user_hod_i + 1; i < figure_i; i++) {
                if (chess_map[i][figure_j] != 0) return false;
            }
    } else if(figure_j != user_hod_j)
    {
        if (figure_j < user_hod_j)
        {
            for (int j = figure_j+1; j < user_hod_j; j++) {
                if (chess_map[figure_i][j] != 0) return false;
            }
        } else if (figure_j > user_hod_j)
        {
            for (int j = user_hod_j+1; j < figure_j; j++) {
                if (chess_map[figure_i][j] != 0) return false;
            }
        }
    }
    return true;
}
void hod_konb(int figure_i, int figure_j,
              int user_hod_i, int user_hod_j, int player)
{
    if((figure_i == user_hod_i + 2 || figure_i == user_hod_i - 2)&&((figure_j == user_hod_j + 1 || figure_j == user_hod_j - 1)))
        if(chess_map[user_hod_i][user_hod_j] !=0)
        {
            chess_map[user_hod_i][user_hod_j] = 0;
            swap(chess_map[figure_i][figure_j],
                 chess_map[user_hod_i][user_hod_j]);
        }
        else swap(chess_map[figure_i][figure_j],
                 chess_map[user_hod_i][user_hod_j]);

}