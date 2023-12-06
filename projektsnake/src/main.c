#include <avr/io.h>
#include <avr/interrupt.h>
#include "oled.h"
#include "gpio.h"
#include "timer.h"
#include "twi.h"

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

int x_tail;
int y_tail;
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

void reset(){
    direction = RIGHT;
    prev_dir = RIGHT;
    x_pos = STARTING_X_POS;
    y_pos = STARTING_Y_POS;
    x_tail = STARTING_X_POS-2;
    y_tail = STARTING_Y_POS;
    death = 0;
    score = 0;
    random_var = MAGIC_CONSTANT;

    for (int i = 0; i<SCREEN_WIDTH; i++){
        for (int j = 0; j<SCREEN_HEIGHT; j++){
            pix[i][j] = -1;
        }
    }


    generateNewTreat();

    oled_clrscr();
    oled_drawRect(WINDOW_MIN_X, WINDOW_MIN_Y, WINDOW_MAX_X-WINDOW_MIN_X, WINDOW_MAX_Y-WINDOW_MIN_Y, WHITE);
    oled_drawPixel(STARTING_X_POS-2, STARTING_Y_POS, WHITE);
    oled_drawPixel(STARTING_X_POS-1, STARTING_Y_POS, WHITE);
    oled_drawPixel(STARTING_X_POS-0, STARTING_Y_POS, WHITE);
    pix[STARTING_X_POS-2][STARTING_Y_POS] = RIGHT;
    pix[STARTING_X_POS-1][STARTING_Y_POS] = RIGHT;
    pix[STARTING_X_POS-0][STARTING_Y_POS] = -1;
    oled_drawPixel(x_treat, y_treat, WHITE);
    oled_display();
}

void main(){
    oled_init(OLED_DISP_ON);
    oled_clrscr();
    oled_display();

    GPIO_mode_input_pullup(&DDRD, LEFT);
    GPIO_mode_input_pullup(&DDRD, RIGHT);
    GPIO_mode_input_pullup(&DDRD, UP);
    GPIO_mode_input_pullup(&DDRD, DOWN);

    TIM1_OVF_1SEC
    TIM1_OVF_ENABLE
    sei();

    reset();

    while (1){
    
    }
}

void readButtonInput(){
    if (GPIO_read(&PIND,LEFT) == 0)
        direction = LEFT;
    else if (GPIO_read(&PIND,RIGHT) == 0)
        direction = RIGHT;
    else if (GPIO_read(&PIND,UP) == 0)
        direction = UP;
    else if (GPIO_read(&PIND,DOWN) == 0)
        direction = DOWN;

    if (((prev_dir==RIGHT) && (direction==LEFT)) || ((prev_dir==LEFT) && (direction==RIGHT)))
        direction = prev_dir;
    else if (((prev_dir==UP) && (direction==DOWN)) || ((prev_dir==DOWN) && (direction==UP)))
        direction = prev_dir;
    else
        prev_dir = direction;
}

void generateNewTreat(){
    while (1){
        x_treat = (x_pos * random_var * direction) % SCREEN_HEIGHT;
        y_treat = (y_pos * random_var * direction) % SCREEN_WIDTH;
        if ((x_treat > WINDOW_MIN_X) && (y_treat > WINDOW_MIN_Y) && (x_treat < WINDOW_MAX_X) && (y_treat < WINDOW_MAX_Y)){
            if ((pix[x_treat][y_treat] == -1) && (x_treat != x_pos) && (y_treat != y_pos))                        
                break;
        }
        random_var = (random_var*2) % 1000;
    }
    oled_drawPixel(x_treat, y_treat, WHITE);
}

void moveTailByOne(){
    oled_drawPixel(x_tail, y_tail, BLACK);
    int temp = pix[x_tail][y_tail];
    pix[x_tail][y_tail] = -1;
    switch (temp) {
        case LEFT:
            x_tail--;
            break;
        case RIGHT:
            x_tail++;
            break;
        case UP:
            y_tail--;
            break;
        case DOWN:
            y_tail++;
            break;
    }
}

ISR(TIMER1_OVF_vect){
    if (death == 0){
        readButtonInput();

        pix[x_pos][y_pos] = direction;
        switch (direction) {
            case LEFT:
                x_pos--;
                break;
            case RIGHT:
                x_pos++;
                break;
            case UP:
                y_pos--;
                break;
            case DOWN:
                y_pos++;
                break;
        }

        if ((x_pos <= WINDOW_MIN_X) || (x_pos >= WINDOW_MAX_X) || (y_pos <= WINDOW_MIN_Y) || (y_pos >= WINDOW_MAX_Y))
            death = 1;
        if (pix[x_pos][y_pos] != -1)
            death = 1;

        oled_drawPixel(x_pos, y_pos, WHITE);

        
        moveTailByOne();
        

        
        if ((x_pos == x_treat) && (y_pos == y_treat)){
            score += 10;
            generateNewTreat();
        }
        else {
            moveTailByOne();
        }
        

       // oled_display();
    }
    else {
        oled_clrscr();
        oled_charMode(DOUBLESIZE);
        oled_puts("GAME OVER");
        oled_charMode(NORMALSIZE);
        oled_gotoxy(0, 2);
        oled_puts("Score: " + score);
        //oled_display();
    }
    oled_display();
}