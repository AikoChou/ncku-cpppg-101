#include "stdafx.h"

#include "game.h"

using namespace std;

Game::Game(int nsize, int nbomb):MAP_SIZE(nsize),MAX_BOMBS(nbomb)
{
    Map = new IntArrayPtr[nsize];
    Visible = new IntArrayPtr[nsize];
    int i;
    for (i = 0; i < nsize; i++){
            Map[i] = new int[nsize];
            Visible[i] = new int[nsize];
    }
    init();
}

Game::~Game()
{
    for(int i = 0; i < MAP_SIZE; i++){
        delete[] Map[i];
        delete[] Visible[i];
    }
    delete[] Map;
    delete[] Visible;
}


bool Game::set(int xpos, int ypos)
{
    if (xpos>=0 && xpos<MAP_SIZE && ypos>=0 && ypos<MAP_SIZE && Map[xpos][ypos] != BOMB)
        return true;
    else
        return false;
}

void Game::init()
{
    win = false;
    bombed = false;
    srand(time(0));

    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
        {
            Map[i][j] = EMPTY;
            Visible[i][j] = 0;
        }

    for (int i = 0; i < MAX_BOMBS; i++)
    {
        int xIndex = rand() % MAP_SIZE;
        int yIndex = rand() % MAP_SIZE;

        if (Map[xIndex][yIndex] == BOMB)
        {
            i--;
            continue;
        }
        Map[xIndex][yIndex] = BOMB;
    }

    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
            if (Map[i][j] == BOMB)
            {
                if (set(i - 1, j - 1))      Map[i - 1][j - 1]++;
                if (set(i, j - 1))          Map[i][j - 1]++;
                if (set(i + 1, j - 1))      Map[i + 1][j - 1]++;
                if (set(i + 1, j))          Map[i + 1][j]++;
                if (set(i + 1, j + 1))      Map[i + 1][j + 1]++;
                if (set(i, j + 1))          Map[i][j + 1]++;
                if (set(i - 1, j + 1))      Map[i - 1][j + 1]++;
                if (set(i - 1, j))          Map[i - 1][j]++;
            }
}

void Game::draw()
{
    start_color();
    int i, j;
    char bomb = 'B';
    for(i = 0; i < MAP_SIZE; i++)
        for (j = 0; j < MAP_SIZE; j++)
            mvaddch(j+1, i+1, ' ');

    if(win)
    {
        for(i = 0; i < MAP_SIZE; i++)
            for (j = 0; j < MAP_SIZE; j++)
                if(Map[i][j] == BOMB)
                {
                    mvaddch(j+1, i+1, 'f');//Show all bombs 
                }
        mvaddstr(LINES/2, COLS/2, "WINNER!");
		nodelay(stdscr, FALSE);
        return;
    }

    if(bombed)
    {
        for(i = 0; i < MAP_SIZE; i++)
            for (j = 0; j < MAP_SIZE; j++)
                if(Map[i][j] == BOMB)
                {
                    mvaddch(j+1, i+1, bomb);//Show all bombs    
                }
        mvaddstr(LINES/2, COLS/2, "BOMB!  ");
		nodelay(stdscr, FALSE);
        return;
    }

    for(i = 0; i < MAP_SIZE; i++)
        for (j = 0; j < MAP_SIZE; j++)
       {
            char ch = Map[i][j] + 48;
            if (Visible[i][j] == 1)
                mvaddch(j+1, i+1, ch);
            else if (Visible[i][j] == 2)
                mvaddch(j+1, i+1, 'f');
        }
    refresh();
}

void Game::check(int yPos, int xPos)
{
    int x = xPos-1;
    int y = yPos-1;


    if (Visible[x][y] == 2)
        return;

    if (Map[x][y] == BOMB)
    {
        bombed = true;
        return;
    }

    Visible[x][y] = 1;

    if (Map[x][y] == EMPTY)
        open(x, y);

    end();

    if (bombed || win)
        init();

}

void Game::open(int x, int y)
{
    if (get(x - 1, y - 1))  open(x - 1, y - 1);
    if (get(x    , y - 1))  open(x    , y - 1);
    if (get(x + 1, y - 1))  open(x + 1, y - 1);
    if (get(x + 1, y    ))  open(x + 1, y    );
    if (get(x + 1, y + 1))  open(x + 1, y + 1);
    if (get(x    , y + 1))  open(x    , y + 1);
    if (get(x - 1, y + 1))  open(x - 1, y + 1);
    if (get(x - 1, y    ))  open(x - 1, y    );
}

bool Game::get(int x, int y)
{
    if (x == -1 || x == MAP_SIZE)
        return false;
    if (y == -1 || y == MAP_SIZE)
        return false;
    if (Map[x][y] == BOMB)
        return false;
    if (Visible[x][y] == FLAG)
        return false;
    if (Visible[x][y] == YES)
        return false;

    Visible[x][y] = 1;

    if (Map[x][y] != EMPTY)
        return false;

    return true;
}

void Game::flag(int yPos, int xPos)
{
    int x = xPos - 1;
    int y = yPos - 1;

    if (Visible[x][y] == 2)
    {   Visible[x][y] = 0;
        mvaddstr(LINES/2, COLS/2, "UNFLAG!");
    }

    else if (Visible[x][y] == 0)
    {   Visible[x][y] = 2;
        mvaddstr(LINES/2, COLS/2, "FLAG!  ");
    }
    refresh();
    end();
}

void Game::end()
{
    int k = 0;
    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
            if (Visible[i][j] == 2 && Map[i][j] == BOMB)
                k++;

    if (k == MAX_BOMBS)
        win = true;
}

void Game::printOut()
{
    ofstream outFile( "Mine.txt", ios::out);
    if(!outFile)
    {
        cerr << "File could not be opened" << endl;
        exit(1);
    }

    int i, j;

    for(i = 0; i < MAP_SIZE; i++)
    {   for (j = 0; j < MAP_SIZE; j++)
            outFile << Map[j][i] << ' ';
        outFile <<endl;
    }
}

