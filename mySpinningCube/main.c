#include <stdio.h>
#include <math.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
void usleep(__int64 usec)
{
  HANDLE timer;
  LARGE_INTEGER ft;

  ft.QuadPart = -(10 * usec);

  timer = CreateWaitableTimer(NULL, TRUE, NULL);
  SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);
}
#endif
#include <signal.h>

#define width 160
#define height 44
#define distance_from_cam 90
#define K1 40
#define background_ASCII_code ' '
#define surf_symb_1 '.'
#define surf_symb_2 '$'
#define surf_symb_3 '?'
#define surf_symb_4 '~'
#define surf_symb_5 '^'
#define surf_symb_6 '+'

int need_to_reset_colour = 0;

float A = 0, B = 0, C = 0;
float x = 0, y = 0, z = 0, ooz = 0;
int xp = 0, yp = 0, idx = 0;

const float cube_width = 18.0, increment_speed = 0.6;
float z_buffer[width * height];
char buffer[width * height];

float calculate_x(int i, int j, int k){
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + 
           j * cos(A) * sin(C) + k * sin(A) *sin(C) + i * cos(B) * cos(C);
}

float calculate_y(int i, int j, int k){
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) - 
           j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
           i * cos(B) * sin(C);
}

float calculate_z(int i, int j, int k){
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void calculate_surface(float cube_x, float cube_y, float cube_z, int ch){
    x = calculate_x(cube_x, cube_y, cube_z);
    y = calculate_y(cube_x, cube_y, cube_z);
    z = calculate_z(cube_x, cube_y, cube_z) + distance_from_cam;

    ooz = 1 / z;
    xp = (int)(width / 2 + K1 * ooz * x * 2);
    yp = (int)(height / 2 + K1 * ooz * y);

    idx = xp + yp * width;
    if(idx >= 0 && idx < width * height){
        if(ooz > z_buffer[idx]){
            z_buffer[idx] = ooz;
            buffer[idx] = ch;
        }
    }
}

void spin_cube(){
    printf("\x1b[2J");
    while(1){
        memset(buffer, background_ASCII_code, width * height);
        memset(z_buffer, 0, width * height * 4);
        for(float cube_x = -cube_width; cube_x < cube_width; cube_x += increment_speed){
            for(float cube_y = -cube_width; cube_y < cube_width; cube_y += increment_speed){
                calculate_surface(cube_x, cube_y, -cube_width, surf_symb_1); 
                calculate_surface(cube_width, cube_y, cube_x, surf_symb_2);
                calculate_surface(-cube_width, cube_y, -cube_x, surf_symb_3);    
                calculate_surface(-cube_x, cube_y, cube_width, surf_symb_4); 
                calculate_surface(cube_x, -cube_width, -cube_y, surf_symb_5);
                calculate_surface(cube_x, cube_width, cube_y, surf_symb_6);
            }   
        }

        printf("\x1b[H");
        for(int i = 0; i < width * height; i++){
            putchar(i % width ? buffer[i] : 10);
        }

        A += 0.005;
        B += 0.005;
        C += 0.001;
        usleep(10000);
    }
}

void reset_font_colour(){
    printf("\033[0m");
}

void read_font_choice(){
    int colour = 0;
    scanf("%d", &colour);

    switch(colour){
        case 1:
            printf("\033[1;32m");
            break;
        case 2:
            printf("\033[1;31m"); 
            break;
        case 3:
            reset_font_colour();
            break;
        default:
            printf("Sorry, i didnt catch that, please enter correct number\n");
            read_font_choice();
    }
}

void set_font_colour(){
    printf("\x1b[2J");
    printf("To set green font colour, press 1\nTo set red font colour press 2\n");
    printf("To set standard font colour, press 3\n");
    read_font_choice();
}

void quit(){
    printf("\n\n\t\t\tGoodbye!\n\n");
    exit(1);
}

void read_user_choice(){
    int choice = 0;
    scanf("%d", &choice);

    switch(choice){
        case 1:
            spin_cube();
            break;
        case 2:
            set_font_colour();
            break;
        case 3:
            quit();
            break;
        default:
            printf("Sorry, i didnt catch that, please enter correct number\n");
            read_user_choice();
    }
}


void run(){
    printf("Welcome to my spinning cube\n");
    while(1){
    printf("\x1b[2J");
    printf("You can:\n1)Spin cube\n2)Change font colour\n3)Quit\n");
    printf("Please choose on of these options by entering integer digit:\n");
    read_user_choice();
    }
}

void signal_handler(int sign_num){
    need_to_reset_colour = 1;
    exit(1);
}

int main(){
    signal(SIGINT, signal_handler);
    run();

    if(need_to_reset_colour) reset_font_colour();
    return 0;
}