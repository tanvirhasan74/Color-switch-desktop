#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include <time.h>
#include<windows.h>
#include<mmsystem.h>
#include<sstream>
#include<string.h>


using namespace std;
void update(int);
void update2(int);
int gameover(int);
float moveball=-2.5f;
int viewmove=0;



float limit=0;
float range=0;
float speed=0.0f;
int flag=0;
int cnt=0;
int r,g,b;
float trans=0;
float tr1=.8,tr2=6.3;
 int v1=0;
 char quote[6][180];
int numberOfQuotes = 0;
float view = 10.0;
GLfloat upwardsScrollVelocity = -10.0;


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}
void sprint( float x, float y, string st)
{
    int l,i;
//    l=strlen( st ); // see how many characters are in text string.
    glColor3f(1.0,1.0,1.0);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i <  st.length(); i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }


}
void sprint2( float x, float y, string st)
{
    int l,i;
//    l=strlen( st ); // see how many characters are in text string.
    glColor3f(1.0,1.0,1.0);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i <  st.length(); i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }
    //st="";

}
//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0,00, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 1.0, 200);
}

float _angle1 = 0.0f;
//float _move = 0.0f;
void Torus2d
    (
    float angle,            // starting angle in radians
    float length,           // length of arc in radians, >0
    float radius,           // inner radius, >0
    float width,            // width of torus, >0
    unsigned int samples    // number of circle samples, >=3
    )
{
   // if( samples < 3 ) samples = 3;
    const float outer = radius + width;
    glBegin( GL_QUAD_STRIP );
    for( unsigned int i = 0; i <= samples; ++i )
    {
        float a = angle + ( i / (float)samples ) * length;
        glVertex2f( radius * cos( a ), radius * sin( a ) );
        glVertex2f( outer * cos( a ), outer * sin( a ) );
    }
    glEnd();
}
void rectanglepixel(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();

}
void trianglepixel(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();

}


void rectangle()
{
    glColor3ub( 255, 0, 0 );
    trianglepixel(-1,-1,1,-1,.7,-.7,-.7,-.7);
    glColor3ub( 0, 255, 0 );
    trianglepixel(.7,-.7,1,-1,1,1,.7,.7);
    glColor3ub( 0, 0, 255 );
    trianglepixel(.7,.7,1,1,-1,1,-.7,.7);
    glColor3ub( 255, 0, 255);
    rectanglepixel(-1,1,-1,-1,-.7,-.7,-.7,.7);

}
void triangle()
{
    glColor3ub( 255, 0, 0 );
   trianglepixel(0,0,3,0,2.567,.25,.433,.25);
    glColor3ub( 0, 255, 0 );
    trianglepixel(2.567,.25,3,0,1.5,2.6,1.5,2.1);
    glColor3ub( 0, 0, 255 );
    trianglepixel(1.5,2.6,1.5,2.1,.433,.25,0,0);

}


void ring()
{
    glColor3ub( 255, 0, 0 );
    Torus2d( 0, 1.57079633, 1, 0.3, 40 );
    glColor3ub( 0, 255, 0 );
     Torus2d( 1.57, 1.57079633, 1, 0.3, 40 );
      glColor3ub( 255, 0, 255 );
     Torus2d( 3.14, 1.57079633, 1, 0.3, 40 );
     glColor3ub( 0, 0, 255);
     Torus2d( 4.71, 1.57079633, 1, 0.3, 40 );
}


void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3d(1,0,0);
	glLoadIdentity(); //Reset the drawing perspective
	glMatrixMode(GL_MODELVIEW);

    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;
    glOrtho( -4 * ar, 4 * ar, -4, 4, -1, 1);

   // glRotatef(_angle, 1.0f, 0.0f, 0.0f); //Rotate the camera
///////////////////// Earth ///////////////////////////
    glPushMatrix(); //Save the current state of transformations
	 //Move to the center of the triangle
	//glRotatef(_angle1, 0.0, 0.0, 1.0);
	//glTranslatef(0.8, 0.0, 0.0);//Rotate about the the vector (1, 2, 3)
	/*glColor3f(1.0,1.0,0.0);
	glBegin(GL_POLYGON);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.15;
		float x = r * cos(A);
		float y = r * sin(A);
		//glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();*/
///////////////////// Orbit ///////////////////////////
   /* glPushMatrix();
    glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/50 ;
		float r=0.8;
		float x = r * cos(A);
		float y = r * sin(A);
		//glVertex2f(x,y );
	}
	glEnd();
    glPopMatrix();*/



