void setCursor(int x, int y);

extern int width, height;
extern int bufferWidth, bufferHeight;

void setCharAtLocation(int x, int y, char c, char** array);
void setCharAtLocation(int x, int y, char c);

void clearScreen();

void setCursorInvis();

void getScreenDim(int* sizeArr);

double abs(double num);

void drawLine(int a,int b, int c, int d);
void drawLine(double p1x, double p1y, double p2x, double p2y);
void drawLine(int a,int b, int c, int d, char** arr);
void drawLine(double p1x, double p1y, double p2x, double p2y, char** arr);

#define yoverx 2
