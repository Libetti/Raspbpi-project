/* This is ETCHY BABY! 
NAME=ANTHONY LIBETTI
DATE=5/16/19
PROJECT=ETCH-A-SKETCH
DESCRIPTION=A RaspberryPi version of the timeless toy known as the
	    Etch-A-Sketch! Use the joystick to draw on the screen
            and press in to change the color of your cursor. When finished,
            shake the screen to erase your art or use Ctrl^C
            to exit cleanly.
*/

#include "incl.h"




/*Frees all devices and clears the screen */
void cleanup(void){
  clearBitmap(frame->bitmap,0);
  freeFrameBuffer(frame);
  freeJoystick(joystick);
  freei2cDevice(dev);
}

/* Handles ^C sig as input and terminates program if deteted.*/
void handler(int sig)
{
    running=0;
    c=0;
    signal(sig, SIG_IGN);
    printf("Are you sure you want to quit this lovely 8 by 8 retreat from reality? [Y] or [N] ->");
    c = getchar();
    if (c == 'y' || c == 'Y'){
        cleanup();
        exit(0);
    }
    else
         signal(SIGINT, handler);
}

/*Handles drawing on bitmap and color using joystick detections*/
void callbackFN(unsigned int code){
  setPixel(frame->bitmap,x,y,color);
  switch(code){
    case KEY_UP:
	y=y==0?7:y-1;
	break;
    case KEY_DOWN:
	y=y==7?0:y+1;
	break;
    case KEY_RIGHT:
	x=x==7?0:x+1;
	break;
    case KEY_LEFT:
	x=x==0?7:x-1;
	break;
    case KEY_ENTER:
	if(color==getColor(255,0,0)){
	  color=getColor(0,255,0);
	  break;
	}
	if(color==getColor(0,255,0)){
	  color=getColor(0,0,255);
	  break;
	}
	if(color==getColor(0,0,255)){
	  color=getColor(255,0,0);
	  break;
	}
	break;
    default:
	running=0;
  }
  setPixel(frame->bitmap,x,y,color);
}

int main(){
  signal(SIGINT,handler);
  joystick=getJoystickDevice();
  frame=getFBDevice();
  dev=geti2cDevice();
  configureAccelGyro(dev);
  clearBitmap(frame->bitmap,0);
  color=getColor(255,0,0);
  setPixel(frame->bitmap,0,0,color);
    do{
      pollJoystick(joystick,callbackFN,1000);
      getAccelData(dev,pdata);
        if((data.y > .3) || (data.x > .9) || (data.z < 0))
          clearBitmap(frame->bitmap,0);
      }while(running);
  cleanup();
  return 0;
}