///////////////////// ball ///////////////////////////
    glPushMatrix();
        glColor3ub(255,0,0);
        glTranslatef(0,moveball,0);
        glutSolidSphere(.1,100,100);
    glPopMatrix();

     glPushMatrix();
     glTranslatef(0,tr1-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);
     rectangle();
     glPopMatrix();


     glPushMatrix();
     glColor3ub(255,255,255);
     ostringstream cnvrt;
     cnvrt << cnt;
     sprint(-3.5,3.5,"SCORE: "+cnvrt.str());
    // sprint2(-2.5,3.5,cnvrt.str());
     //cnvrt.str()="";
    //sprint(-2.9,3.5,score);
     glPopMatrix();


    if(moveball>=3)
    {
            trans=5.5;
            moveball=-2.5;
             v1=(rand() % 3 )+ 1;
             ++cnt;

    }
    if(v1==2)
    {
     glPushMatrix();
     glTranslatef(0,tr2-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);
     ring();
     glPopMatrix();
    }
    else if(v1==1)
    {
    glPushMatrix();
     glTranslatef(0,tr2-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);
     rectangle();
     glPopMatrix();
    }
    else if(v1==3)
    {
     glPushMatrix();
     glTranslatef(0,tr2-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);

     glTranslatef(-1.5,-.867,0);
     triangle();
     glPopMatrix();
    }

     /*glPushMatrix();
     glTranslatef(0,tr1-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);
     ring();
     glPopMatrix();*/

    /* glPushMatrix();
     glTranslatef(0,tr2-trans,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);
     rectangle();
     glPopMatrix();*/
     /*glPushMatrix();

     glTranslatef(0,.8,0);
     glRotatef(_angle1, 0.0, 0.0, 1.0);

     glTranslatef(-1.5,-.867,0);
     triangle();
     glPopMatrix();*/

    /*
    else if(v1==3)
    {

    }*/
    //glFlush();

	glutSwapBuffers();
}
void reshape2(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}

void timeTick(void)
{
	if (upwardsScrollVelocity < -600)
    {
        view -= 0.000011;
    }
	if (view < 0)
    {
        view = 20;
        upwardsScrollVelocity = -10.0;
    }
	//exit(0);
	upwardsScrollVelocity -= 0.1;
	glutPostRedisplay();
}
void renderToDisplay()
{
	int i, l, lenghOfQuote;

	glTranslatef(0.0, -100, upwardsScrollVelocity);
	glRotatef(-20, 1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);

	for (l = 0; l < numberOfQuotes; l++)
	{
		lenghOfQuote = (int)strlen(quote[l]);
		glPushMatrix();
		glTranslatef(-(lenghOfQuote * 37), -(l * 200), 0.0);
		for (i = 0; i < lenghOfQuote; i++)
		{
			glColor3f((upwardsScrollVelocity / 10) + 300 + (l * 10), (upwardsScrollVelocity / 10) + 300 + (l * 10), 0.0);
			glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
		}
		glPopMatrix();
	}
}
void myDisplayFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 30.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	renderToDisplay();
	glutSwapBuffers();
}


int gameOver()
{   ostringstream cnrt;
     cnrt << cnt;
    string message = "Your Score is: " + cnrt.str();
	numberOfQuotes = 3;

	strcpy(quote[0], "Cross the Road");
	strcpy(quote[1], "Game Over");
	//strcpy(quote[2], message.c_str());

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(1360, 750);
	glutCreateWindow("Game Result");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3);

	glutDisplayFunc(myDisplayFunction);
	glutReshapeFunc(reshape2);
	glutIdleFunc(timeTick);
return 0;
	//glutMainLoop();

}

void specialKeys(int key, int x, int y) {
    switch (key) {
      case GLUT_KEY_UP:
          speed=0.02f;
          limit=0;
          flag=0;
          //wait(500);

          //update2(0);
          break;
    }
}

void update(int value) {

	_angle1 += 1.5;
	//cout<<_angle1<<endl;
	/*if (_angle1 > 360) {
		_angle1 -= 360;
	}*/
	//if(moveball==
	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(20, update, 0);
}

void update2(int value)
{
            if(flag==0)
        {
            moveball+=speed;
            limit=limit+speed;
            if(limit>=0.7)
            {
                flag=1;
            }

        }
         if(flag==1)
        {
            moveball-=speed;
            limit-=speed;
        }

        if(moveball<-2.6)
        {   //int gameover();
            exit(0);

        }

            unsigned char pixel[3];
            int col1=(4+moveball)*100;
            int col2=(4+moveball)*100;
            int col3=(4+moveball)*100;

            cout<<col1<<endl;
            cout<<col2<<endl;
            glReadPixels(400,col1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
             r=(int)pixel[0];
             g=(int)pixel[1];
             b=(int)pixel[2];
            cout<<r<<endl;
            cout<<g<<endl;
            cout<<b<<endl;
            if((r==0 && g == 255 && b==0)|| (r==0 && g == 0 && b==255)|| (r==255 && g == 0 && b==255) )
            {
                //int gameover();
                exit(0);
            }
            glReadPixels(400,col2, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            r=(int)pixel[0];
             g=(int)pixel[1];
             b=(int)pixel[2];
            if((r==0 && g == 255 && b==0)|| (r==0 && g == 0 && b==255)|| (r==255 && g == 0 && b==255) )
            {
                //int gameover();
                exit(0);
            }
            glReadPixels(400,col3, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            r=(int)pixel[0];
             g=(int)pixel[1];
             b=(int)pixel[2];
            if((r==0 && g == 255 && b==0)|| (r==0 && g == 0 && b==255)|| (r==255 && g == 0 && b==255) )
            {
                //int gameover();
                exit(0);
            }
            glReadPixels(400,col3, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            r=(int)pixel[0];
             g=(int)pixel[1];
             b=(int)pixel[2];
            if((r==0 && g == 255 && b==0)|| (r==0 && g == 0 && b==255)|| (r==255 && g == 0 && b==255) )
            {
                //int gameover();
                exit(0);
            }
        glutPostRedisplay();
        glutTimerFunc(5, update2, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	//Create the window
	glutCreateWindow("Transformation");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(specialKeys);
	sndPlaySound("color_switch.wav",SND_ASYNC|SND_LOOP);//Play background music

	glutTimerFunc(20, update, 0);
	glutTimerFunc(5, update2, 0);
	 //Add a timer

	glutMainLoop();
	return 0;
}









