#include <iostream>
#include "quiz.h"

int main()
{
std::cout<<"Hello \nthis is Quiztronic 3000 game made for you to play with your friends \non one computer like old times with 'hot seat'"<<std::endl;
std::srand((unsigned int)time(0));
Quiz game;
game.how_many_players();
game.game();
return 0;
}
