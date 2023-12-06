#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define LEFT  3
#define RIGHT 4
#define UP    5
#define DOWN  6
#define MAGIC_CONSTANT 1337
#define STARTING_X_POS 32
#define STARTING_Y_POS 32
#define WINDOW_MIN_X 1
#define WINDOW_MAX_X SCREEN_WIDTH-1
#define WINDOW_MIN_Y 1
#define WINDOW_MAX_Y SCREEN_HEIGHT-1

int direction;
int prev_dir;
int pix[SCREEN_WIDTH][SCREEN_HEIGHT];
int x_pos;
int y_pos;
int x_treat;
int y_treat; 
int death;
int score;
int random_var;
int x_tail;
int y_tail;