#include <bits/stdc++.h>
using namespace std;

class TicTacToe
{
private:
    /* data */
public:
    TicTacToe(/* args */);
    ~TicTacToe();
};

TicTacToe::TicTacToe(/* args */)
{
}

TicTacToe::~TicTacToe()
{
}


class Player{
    private : 
    string name;
    char symbol;
    public:
    Player(string name, char symbol){
        this->name = name;
        this->symbol = symbol;
    }

    string getName(){
        return this->name;
    }

    char getSymbol(){
        return this->symbol;
    }
};



