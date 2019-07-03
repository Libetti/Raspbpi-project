#include <sense/sense.h>
#include <sense/i2c.h>
#include <sense/framebuffer.h>
#include <sense/joystick.h>
#include <sense/coord.h>
#include <stdio.h>
#include <linux/input.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

char running=1;
char c;
float x=0;
float y=0;
int i=0;
uint16_t color;
pi_framebuffer_t* frame;
pi_i2c_t* dev;
pi_joystick_t* joystick;
coordinate_t data;
coordinate_t* pdata = &data;


