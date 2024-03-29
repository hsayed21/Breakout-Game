#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <sstream>

#define drawW 180
#define drawH 180
#define PI 3.14159265358979323846

double speed_key = 26;
float p1=50,p2=50;
bool stop=false ;
double ball_x = 0, ball_y = 0;
double ball2_x = 0, ball2_y = 50;
double x_velocity1 = 8.0;
double y_velocity1 = 1.0;
double x_velocity2 = 10.0;
double y_velocity2 = 3.0;
int score = 0;

using namespace std;

////////////////////////////////////////////////////////////////////////////////
GLfloat black[3] = { 0.0, 0.0, 0.0 };
GLuint fontOffset;
GLubyte space[] = 
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
GLubyte letters[][13] = {
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18}, 
{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc}, 
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff}, 
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff}, 
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e}, 
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e}, 
{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06}, 
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3}, 
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0}, 
{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3}, 
{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3}, 
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e}, 
{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c}, 
{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe}, 
{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e}, 
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff}, 
{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3}, 
{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3}, 
{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff}
};
void makeRasterFont(void)
{
   GLuint i, j;
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

   fontOffset = glGenLists (128);
   for (i = 0,j = 'A'; i < 26; i++,j++) {
      glNewList(fontOffset + j, GL_COMPILE);
      glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
      glEndList();
   }
   glNewList(fontOffset + ' ', GL_COMPILE);
   glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
   glEndList();
}
void init(void)
{
   glShadeModel (GL_FLAT);
   makeRasterFont();
}
void printString(char *s)
{
   char text[256];
   glPushAttrib (GL_LIST_BIT);
   glListBase(fontOffset);
   glCallLists((GLsizei) strlen(s), GL_UNSIGNED_BYTE, (GLubyte *) s);
   glPopAttrib ();
}
/* Everything above this line could be in a library 
 * that defines a font.  To make it work, you've got 
 * to call makeRasterFont() before you start making 
 * calls to printString().
 */
////////////////////////////////////////////////////////////////////////////////

