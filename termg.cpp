#include "termg.h"

#include <stdio.h>//printf()
#include <iostream>//terminal manipulation
#include <sys/ioctl.h>//screendim
#include <unistd.h>//screendim
#include <algorithm>//min,max

using namespace std;
void setCursor(int x, int y) {
	printf("\033[%d;%dH",y+1,x+1);
}

void setCharAtLocation(int x, int y, char c, char** array) {
	x = min(x,bufferWidth-1); x = max(0,x);
	y = min(y,bufferHeight-1); y = max(0,y);
	array[x][y] = c;
}

void setCharAtLocation(int x, int y, char c) {
	x = max(0,x);
	y = max(0,y);
	setCursor(x,y);
	printf("%c",c);
}

void clearScreen() {
	cout << "\033[2J";
}

void setCursorInvis() {
	//make cursor invisible
	cout << "\033[?25l";
}

void getScreenDim(int* sizeArr) {
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	sizeArr[0] = size.ws_col;
	sizeArr[1] = size.ws_row;
	sizeArr[2] = size.ws_xpixel;
	sizeArr[3] = size.ws_ypixel;
}

void drawLine(int a,int b, int c, int d) {
	drawLine((double)a,(double)b,(double)c,(double)d);
}

void drawLine(double p1x, double p1y, double p2x, double p2y) {
	if(p1x==p2x && p1y==p2y) {
		setCharAtLocation(p1x, p1y, '&');
	} else if(p1x == p2x) {
		bool up = p1y < p2y;
		for(int y = p1y; up ? y <= p2y : y >= p2y; up ? y++ : y--) {
			setCharAtLocation(p1x, y, '&');
		}
	} else if(p1y == p2y) {
		bool up = p1x < p2x;
		for(int x = p1x; up ? x <= p2x : x >= p2x; up ? x++ : x--) {
			setCharAtLocation(x, p1y, '&');
		}
	} else {
		bool smallest = p1x<p2x;
		int l = smallest ? p1x : p2x;
		int r = !smallest ? p1x : p2x;
		int startY = smallest ? p1y : p2y;
		int endY = !smallest ? p1y : p2y;
		
		double slope = (double)(endY-startY)/(r-l);
		if(abs(slope) <= 1){
			double y = 0;
			int yi = 0;
			int ydir = slope > 0 ? 1 : -1;
			for(int x = l; x <= r; x++) {
				setCharAtLocation(x, startY + yi, '&');
				y += slope;
				if (abs(y) >= 0.5) {
					yi += ydir;
					y -= ydir;
				}
			}
		} else {
			bool smallest = p1y<p2y;
			int b = smallest ? p1y : p2y;
			int t = !smallest ? p1y : p2y;
			int startX = smallest ? p1x : p2x;
			int endX = !smallest ? p1x : p2x;
			
			slope = (double)(endX-startX)/(t-b);
			
			double x = 0;
			int xi = 0;
			int xdir = slope > 0 ? 1 : -1;
			for(int y = b; y <= t; y++) {
				setCharAtLocation(startX + xi, y, '&');
				x += slope;
				if (abs(x) >= 0.5) {
					xi += xdir;
					x -= xdir;
				}
			}
		}
		
		
		
	}
}

void drawLine(int a,int b, int c, int d, char** arr) {
	drawLine((double)a,(double)b,(double)c,(double)d, arr);
}

void drawLine(double p1x, double p1y, double p2x, double p2y, char** arr) {
	if(p1x==p2x && p1y==p2y) {
		setCharAtLocation(p1x, p1y, '&', arr);
	} else if(p1x == p2x) {
		bool up = p1y < p2y;
		for(int y = p1y; up ? y <= p2y : y >= p2y; up ? y++ : y--) {
			setCharAtLocation(p1x, y, '&', arr);
		}
	} else if(p1y == p2y) {
		bool up = p1x < p2x;
		for(int x = p1x; up ? x <= p2x : x >= p2x; up ? x++ : x--) {
			setCharAtLocation(x, p1y, '&', arr);
		}
	} else {
		bool smallest = p1x<p2x;
		int l = smallest ? p1x : p2x;
		int r = !smallest ? p1x : p2x;
		int startY = smallest ? p1y : p2y;
		int endY = !smallest ? p1y : p2y;
		
		double slope = (double)(endY-startY)/(r-l);
		if(abs(slope) <= 1){
			double y = 0;
			int yi = 0;
			int ydir = slope > 0 ? 1 : -1;
			for(int x = l; x <= r; x++) {
				setCharAtLocation(x, startY + yi, '&', arr);
				y += slope;
				if (abs(y) >= 0.5) {
					yi += ydir;
					y -= ydir;
				}
			}
		} else {
			bool smallest = p1y<p2y;
			int b = smallest ? p1y : p2y;
			int t = !smallest ? p1y : p2y;
			int startX = smallest ? p1x : p2x;
			int endX = !smallest ? p1x : p2x;
			
			slope = (double)(endX-startX)/(t-b);
			
			double x = 0;
			int xi = 0;
			int xdir = slope > 0 ? 1 : -1;
			for(int y = b; y <= t; y++) {
				setCharAtLocation(startX + xi, y, '&', arr);
				x += slope;
				if (abs(x) >= 0.5) {
					xi += xdir;
					x -= xdir;
				}
			}
		}
		
		
		
	}
}
