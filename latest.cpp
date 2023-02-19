// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: T11L
// Names: CHAI DI SHENG | LEONG JIA YI
// IDs: 1211101961 | 1211101506
// Emails: 1211101961@student.mmu.edu.my | 1211101506@student.mmu.edu.my
// Phones: 0108940336 |  0179882201
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <cmath>
#include <conio.h> //for getch()

using namespace std;
class Zombie;

int MovementState = 0;
int AlienHit = 0;
int GameState = 1; // Alien turn = 1, zombie turn = 11-19, alien wins = 3, alien loses = 4, quit = 5
int CommandState = 0; // 
int nzombie = 0; // save number of zombies 
int zombieAlive = 0; // save number of zombie alive
int nrow = 0; //  save number of rows
int ncolumn = 0; // save number of columns  

class Board
{
private:
    int dimX_, dimY_;
public:
    Board(); //Defult Board Settings
    Board(int dimX, int dimY);  
    
    void init(int dimX, int dimY);            
    void display() const;

    int getDimX() const;
    int getDimY() const;

    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);

    bool isEmpty(int x, int y) const; 
    bool InBoard(int x, int y) const;

    vector<vector<char>> map_; // convention to put trailing underscore
};

Board::Board()      
{
    int dimX = 9;
    int dimY = 5;
    init(dimX, dimY);
}

Board::Board(int dimX, int dimY)
{
    init(dimX, dimY);
}

int Board::getDimX() const 
{
    return dimX_;
}

int Board::getDimY() const
{
    return dimY_;
}

void Board::init(int dimX, int dimY)
{
    dimX_ = dimX;
    dimY_ = dimY;
	char objects[] = {' ', ' ', ' ', ' ', '<', '>', '^', 'h', 'r', 'p', 'v'};
    int noOfObjects = 10; // number of objects in the objects array
    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }
    // place random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void Board::display() const
{
    system("cls");
    cout << "   ";
    if (dimX_ > 9)
    {
        int x = dimX_ - 9;
        for (int i = 0; i < x; ++i)
        {
            cout << " ";
        }
    }
    cout << "  .:Alien vs Zombie :.      " << endl;
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setw(2) << (dimY_ - i) << " ";
        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "   ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "  ";
    if (dimX_ > 9)
    {
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            int digit = (j + 1) / 10;
            cout << " ";
            if (digit == 0)
                cout << " ";
            else
                cout << digit;
        }
        cout << endl;
        cout << "   ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
    }
    else
    {
        cout << " ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << " " << (j + 1) % 10;
        }
    }
    cout << endl
         << endl;    
}

char Board::getObject(int x, int y) const
{
    return map_[dimY_ - y][x - 1];
}

void Board::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}

bool Board::isEmpty(int x, int y) const
{
    return map_[dimY_ - y][x - 1] == ' ';
}

bool Board::InBoard(int x, int y) const
{
    return x && y && dimX_ - x + 1 && dimY_ - y + 1;
}

class Alien
{
private:
    char symbol;
    char trail;
    int x_, y_;
    int hp_, atk_;

public:
    Alien();
    Alien(int x, int y,char chAlien);
    
    int getX() const;
    int getY() const;
    int getHp() const;
    int getAtk() const;

    void setXY(int x, int y);
    void setHp(int hp);
    void setAtk(int atk);
    void setAlien(int x, int y, Board &game);

    void alienMovement(Board &game);
    void alienCheck(Board &game);
    void alienAction(Board &game);
    
};