void game_over_string(){
	// Display when Game Over
	   glColor3fv(black);
	   glRasterPos2i(-15, 0);
	   printString("GAME OVER");
	   glRasterPos2i(-15, -15);
	   printString("PRESS R TO RESTART");
	   glRasterPos2i(-15, -30);
	   printString("YOUR SCORE IS ");
}
string arr_score(int a){
	//convert int to str to used it in glutBitmapCharacter
	int i = a;
	std::string out_string;
	std::stringstream s;
	s << i;
	out_string = s.str();
	return out_string;
} 
void drawCircle(double cx, double cy, double radius)
{
	double steps = 30;
	double delta = 2 * PI / steps;
	glBegin(GL_TRIANGLE_FAN);
	double angle = 0;
	glVertex2f(cx, cy);
	for (int i = 0; i <= steps; i++){
		double x = cx + radius * cos(angle);
		double y = cy + radius * sin(angle);
		glVertex2f(x, y);
		angle += delta;}
	glEnd();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	if(stop==false){
		//draw breakout
	   glLineWidth(20);
		glColor3d(0,0,0);
		glBegin(GL_LINES);
			glVertex2f(-p1,-120);
			glVertex2f(p2,-120);
		glEnd();
		//draw border
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glColor3d(0,0,0);
			glVertex2d(-180,180);  
			glVertex2d( 180,180);  
			glVertex2d( 180,-180); 
			glVertex2d( -180, -180);
		glEnd();

		glColor3f(0, 0, 1);					//blue
		drawCircle(ball_x, ball_y, 20);		//ball 1
		glColor3f(1, 0, 0);					//red
		drawCircle(ball2_x, ball2_y, 20);	//ball 2
	}
	else{
		//draw border
		glLineWidth(7);
		glBegin(GL_LINE_LOOP);
		glColor3d(0,0,0);
			glVertex2d(-180,180);  
			glVertex2d( 180,180);  
			glVertex2d( 180,-180); 
			glVertex2d( -180, -180);
		glEnd();
		game_over_string();
	
		if(score-2 < 0){score=0;}
		else{score = score - 2;}

		glColor3d(1,0,0);
		//if use array_score to display numbers on screen
		glRasterPos2i(52, -31);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,arr_score(score)[0]);
	}

	glFlush();

	if (stop==false )
		glutPostRedisplay();

}
void timer(int val)
{
	////// Ball 1 ///////
	ball_x += x_velocity1;
	ball_y += y_velocity1;
	//collison with border
	if (ball_x + 20 >= 175 || ball_x - 20 <= -175){ x_velocity1 *= -1; }
	if (ball_y + 20 >= 175 || ball_y - 20 <= -175){ y_velocity1 *= -1; score+=1; }
	//collision with breakout
	if (ball_y - 20 <= -120){
		if(ball_x >= -p1 && ball_x + 20 <=p2)
			y_velocity1 *= -1;}
	if (ball_x + 20 >= -120 && ball_x + 20 <= -175){
		if(ball_x >= -p1 && ball_x + 20 <=p2)
			y_velocity1 *= -1;}
	//stop game at -160 or less (Game Over) Ball 1
	if (ball_y - 20 <= -160){ stop=true; }


	////// Ball 2 ///////
	ball2_x += x_velocity2;
	ball2_y += y_velocity2;
	//collison with border
	if (ball2_x + 20 >= 175 || ball2_x - 20 <= -175){ x_velocity2 *= -1; }
	if (ball2_y + 20 >= 175 || ball2_y - 20 <= -175){ y_velocity2 *= -1;score+=1; }
	//collision with breakout
	if (ball2_y - 20 <= -120){
		if(ball2_x+20>= -p1+10 && ball2_x-20 <=p2-10)
			y_velocity2 *= -1;}
	if (ball2_x + 20 >= -120 && ball2_x - 20 <= -175){
		if(ball2_x - 20 >= -p1 && ball2_x + 20 <=p2)
			y_velocity2 *= -1;}
	//stop game at -160 or less (Game Over) Ball 2
	if (ball2_y - 20 <= -160){ stop=true; }

	// Game Over (if false continue else if true stop)
	if (stop==false)
		glutPostRedisplay();
		glutTimerFunc(40, timer, 0);
}
void move_left(){
if (p1>-165 ){
	p1+=speed_key;
	p2-=speed_key;}
if (p2<-100){
	p2+=speed_key;
	p1-=speed_key;}
}
void move_right(){
if (p2<165 ){
	p2+=speed_key;
	p1-=speed_key;}
else if (p1>100){
	p1+=speed_key;}
}
void keyboard(unsigned char key, int x, int y)
{
   if ( key==27) exit(0); //Exit From Game
	else if ( key== 'r' ){  //Restart Game
	stop=false;
	score=0;
	p1=50,p2=50;
	ball_x = 0;
	ball_y = 30;	
	ball2_x = 0;
	ball2_y = 50;
	x_velocity1 = 2.8;
	y_velocity1 = 0.8;
	x_velocity2 = 3.7;
	y_velocity2 = 1.2;
	glutPostRedisplay();
	glutTimerFunc(30, timer, 0);
	}
	else if ( key== 'a' ) move_left(); //left
	else if ( key== 'd' ) move_right(); //right
	if (stop==false)
		glutPostRedisplay();

}
void reshape(int width, int height)
{
	//set the coordinates and size of the viewing area on the window
	glViewport(0, 0, width, height);

	// Start modifying the projection matrix.
	glMatrixMode(GL_PROJECTION);
	//glMatrixMode(GL_MODELVIEW);

	// Reset the matrix
	glLoadIdentity();

	// set the displayed area
	float ratio = (float)width / height; //aspect ratio
	if (width > height)
	{
		glOrtho(-drawW * ratio, drawW * ratio, -drawH, drawH, -1, 1);
	}
	else
	{
		glOrtho(-drawW, drawW, -drawH / ratio, drawH / ratio, -1, 1);
	}

	//set the default buffer color
	glClearColor(1, 1, 1, 1);

}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(1000, 800);
   glutInitWindowPosition (200, 0);
   glutCreateWindow("Breakout");
   init();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutTimerFunc(50, timer, 0);
   glutMainLoop();
   return 0;
}
