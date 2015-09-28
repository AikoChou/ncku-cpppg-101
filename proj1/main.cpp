#include "stdafx.h"
#include "game.h"
using namespace std;

#define WIDTH 35
#define HEIGHT 10

int startx = 0;
int starty = 0;
int numChoice = 5;

char choices[][35] = {
    "Easy   (9*9 with 10 Bombs)",
    "Medium (16*16 with 40 Bombs)",
    "Hard   (25*25 with 120 Bombs)",
    "Customize",
    "Exit",
     };


int mapSize;
int maxBombs;


void print_menu(WINDOW *menu_win, int highlight)
{
    int x = 2, y = 2, i;
    box(menu_win, 0, 0);
    for(i = 0; i < numChoice; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            ++y;
    }
    wrefresh(menu_win);
}

void instruction()
{
	mvaddstr(1, mapSize + 4, "Press 'a' to open a grid");
	mvaddstr(2, mapSize + 4, "Press 'f' to set a flag");
	mvaddstr(3, mapSize + 4, "Press 'q' to quit");
}


int main()
{
/*Menu*/
    WINDOW *menu_win;
    int highlight = 1, choice = 0, c;

    initscr();
    clear();
    noecho();
    cbreak();

    startx = (COLS - WIDTH) / 2;
    starty = (LINES - HEIGHT) / 2;

	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();

    print_menu(menu_win, highlight);

    while(1){
        c = wgetch(menu_win);
        switch(c)
        {   case KEY_UP:
                if(highlight == 1)  highlight = numChoice;
                else    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == numChoice)  highlight = 1;

                else    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default: mvprintw(0, 0, "Press enter to select a choice");
                refresh();
                break;
        }

    print_menu(menu_win, highlight);

    if(choice != 0) /* User did a choice come out of the infinite loop */
        break;
    }

    switch(choice)
    {
        case 1: mapSize  = 9; maxBombs = 10; break;
        case 2: mapSize  = 16; maxBombs = 40; break;
        case 3: mapSize  = 25; maxBombs = 120; break;
        case 4: endwin(); return 0;
        default: endwin(); return 0;
    }

    Game newGame1(mapSize, maxBombs);
    newGame1.printOut();

    clear();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    refresh();

    WINDOW *game_win;
    game_win = newwin(mapSize + 2, mapSize + 2, 0, 0);
    box(game_win, 0, 0);
    wrefresh(game_win);
	instruction();

    int xPos = 1, yPos = 1;
    int ch, go_on = TRUE;

    time_t t1,t2;
    int h = 0, m = 0, s = 0, t = 0;

    while(go_on){
        move(yPos, xPos);
        ch = getch();
        switch(ch){
            case KEY_LEFT: --xPos; break;
            case KEY_RIGHT: ++xPos; break;
            case KEY_UP: --yPos; break;
            case KEY_DOWN: ++yPos; break;

            case 'a': if(t == 0){
                            t1 = time(NULL);
                            t++;
                            }
                      newGame1.check(yPos, xPos);
                      newGame1.draw();
                      break;

            case 'f': if(t == 0){
                            t1 = time(NULL);
                            t++;
                            }
                      newGame1.flag(yPos, xPos);
                      newGame1.draw();
                      break;

            case ERR: if(t != 0){
                            time(&t2);
                            h = (t2-t1) / 3600;
                            m = ((t2-t1) - (h*3600)) / 60;
                            s = (t2-t1) - (h*3600) - (m*60);
                            }
                       mvprintw(mapSize+4, 0, "Time: %2d:%2d:%2d", h, m, s);
                       move(yPos, xPos);
                       usleep(1000);
                       break;

            default: go_on = FALSE;
        }
        while(xPos < 1) xPos += mapSize;
        while(xPos > mapSize) xPos -= mapSize;
        while(yPos < 1) yPos += mapSize;
        while(yPos > mapSize) yPos -= mapSize;

        wrefresh(game_win);
    }

    endwin();
    return 0;
}

