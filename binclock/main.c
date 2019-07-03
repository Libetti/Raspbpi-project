/*
Name= Anthony Libetti
Date= 4/23/2019
File= Main.c
Description= A simple binary clock that displays the current est
	     time. Hours are represented in blue, minutes in green and
             seconds in red. Each lit-up pixel represents a 1, those 
             which are not lit represent 0.

*/
#include "framebuffer.h"

void num2bin(int tme,int row, uint16_t color);
void SIGhandler(int);

int main(){
pi_framebuffer_t* dev = getFBDevice();
sense_fb_bitmap_t* bitmap = dev->bitmap;

signal(SIGINT,SIGhandler);
while(1)
    {
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    clearBitmap(bitmap,0);
    num2bin(now_t.tm_hour,1,getColor(0,0,255));
    num2bin(now_t.tm_min,3,getColor(0,255,0));
    num2bin(now_t.tm_sec,5,getColor(255,0,0));
    sleep(1);
    }
return 0;
}


void num2bin(int tme,int row, uint16_t color){
pi_framebuffer_t* dev = getFBDevice();
sense_fb_bitmap_t* bitmap = dev->bitmap;

    for(int i=0;i<8;i++)
    {
        bitmap->pixel[row][i] = tme % 2;
        tme = tme / 2;
    }
    for(int i=0;i<8/2;i++)
    {
        uint16_t tmp = bitmap->pixel[row][i];
        bitmap->pixel[row][i] = bitmap->pixel[row][8 - 1 - i];
        bitmap->pixel[row][8 - 1 - i] = tmp;
}
for(int i=0;i<8;i++)
{
if(bitmap->pixel[row][i] == 1)
{
bitmap->pixel[row][i] = color;
}
}
}

void SIGhandler(int sig)
{
    char c;

    signal(sig, SIG_IGN);
    printf("Do you really want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y')
       	exit(0);
    else
         signal(SIGINT, SIGhandler);
}

