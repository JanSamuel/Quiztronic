#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "quiz.h"

void Quiz::how_many_players()//function asking about number of player and their in game names
{
    std::cout << "Enter the number of players"<<std::endl;
    std::cin>>gamers_num;
    if(!std::cin)
    {
        std::cin.clear();
        std::cin.ignore();
        std::cout<< "Pleas enter positive number"<<std::endl;
        how_many_players();
    }
    else
    {
        gamers.resize(gamers_num);
        for(int i=0;i<gamers_num;i++)
        {
            std::string name;
            std::cout<<"name of player :"<<i+1<<std::endl;
            std::cin>>name;
            gamers[i].name=name;
            gamers[i].points=0;
        }
    }
    clear();
}

void Quiz::game()
{
    Questions quest;
    int num_asked=5;//number of qestion each player is asked during one game
    for (int i=0;i<num_asked;i++)//this loop indicates number of questions each player will be asked
    {
        for (int j=0;j<gamers_num;j++)
        {
            std::cout<< "Gamer "<<gamers[j].name<<" question: "<<std::endl;
            quest.randomize();
            quest.open();
            quest.ask();
            quest.foolproof_answer();
            gamers[j].points+=quest.check();
            clear();
        }
        how_many_points();
    }
}

void Quiz::how_many_points()
{
    for (int i=0;i<gamers_num;i++)
    {
        std::cout<<"Gamer "<<gamers[i].name<<" have "<<gamers[i].points<<" points"<<std::endl;
    }
    std::cin.get();
    std::cin.ignore();
    clear();
}

void Questions::randomize()//function that draws the field and the question 
{
    int num_fields=4;//number of fildes
    field=rand()%num_filds;
    //this is sort of template so I didn't put any real ones like
    switch (field)
    {
    case 0:
        std::cout<<"thing 1 "<<std::endl;
        break;
    case 1:
        std::cout<<"another field "<<std::endl;
        break;
    case 2:
        std::cout<<" you can create as many "<<std::endl;
        break;
    case 3:
        std::cout<<" as you need "<<std::endl;
        break;
    default:
        randomize();
    }
    int qeustion_pool=5;//number of qestion in each field minus 1
    number_question=rand()%qeustion_pool+1;
}

void Questions::open()
{
    
    std::fstream file;//for this part you need files with questions in the same folder as my game executable file is created
    //files have to be txt format and have specific construction
    //the content of question
    //4 lines with answers
    //correct answer as small letter like "a","b"up to "d"
    //example:
    //Do you like trains?
    //yes
    //no
    //oranges
    //I like trains
    //d
    switch (field)// each file in this switch contains one field of questions
    {
    case 0:
        file.open("1.txt", std::ios::in);
        break;
    case 1:
        file.open("2.txt", std::ios::in);
        break;
    case 2:
        file.open("3.txt", std::ios::in);
        break;
    case 3:
        file.open("4.txt", std::ios::in);
        break;
    case 4:
        file.open("5.txt", std::ios::in);
        break;
    }
    if(!file.good())
    {
        std::cout<<"file not acquired";//error if file is not in folder or doesn't exist, this error terminates game.
        std::exit(0);
    }
    else
    {
        int number_lines=1;
        int number_line_now=(number_question-1)*6+1;//number of line in which specific question begins.
        std::string line;
        while(getline(file,line))
        {
            if(number_lines==number_line_now) contents=line;
            if(number_lines==number_line_now+1) a=line;
            if(number_lines==number_line_now+2) b=line;
            if(number_lines==number_line_now+3) c=line;
            if(number_lines==number_line_now+4) d=line;
            if(number_lines==number_line_now+5) answer_correct=line;
            number_lines++;
        }
        file.close();
    }
}

int Questions::check()//simple check if answer is correct, i wonder if it can be made without if
{
    if(answer_user==answer_correct)
    {
        return 1;
    }
    else
    {
        std::cout<<"wrong answer"<<std::endl;
        return 0;
    }
}

void Questions::ask()//this method reads out question loaded from file
{
    std::cout<<contents<<std::endl;
    std::cout<<a<<std::endl;
    std::cout<<b<<std::endl;
    std::cout<<c<<std::endl;
    std::cout<<d<<std::endl;
    std::cout<<"____________________________________"<<std::endl;
    std::cout<<"answer?"<<std::endl;
    std::cin>>answer_temp;
    foolproof_answer();
    clear();
}

void Questions::foolproof_answer()//foolproof method in case of using big letters or wrong character at all
{
    if (answer_temp=="a"||answer_temp=="A")
    {
        answer_user="a";
    }
    else if (answer_temp=="b"||answer_temp=="B")
    {
        answer_user="b";
    }
    else if (answer_temp=="c"||answer_temp=="C")
    {
        answer_user="c";
    }
    else if (answer_temp=="D"||answer_temp=="d")
    {
        answer_user="d";
    }
    else
    {
        std::cout<<"wrong character"<<std::endl;
        std::cout<<"allowed character are :"<<std::endl;
        std::cout<<" a  b  c  d"<<std::endl;
        open();//after using wrong character it loads the same question
        ask();
        foolproof_answer();
        check();
    }
}

void clear()
{
    printf("\e[1;1H\e[2J");
}
