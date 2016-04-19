//Program that renders an analog clock in the linux terminal. (not windows compatible)
#include <iostream>

#include "termg.h"// 		terminal graphics functions
#include "timeutils.h"// 	time functions

#include <algorithm>//		min()
#include <math.h>//			sqrt() sine cosine

#include <unistd.h>//		usleep

#define PI 3.141592653589793

int width,height;
int bufferWidth,bufferHeight;

char** drawBuffer; //buffer containing next frame
char** oldBuffer; //buffer containing previous frame

void updateDimensions(){
	int size[4];
	getScreenDim(size);
	width = size[0]; height = size[1];
}

void initBuffers() {
	drawBuffer = new char*[width];
	oldBuffer = new char*[width];
	for(int i = 0; i < width; i++) {
		drawBuffer[i] = new char[height];
		oldBuffer[i] = new char[height];
		for(int y = 0; y < height; y++) {
			drawBuffer[i][y] = ' ';
			oldBuffer[i][y] = ' ';
		}
	}
	bufferWidth = width;
	bufferHeight = height;
}

void resizeBuffers(){
	char** newDrawBuffer = new char*[width];
	char** newOldBuffer = new char*[width];
	for(int x = 0; x < width; x++){
		newDrawBuffer[x] = new char[height];
		newOldBuffer[x] = new char[height];
		for(int y = 0; y < height; y++) {
			newDrawBuffer[x][y] = ' ';
			newOldBuffer[x][y] = ' ';
		}
	}
	
	for(int x = 0; x < bufferWidth; x++) {
		delete []drawBuffer[x];
		delete []oldBuffer[x];
	}
	
	delete []drawBuffer;
	delete []oldBuffer;
	
	drawBuffer = newDrawBuffer;
	oldBuffer = newOldBuffer;
	
	clearScreen();
	bufferWidth = width;
	bufferHeight = height;
}

void updateTerminal() {
	//write differences between old and draw to terminal.
	for(int y = 0; y < bufferHeight; y++) {
		for(int x = 0; x < bufferWidth; x++) {
			if(oldBuffer[x][y]!=drawBuffer[x][y]) {
				setCharAtLocation(x, y, drawBuffer[x][y]);
			}
		}
	}
	//old buffer = draw. draw buffer = old
	char** swap = oldBuffer;
	oldBuffer = drawBuffer;
	drawBuffer = swap;
	
	//oldbuffer which is now draw buffer is already clear.
	//So oldBuffer contains current frame and drawBuffer is clear for drawing.
	
	for(int y = 0; y < bufferHeight; y++) {
		for(int x = 0; x < bufferWidth; x++) {	
			drawBuffer[x][y] = ' ';
		}
	}
	
	//make sure it displays.
	std::cout << std::flush;
	
	
}

int radius(){
	int radius = height/2;
	if(radius*2*yoverx > width) {
		radius = width/2;
	}
	return radius;
}

void drawCircle() {
	
	int r = radius();
	for(int y = 1; y < height; y++){
		//r^2 = (x-width/2)^2 + (y-height/2)^2useep
		//(x-width/2)^2 = r^2 - (y-height/2)^2
		//x-width/2 = sqrt(r^2 - (y-height/2)^2) or -
		//x = width/2 -+ sqrt(r^2 - (y-height/2)^2)
		y--;
		int x1 = width/2 - yoverx*sqrt(r*r - (y-height/2)*(y-height/2));
		int x2 = width/2 + yoverx*sqrt(r*r - (y-height/2)*(y-height/2));
		y++;
		int x3 = width/2 - yoverx*sqrt(r*r - (y-height/2)*(y-height/2));
		int x4 = width/2 + yoverx*sqrt(r*r - (y-height/2)*(y-height/2));
		
		drawLine(x1, y-1, x3, y, drawBuffer);
		drawLine(x2, y-1, x4, y, drawBuffer);
	}
	
	
	
	
}

void drawHandle(double progress, double relLength) {
	int cx = width/2;
	int cy = height/2;
	int r = radius();
	int dx = relLength*yoverx*r*sin(progress*PI*2);
	int dy = relLength*r*cos(progress*PI*2);
	drawLine(cx, cy, cx + dx, cy - dy, drawBuffer);
}



int main() {
	updateDimensions();
	initBuffers();
	clearScreen();
	setCursorInvis();
	
	while(true) {
		updateDimensions();
		if(bufferWidth != width || bufferHeight != height) {
			resizeBuffers();
		}
		drawCircle();
		double secondProg = timeSecond()/(double)60;
		double minProg = timeMinute()/(double)60 + secondProg/(double)60;
		double hourProg = timeHour()/(double)12 + minProg/(double)60;
		drawHandle(minProg,1);
		drawHandle(hourProg,0.5);
		drawHandle(secondProg, 0.25);
		updateTerminal();
		usleep(1000000);
	}
	
	
	
	
	
}