Alien::Alien(int x, int y, char chAlien) // create object Alien and specify its coordinates
{
    symbol = chAlien;
    trail = '.';
    x_ = x;
    y_ = y;
    hp_ = 100;
    atk_ = 0;
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

int Alien::getHp() const
{
    return hp_;
}

void Alien::setHp(int hp)
{
    hp_ = hp;
}

int Alien::getAtk() const
{
    return atk_;
}

void Alien::setXY(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Alien::setAtk(int atk)
{
    atk_ = atk;
}

void Alien::setAlien(int x, int y, Board &game)
{
    x_ = x;
    y_ = y;
    game.setObject(x, y, symbol);
}

void Alien::alienMovement(Board &game)
{
    game.setObject(x_, y_, trail);

    switch (MovementState)
    {
        case 1: // up
            y_++;
            setAlien(x_, y_, game);
            break;
        case 2: // down
            y_--;
            setAlien(x_, y_, game);
            break;
        case 3: // left
            x_--;
            setAlien(x_, y_, game);
            break;
        case 4: // right
            x_++;
            setAlien(x_, y_, game);
            break;
    }
}

void Alien::alienCheck(Board &game)
{
    int x = x_;
    int y = y_;

    switch (MovementState)
    {
        case 1: // up
            y++;
            break;
        case 2: // down
            y--;
            break;
        case 3: // left
            x--;
            break;
        case 4: // right
            x++;
            break;
    }

    if (game.InBoard(x, y)) // if inside the board
    {
        char objEncounter = game.getObject(x, y);

        switch (objEncounter)
        {
            case ' ':
            case '.':
                AlienHit = 11; // discover space or trail
                break;
            case 'h':
                AlienHit = 12; // discover health pack
                break;
            case 'p':
                AlienHit = 13; // discover pod
                break;
            case 'r':
                AlienHit = 14; // discover rock
                break;
            case '^':
                AlienHit = 15; // discover up arrow 
                break;
            case 'v':
                AlienHit = 16; // discover down arrow 
                break;
            case '<':
                AlienHit = 17; // discover left arrow 
                break;
            case '>':
                AlienHit = 18; // discover right arrow 
                break;
            // encounters zombie 1-9
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7': 
            case '8':
            case '9':
                AlienHit = 21;
                break;   
        }
    }
    else // if out of the board
    {
        AlienHit = 19; // hit border
    }

}

class Zombie
{
private:
    char symbol;
    int x_, y_;
    int hp_, atk_, range_;

public:
    Zombie();

    char getSymbol() const;
    int getX() const;
    int getY() const;
    int getHp() const;
    int getAtk() const;
    int getRange() const;

    void setSymbol(char ch);
    void setX(int x);
    void setY(int y);
    void setHp(int hp);
    void setAtk(int atk);
    void setRange(int range);
    void setZombie(int x, int y, Board &game);

    void MoveUp(Board& game);
    void MoveDown(Board& game);
    void MoveLeft(Board& game);
    void MoveRight(Board& game);

    void movement(Board& game, Alien& alien);
    void attack(Alien& alien);
};

Zombie zombie[10];

Zombie::Zombie()
{
    hp_ = (rand() % 5 + 2) * 50; 
    atk_ = (rand() % 5 + 1) * 5;
    range_ = rand() % 3 + 1;
}

char Zombie::getSymbol() const
{
    return symbol;
}

int Zombie::getX() const
{
    return x_;
}

int Zombie::getY() const
{
    return y_;
}

int Zombie::getHp() const
{
    return hp_;
}

int Zombie::getAtk() const
{
    return atk_;
}

int Zombie::getRange() const
{
    return range_;
}

void Zombie::setSymbol(char ch)
{
    symbol = ch;
}

void Zombie::setX(int x)
{
    x_ = x;
}

void Zombie::setY(int y)
{
    y_ = y;
}

void Zombie::setHp(int hp)
{
    hp_ = hp;
}

void Zombie::setAtk(int atk)
{
    atk_ = atk;
}

void Zombie::setRange(int range)
{
    range_ = range;
}

void Zombie::setZombie(int x, int y, Board &game)
{
    x_ = x;
    y_ = y;
    game.setObject(x, y, symbol);
}

void Zombie::MoveUp(Board &game)
{
    game.setObject(x_, y_, ' ');
    int y = y_ + 1;
    setZombie(x_, y, game); // set zombies
}

void Zombie::MoveDown(Board &game)
{
    game.setObject(x_, y_, ' ');
    int y = y_ - 1;
    setZombie(x_, y, game); // set zombies
}

void Zombie::MoveLeft(Board &game)
{
    game.setObject(x_, y_, ' ');
    int x = x_ - 1;
    setZombie(x, y_, game); // set zombies
}

void Zombie::MoveRight(Board &game)
{
    game.setObject(x_, y_, ' ');
    int x = x_ + 1;
    setZombie(x, y_, game); // set zombies
}

void Zombie::movement(Board& game, Alien& alien)
{
    int alienX, alienY;

    bool left = false;
    bool right = false;
    bool up = false;
    bool bottom = false;

    alienX = alien.getX();
    alienY = alien.getY();

    // Check zombie is beside border and beside alien
    if (x_ == 1 || alienX == x_ - 1 && alienY == y_)
    {
        // Border or alien at the left
        left = true;
    }
    else if (x_ == game.getDimX() || alienX == x_ + 1 && alienY == y_)
    {
        // Border or alien at the right
        right = true;
    }
    else if (y_ == 1 || alienX == x_ && alienY == y_ + 1)
    {
        // Border or alien at the top
        up = true;
    }
    else if (y_ == game.getDimY() || alienX == x_ && alienY == y_ - 1)
    {
        // Border or alien at the bottom
        bottom = true;
    }

    // Random zombie movement
    int random = rand() % 10;
    if (random < 2)
    {
        // Zombie randomly walk
        int random = rand() % 4;
        bool flag = false;

        if (random == 0 && !up)
        {
            MoveUp(game);
            cout << "Zombie " << symbol << "moves up." << endl;
            flag = true;
        }
        else if (random == 1 && !bottom)
        {
            MoveDown(game);
            cout << "Zombie " << symbol << " moves down." << endl;
            flag = true;
        }
        else if (random == 2 && !left)
        {
            MoveLeft(game);
            cout << "Zombie " << symbol << " moves left." << endl;
            flag = true;
        }
        else if (random == 3 && !right)
        {
            MoveRight(game);
            cout << "Zombie " << symbol << " moves right." << endl;
            flag = true;
        }
    }
    else if (random > 2)
    {
        random = rand() % 2;
        if (random == 1)
        {
            // Vertical
            if (alienY > y_ && !up)
            {
                MoveUp(game);
                cout << "Zombie " << symbol << " moves up." << endl;
            }
            else if (alienY < y_ && !bottom)
            {
                MoveDown(game);
                cout << "Zombie " << symbol << " moves down." << endl;
            }
        }
        else
        {
            // Horizontal
            if (alienX > x_ && !right)
            {
                MoveRight(game);
                cout << "Zombie " << symbol << " moves right." << endl;
            }
            else if (alienX < x_ && !left)
            {
                MoveLeft(game);
                cout << "Zombie " << symbol << " moves left." << endl;
            }
        }
    }
    cout << endl;
}

void Zombie::attack(Alien& alien)
{
    int alienX = alien.getX();
    int alienY = alien.getY();

    // Check if alien is in range
    if (alienX >= x_ - range_ && alienY == y_ || alienX <= x_ + range_ && alienY == y_ || 
        alienX == x_  && alienY >= y_ - range_|| alienX == x_ && alienY <= y_ + range_)
    {
        // Attack Alien
        cout << "Zombie " << symbol << " attacks Alien." << endl;
        int alienHp = alien.getHp();
        alienHp -= atk_;
        if (alienHp <= 0)
        {
            alien.setHp(0);
            cout << "Alien died." << endl;
            GameState = 4;
        }
        else
        {
            alien.setHp(alienHp);
            cout << "Alien survives from the attack." << endl;
        }
    }
    else 
    {
        cout << "Zombie " << symbol << " is unable to attack alien." << endl
             << "Alien not within range of zombie " << symbol << "." << endl;
    }
    cout << endl;
}

void Alien::alienAction(Board &game)
{
    switch (AlienHit)
    {
        case 11: // Alien discover space or trail
        {
            cout << "Alien encounters nothing." << endl;

            switch (MovementState)
            {
            case 1: // up
                    cout << "Alien moves up." << endl;
                    break;
            case 2: // down
                    cout << "Alien moves down." << endl;
                    break;
            case 3: // left
                    cout << "Alien moves left." << endl;
                    break;
            case 4: // right
                    cout << "Alien moves right." << endl;
                    break;
            }
            alienMovement(game);
            break;
        }
        
        case 12: // Alien discover health pack
        {
            cout << "Alien finds a health pack." << endl;
            cout << "Alien's life increased by 20." << endl;
            int hp = hp_ + 20;
            if (hp >= 100)
            {
                hp_ = 100;
                cout << "Alien's life is full." << endl;
            }
            else
            {
                hp_ = hp;
                cout << "Alien's life increased by 20." << endl;
            }
            alienMovement(game);
            break;
        }

        case 13: // Alien discover pod
        {
            cout << "Alien finds a pod." << endl;

            int closest = 1;
            float smallestDistance = 39.59797975; // max distance of max dimensions

            int x1, y1;
            for (int i = 1; i < nzombie; i++)
            {
                x1 = zombie[i].getX();
                y1 = zombie[i].getY();

                float distance = sqrt(pow((x1 - x_), 2.0) + pow((y1 - y_), 2.0));

                if (distance < smallestDistance)
                {
                    smallestDistance = distance;
                    closest = i;
                }
            }

            int previousHp = zombie[closest].getHp();
            int currentHp = previousHp - 10;
            cout << "Alien attacks zombie " << closest << " with 10 damage using pod." << endl
                 << endl;

            if (currentHp > 0)
            {
                cout << "Zombie " << closest << " still alive after the attack." << endl;
                zombie[closest].setHp(currentHp);
            }
            else
            {
                cout << "Zombie " << closest << " died." << endl;
                zombie[closest].setHp(0);
                zombieAlive = zombieAlive - 1;
                // remove zombie from board
                game.setObject(x1, y1, ' '); 
                zombie[closest].setX(100);
                zombie[closest].setY(100);
            }
            alienMovement(game);
            break;
        }
        
        case 14: // alien discover rock
        {
            cout << "Alien stumbles upon a rock." << endl << endl;

            char objects[] = {' ', ' ', '<', '>', '^', 'h', 'p', 'v'};
            int noOfObjects = 8;
            int objNo = rand() % noOfObjects;

            char obj = objects[objNo];

            if (obj == ' ')
            {
                cout << "Alien discovers nothing beneath the rock." << endl;
            }

            else if (obj == '<' || obj == '>' || obj == '^' || obj == 'v')
            {
                cout << "Alien discovers an arrow beneath the rock." << endl;
            }

            else if (obj == 'p')
            {
                cout << "Alien discovers a pod beneath the rock. " << endl;
            }

            else if (obj == 'h')
            {
                cout << "Alien discovers a health pack beneath the rock. " << endl;
            }

            int x = x_;
            int y = y_;

            switch (MovementState)
                {
                    case 1: // up
                        y = y + 1;
                        break;
                    case 2: // down
                        y = y - 1;
                        break;
                    case 3: // left
                        x = x - 1;
                        break;
                    case 4: // right
                        x = x + 1;
                        break;
                }
            game.setObject(x, y, obj);
            cout << "Alien stops in front of the object." << endl;
            AlienHit = 20; // alien turn's ends
            break;
        }

        case 15: // alien discover up arrow
        {
            cout << "Alien discovers an arrow." << endl;
            atk_ = atk_ + 20;
            cout << "Alien's attack increased by 20 and move upwards." << endl;
            alienMovement(game);
            MovementState = 1; // alien up
            break;
        }

        case 16: // alien discover down arrow
        {   
            cout << "Alien discovers an arrow." << endl;
            atk_ = atk_ + 20;
            cout << "Alien's attack increased by 20 and move downwards." << endl;
            alienMovement(game);
            MovementState = 2; // alien down
            break;
        }

        case 17: // alien discover left arrow
        {
            cout << "Alien discovers an arrow." << endl;
            atk_ = atk_ + 20;
            cout << "Alien's attack increased by 20 and move to the left." << endl;
            alienMovement(game);
            MovementState = 3; // alien left
            break;
        }

        case 18: // alien discover right arrow
        {
            cout << "Alien discovers an arrow." << endl;
            atk_ = atk_ + 20;
            cout << "Alien's attack increased by 20 and move to the right." << endl;
            alienMovement(game);
            MovementState = 4; // alien right
            break;
        }

        case 19: // alien hits border
        {
            cout << "Alien hits the border." << endl << endl;
            AlienHit = 20; // alien turn's ends
            break;
        }

        case 21: // alien hits zombie 1-9
        {
            int x = x_;
            int y = y_;

            switch (MovementState)
                {
                    case 1: // up
                        y = y + 1;
                        break;
                    case 2: // down
                        y = y - 1;
                        break;
                    case 3: // left
                        x = x - 1;
                        break;
                    case 4: // right
                        x = x + 1;
                        break;
                }
            char ch = game.getObject(x, y);
            int zNumber = ch - '0';

            cout << "Alien hits zombie " << zNumber << " ." << endl;
            cout << "Alien inficts " << atk_ << " damage to zombie " << zNumber << " . ";

            int zombieHP = zombie[zNumber].getHp();
            zombieHP = zombieHP - atk_;

            if (zombieHP > 0)
            {
                cout << "Zombie " << zNumber << " still alive after the attack." << endl;
                zombie[zNumber].setHp(zombieHP);
            }
            else
            {
                cout << "Zombie " << zNumber << " died." << endl;
                zombie[zNumber].setHp(0);
                zombieAlive = zombieAlive - 1;
                // remove zombie from board
                game.setObject(x, y, ' '); 
                zombie[zNumber].setX(100);
                zombie[zNumber].setY(100);
            }
            
            AlienHit = 20; // alien turn's ends
            GameState = 2;
            break;
        }
    }
    if (zombieAlive == 0) // win condition
        {
            GameState = 3; // alien wins
        }
}

void ChangeData()
{
    string settings;
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> setw(1) >> settings;

    while (!cin.good() || settings != "y" && settings != "Y" && settings != "n" && settings != "N")
    {
        cout << "Please enter in y/n." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> setw(1) >> settings;
    }
    
    if (settings == "y" || settings == "Y")
    {
        cout << "Board Settings  " << endl;
        cout << "----------------" << endl;

        // Change Rows //
        cout << "Enter rows => ";
        cin >> nrow;
        while (!cin.good() || nrow % 2 == 0 || nrow < 3 || nrow > 29)
        {
            cout << "Please enter odd numbers" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter rows => ";
            cin >> nrow;
        }

        // Change Columns //
        cout << "Enter columns => ";
        cin >> ncolumn;
        while (!cin.good() || ncolumn % 2 == 0 || ncolumn < 3 || ncolumn > 29)
        {
            cout << "Please enter odd numbers" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter columns => ";
            cin >> ncolumn;
        }

        // Change number of Zombies //
        cout << "Enter number of zombies => ";
        cin >> nzombie;
        while (!cin.good() || nzombie <= 0 || nzombie > 9)
        {
            cout << "Please enter numbers between 1 and 9" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter number of zombies => ";
            cin >> nzombie;
        }
        zombieAlive = nzombie;
    }
    else
    {
        ncolumn = 9;
        nrow = 5;
        nzombie = 1;
        zombieAlive = 1;
    }
}

void displayStatus(Alien ALIEN, int j)
{
    if (GameState == 1)
    {
        cout << "->  Alien       : Life " 
             << ALIEN.getHp() << ", Attack " << ALIEN.getAtk() << endl;
        
        for (int i = 1; i <= nzombie; i++)
        { 
            cout << "    Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                 << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
        }
        cout << endl;
    }
    else if (GameState == 2)
    {
        cout << "    Alien       : Life " 
             << ALIEN.getHp() << ", Attack " << ALIEN.getAtk() << endl;
        
        for (int i = 1; i <= nzombie; i++)
        {
            if (i == j)
            {
                cout << "->  Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                     << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
            }
            else
            {
                cout << "    Zombie " << i << "    : Life " << zombie[i].getHp() << ", Attack " 
                     << zombie[i].getAtk() << ", Range " << zombie[i].getRange() << endl;
            }
        }
        cout << endl;
    }
        
}

void command()
{
    string command = " ";
    cout << "Command => ";
    cin >> command;
    
    while (!cin.good() || command != "up" && command != "down" && command != "left" && command != "right" && command != "arrow" 
           && command != "help" && command != "save" && command != "load" && command != "quit")
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a correct commands." << endl;
            cout << "Command => ";
            cin >> command;
        }

    if (command == "up")
    {        
        CommandState = 1;
        MovementState = 1;
        cout << "Alien move up." << endl;
    }

    else if (command == "down")
    {
        CommandState = 2;
        MovementState = 2;
        cout << "Alien move down." << endl;
    }

    else if (command == "left")
    {
        CommandState = 3;
        MovementState = 3;
        cout << "Alien move left." << endl;
    }

    else if (command == "right")
    {
        CommandState = 4;
        MovementState = 4;
        cout << "Alien move right." << endl;
    }

    else if (command == "arrow")
    {
        CommandState = 5;
    }

    else if (command == "help")
    {
        CommandState = 6; 
    }

    else if (command == "save")
    {
        CommandState = 7;
    }

    else if (command == "load")
    {
        CommandState = 8;
    }

    else if (command == "quit")
    {
        CommandState = 9;
    }

}

void saveGame(string filename, Board &game, Alien &alien, bool &saved)
{
    fstream myFile;
    filename = filename + ".txt";
    myFile.open(filename, ios::out);
    if (myFile.is_open())
    {
        // write game settings
        myFile << endl << nrow << " " << ncolumn <<endl;
        for (int i = 0; i < nrow; i++) // for y dim
        {
            for (int j = 0; j < ncolumn; j++) // for x dim
            {
                myFile << game.map_[i][j] << ",";
            }
            myFile << endl;
        }
        // write alien status
        myFile << alien.getX() << " " << alien.getY() << " " << alien.getHp() << " " << alien.getAtk() << endl;
        
        // write zombie status
        for (int i = 0; i < nzombie; i++)
        {
            myFile << zombie[i].getSymbol() << " " << zombie[i].getX() << " " << zombie[i].getY() << " " << zombie[i].getHp() 
            << " " << zombie[i].getAtk() << " " << zombie[i].getRange() << endl;
        }
        
    }
    saved=1;
    myFile.close();
    cout << endl
         << "Game is saved to the file :" << filename << endl
         << "Press any key to continue......" << endl;
    getch();
}

void loadGame(string filename, Board &game, Alien &alien, bool &loaded)
{
    
    Zombie zombie;
    filename = filename + ".txt";
    ifstream infile;
    // If file fail to open
    infile.open(filename);
    if (!infile.is_open())
    {
        cout << "Failed to open the file. " << filename << endl;
        return;
    }
    // Read the size of the vector from the file
    int rows, cols;
    infile >> rows >> cols;

    // Resize the map vector to the correct size
    game.init(cols, rows);

    // read the board data
    string line;
    getline(infile, line); // skip the rest of the line
    for (int i = 0; i < rows; i++)
    {
        getline(infile, line);
        istringstream iss(line);
        for (int j = 0; j < cols; j++)
        {
            string cell;
            getline(iss, cell, ',');
            game.map_[i][j] = cell[0];
        }
    }

    // Read the alien's data from the file

    int alienX, alienY, alienHp, alienAtk;
    infile >> alienX >> alienY >> alienHp >> alienAtk;

    alien.setAlien(alienX, alienY, game);
    alien.setHp(alienHp);
    alien.setAtk(alienAtk);

    // Read the zombie's data from the file
    
    char symbol;
    int x, y, hp, atk, range;
    infile >> symbol >> x >> y >> hp >> atk >> range;
    zombie.setSymbol(symbol);

    zombie.setHp(hp);
    zombie.setAtk(atk);
    zombie.setRange(range);
    
    infile.close();
    loaded = 1;
    cout << endl
             << filename << " is loaded!!!" << endl
             << "Press any key to continue......" << endl;
    getch();
}

void maingame()
{
    MovementState = 0;        
    AlienHit = 0;        
    GameState = 1;        // Alien turn = 1, zombie turn = 11-19, alien wins = 3, alien loses = 4, quit = 5
    CommandState = 0;       
    nzombie = 0;    // save number of zombies 
    zombieAlive = 0; // save number of zombie alive 
    nrow = 0;       // save number of rows 
    ncolumn = 0;    // save number of columns 
    system("cls");
    char settings;

    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows   : 5" << endl;
    cout << "Board Colums : 9" << endl;
    cout << "Zombie Count : 1" << endl << endl;
    
    ChangeData();

    // initial alien position
    int x1 = ncolumn/2 + 1;
    int y1 = nrow/2 + 1;
    char ch_ = '@';
    
    // declaring game objects
    Board game(ncolumn, nrow);
    Alien ALIEN(x1, y1, ch_);
    ALIEN.setAlien(x1, y1, game);

    for (int i = 1; i <= nzombie; i++) // place zombies into the board
    {
        char ch = i + '0';
        zombie[i].setSymbol(ch);
        
        int hp = (rand() % 5 + 2) * 50; 
        int atk = (rand() % 5 + 1) * 5;
        int range = rand() % 3 + 1;
        zombie[i].setHp(hp);
        zombie[i].setAtk(atk);
        zombie[i].setRange(range);
           
        int x = rand() % ncolumn + 1;
        int y = rand() % nrow + 1;
        
        char chZombie = game.getObject(x, y);
        zombie[i].setZombie(x, y, game);
    }

    do
    {
        if (GameState == 1) // alien's turn
        {
            game.display();
            displayStatus(ALIEN, 0);
            cout << "Alien's turn." << endl << endl;
            system("pause");

            game.display();
            displayStatus(ALIEN, 0);
            command();
            
            switch (CommandState)
            {
                case 1: // command up
                case 2: // command down
                case 3: // command left
                case 4: // command right
                {
                    AlienHit = 0;
                    while (AlienHit != 20 && GameState != 3)
                    {
                        game.display();
                        displayStatus(ALIEN, 0);
                        ALIEN.alienCheck(game);
                        ALIEN.alienAction(game);
                        cout << endl;
                        system("pause");
                        if (zombieAlive == 0)
                        {
                            GameState = 3;
                            break;
                        }
                    }
                    if (AlienHit == 20) // alien stopped by object
                    {
                        game.display();
                        displayStatus(ALIEN, 0);
                        // cout << "Alien turn ends." << endl << endl;
                        // system("pause");
                        if (zombieAlive == 0)
                        {
                            GameState = 3;
                            break;
                        }
                        else
                        {
                            cout << "Alien's turn ends." << endl << endl;
                            system("pause");
                            GameState = 2; // zombie's turn
                        }
                    }
                    break;
                }

                case 5: // command arrow
                {
                    int x, y;
                    string arrow;
                    cout << "Please enter the coordinates and direction of arrow (eg. 5 7 up)." << endl
                        << "=> ";
                    cin >> x >> y >> arrow;

                    while (!cin.good() || x <= 0 || x > ncolumn || y <= 0 || y > nrow ||
                        arrow != "up" && arrow != "down" && arrow != "left" && arrow != "right")
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Please enter correct coordinates and directions." << endl;
                        break;
                    }

                    char ch = game.getObject(x, y);

                    if (ch == '^' || ch == 'v' || ch == '<' || ch == '>')
                    {
                        if (arrow == "up")
                        {
                            game.setObject(x, y, '^');
                        }
                        else if (arrow == "down")
                        {
                            game.setObject(x, y, 'v');
                        }
                        else if (arrow == "left")
                        {
                            game.setObject(x, y, '<');
                        }
                        else if (arrow == "right")
                        {
                            game.setObject(x, y, '>');
                        }
                        cout << "Arrow set." << endl;
                    }
                    else
                    {
                        cout << "Arrow not found." << endl;
                    }
                    system("pause");
                    break;
                }

                case 6: 
                {
                    cout << endl
                        << "Commands:" << endl
                        << "1. up      - Move up." << endl
                        << "2. down    - Move down." << endl
                        << "3. left    - Move left." << endl
                        << "4. right   - Move right." << endl
                        << "5. arrow   - Change the direction of the arrow." << endl
                        << "6. help    - Display the user commands." << endl
                        << "7. save    - Save the game." << endl
                        << "8. load    - Load a game." << endl
                        << "9. quit    - Quit the game." << endl;
                    system("pause");
                    break;
                }

                case 7: // command save
                {
                    bool saved = 0;
                    string filename;
                    cout << "Enter the file name (without .txt) to save the current game." << endl
                         << "=> ";
                    cin >> filename;
                    saveGame(filename, game, ALIEN, saved);
                    if (saved)
                    {
                        cout << "Game saved." << endl << endl;
                    }
                    else
                    {
                        cout << "Game not saved." << endl
                             << "Please check filename / read write permissions." << endl << endl;
                    }
                    system("pause");
                    break;
                }

                case 8: // command load
                {
                    bool loaded = 0;

                    string filename;
                    cout << "Enter the file name (without .txt) to load the previous game." << endl
                         << "=> ";
                    cin >> filename;

                    loadGame(filename, game, ALIEN, loaded);
                    if (loaded)
                    {
                        cout << "Game loaded." << endl << endl;
                    }
                    else
                    {
                        cout << "Game not loaded." << endl
                             << "Please check filename / read write permissions." << endl << endl;
                    }
                    system("pause");
                    break;
                }

                case 9: // command quit
                {
                    char input;
                    cout << "Any unsaved progress will be lost." << endl
                        << "Are you sure to quit game y/n ?" << endl;
                    cin >> input;
                    input = toupper(input);
                    
                    while (!cin.good() && input != 'Y' && input != 'N')
                    {
                        cout << "Please enter in y/n." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Are you sure to quit game (y/n)? => ";
                        cin >> input;
                        input = toupper(input);
                    }

                    if (input == 'Y')
                    {
                        GameState = 5;
                    }         
                    break;
                }    
            }
        }

        else if (GameState == 2)
        {
            // alien attack return to 0
            ALIEN.setAtk(0);
            // remove alien trail and set random game objects
            char objects[] = {' ', ' ', ' ', '<', '>', '^', 'h', 'r', 'p', 'v'};
            int noOfObjects = 10; // number of objects in the objects array
            for (int i = 1; i <= game.getDimY(); i++)
            {
                    for (int j = 1; j <= game.getDimX(); j++)
                    {
                        if (game.getObject(j, i) == '.')
                        {
                            int objNo = rand() % noOfObjects;
                            game.setObject(j, i, objects[objNo]);
                        }
                    }
            }
            // zombie action
            for (int i = 1; i <= nzombie; i++)
            {
                game.display();
                displayStatus(ALIEN, i);
                cout << "Zombie " << i << " turn." << endl << endl;
                system("pause");

                if (zombie[i].getHp() != 0) // zombie alive
                {
                    game.display();
                    displayStatus(ALIEN, i);
                    zombie[i].movement(game, ALIEN);
                    system("pause");

                    game.display();
                    displayStatus(ALIEN, i);
                    zombie[i].attack(ALIEN);
                    system("pause");

                    if (GameState == 4)
                    {
                        break;
                    }
                }
                else // zombie dead
                {
                    cout << "Zombie " << i << " is dead." << endl;
                    system("pause");
                }
                game.display();
                displayStatus(ALIEN, i);
                cout << "Zombie " << i << " turn's ends." << endl << endl;
                system("pause");
            }

            if (GameState == 4)
            {
                break;
            }
            else
            {
                GameState = 1;
            }
        }
    }while (GameState != 3 && GameState != 4 && GameState != 5);

    if (GameState == 3)
    {
        game.display();
        displayStatus(ALIEN, 0);
        cout << "Victory!!!" << endl;
    }
    else if (GameState == 4)
    {
        game.display();
        displayStatus(ALIEN, 0);
        cout << "Game Over" << endl;
    }
}


int main()
{
    srand(time(NULL)); // for random map

    int flag = 1;
    while (flag == 1)
    {
        maingame(); // GameState = 1, 2, 3, 4

        // after GameState = 3, 4 and 5
        if (GameState == 3 || GameState == 4)
        {
            char input;
            cout << "Do you want to play again (y/n) ?" << endl
                 << "-> ";
            cin >> input;
            input = toupper(input);

            while (!cin.good() && input != 'Y' && input != 'N')
            {
                cout << "Please enter in y/n." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Do you want to play again (y/n)? -> ";
                cin >> input;
                input = toupper(input);
            }
            if (input == 'N')
            {
                cout << "See you next time!!!" << endl;
                system("pause");
                flag = 0;
            }
        }
        else if (GameState == 5)
        {
            flag = 0;
        }
        continue;
    }
    return 0; 
}