
typedef int* IntArrayPtr;


class Game
{
public:
        Game(int, int);
        ~Game();
        void draw();
        void check(int, int);
        void flag(int, int);
        void printOut();

private:
        const int MAP_SIZE;
        const int MAX_BOMBS;

        IntArrayPtr *Map, *Visible;
        enum {EMPTY = 0, BOMB = 9};
        enum {NO = 0, YES = 1, FLAG = 2};

        bool bombed;
        bool win;

        bool set(int, int);
        void init();
        bool get(int, int);
        void open(int, int);
        void end();

};
