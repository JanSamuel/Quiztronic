#include <iostream>
#include <vector>

struct gamer
{
    std::string name;
    int points;
};

class Questions//function of this class is randomizing, loading, asking and checking questions
{
    std::string contents;
    std::string a,b,c,d;
    std::string answer_user, answer_correct, answer_temp;
    int field;
    int number_question;
public:
    void randomize();
    void open();
    void ask();
    int check();
    void foolproof_answer();
};

class Quiz// this class manages players, their number names and points. Also order in which players answer
{
    int gamers_num;
    std::vector<gamer> gamers;
public:
    void how_many_players();
    void game();
    void how_many_points();
};

void clear();//screen clearing function
