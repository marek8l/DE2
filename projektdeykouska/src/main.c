#include <stdio.h>
#include <oled.h>
#include <avr/io.h>
#include <timer.h>
#include <time.h>
#include <gpio.h>
#include <avr/interrupt.h>
#include <twi.h>

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define LEFT  3
#define RIGHT 4
#define UP    5
#define DOWN  6
#define SNAKE_SPEED 5
#define STARTING_X_POS 32
#define STARTING_Y_POS 32
#define WINDOW_MIN_X 1
#define WINDOW_MAX_X SCREEN_WIDTH-1
#define WINDOW_MIN_Y 1
#define WINDOW_MAX_Y SCREEN_HEIGHT-1

int direction;                              // Current direction of snakes movement
int prev_dir;                               // Direction of snakes movement in his last move
int cycle_cnt;                              // Counter of cycles of the main program
int x_pos;                                  // X position of snakes head
int y_pos;                                  // Y position of snakes head
int pix[SCREEN_WIDTH][SCREEN_HEIGHT];    // Array of all pixels. Pixel can either be unoccupied (-1) 
                                            // or show direction of snakes movement from that pixel (3-6)
int x_treat;                                // X position of treat
int y_treat;                                // Y position of treat
time_t t;                                   // Variable for creating randomness
int x_tail;                                 // X position of tail
int y_tail;                                 // Y position of tail
int temp;                                   // Temporary variable for storing pixel data
int death;                                 // Whether the snake is dead (=true) or alive (=false)
int score;                                  // Current player score defined by (the amount of treats eaten*10)

/*
* Function:   reset
* --------------------------  
* Sets all global variables to theirs starting values.
* Displays game window, players starting position and randomly placed treat
*/
void reset(){
    direction = RIGHT;
    prev_dir = RIGHT;
    cycle_cnt = 0;
    x_pos = STARTING_X_POS;
    y_pos = STARTING_Y_POS;
    x_tail = STARTING_X_POS-2;
    y_tail = STARTING_Y_POS;
    temp = 0;
    death = 0;
    score = 0;

    for (int i = 0; i<SCREEN_WIDTH; i++){
        for (int j = 0; j<SCREEN_HEIGHT; j++){
            pix[i][j] = -1;
        }
    }

    /* Generating new treat position.
    *   x_treat ∈ (WINDOW_MIN_X, WINDOW_MAX_X)
    *   y_treat ∈ (WINDWO_MIN_Y, WINDOW_MAX_Y)
    *//*
    while (1){
        x_treat = 50;//rand() % (WINDOW_MAX_X-1);
        y_treat = 50;//rand() % (WINDOW_MAX_Y-1);
        if ((x_treat > WINDOW_MIN_X) && (y_treat > WINDOW_MIN_Y)){
            //if ((pix[x_treat][y_treat] == -1) && (x_treat != x_pos) && (y_treat != y_pos))
                break;
        }
    }*/

    oled_clrscr();
    oled_drawRect(WINDOW_MIN_X, WINDOW_MIN_Y, WINDOW_MAX_X-WINDOW_MIN_X, WINDOW_MAX_Y-WINDOW_MIN_Y, WHITE);
    oled_drawPixel(STARTING_X_POS-2, STARTING_Y_POS, WHITE);
    oled_drawPixel(STARTING_X_POS-1, STARTING_Y_POS, WHITE);
    oled_drawPixel(STARTING_X_POS-0, STARTING_Y_POS, WHITE);
    pix[STARTING_X_POS-2][STARTING_Y_POS] = RIGHT;
    pix[STARTING_X_POS-1][STARTING_Y_POS] = RIGHT;
    pix[STARTING_X_POS-0][STARTING_Y_POS] = -1;
    //oled_drawPixel(x_treat, y_treat, WHITE);
    oled_display();
    
}
// end of reset()


int main(){
    // Initiation of display, buttons and random number generation
    
    TIM2_OVF_16MS
    TIM2_OVF_ENABLE
    sei();

    GPIO_mode_input_pullup(&DDRD, LEFT);
    GPIO_mode_input_pullup(&DDRD, RIGHT);
    GPIO_mode_input_pullup(&DDRD, UP);
    GPIO_mode_input_pullup(&DDRD, DOWN);
    

    oled_init(OLED_DISP_ON);
    oled_clrscr();
    oled_display();


    reset();

    while(1){
       
    }
    }
    

// end of main()

ISR(TIMER2_OVF_vect){
            if (GPIO_read(&PIND,LEFT) == 0)
                x_pos--;
            else if (GPIO_read(&PIND,RIGHT) == 0)
                x_pos++;
            else if (GPIO_read(&PIND,UP) == 0)
                y_pos--;
            else if (GPIO_read(&PIND,DOWN) == 0)
                y_pos++;
    if (x_pos<0)
        x_pos = 0;
    if (x_pos>SCREEN_WIDTH)
        x_pos = SCREEN_WIDTH;
    if (y_pos<0)
        y_pos = 0;
    if (y_pos>SCREEN_HEIGHT)
        y_pos = SCREEN_HEIGHT;   
      
    oled_gotoxy(x_pos,y_pos);
    oled_puts("mm");
        
}
   