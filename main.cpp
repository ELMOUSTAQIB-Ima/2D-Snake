#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include<stdlib.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 10 //not to slow or two fast

extern short sDirection;
bool gameOver=false;

int score=0;

void timer_callback(int);
void display_callback();
void reshape_callback(int,int);//la fonction de rappel de redimensionnement de la fenetre courante
void keyboard_callback(int,int,int);

void init(){
    glClearColor(0.0,0.0,0.0,1.0);
    initGrid(COLUMNS,ROWS);
}

int main(int argc,char **argv){

    glutInit(&argc,argv);//initialize the GLUT library
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    glutMainLoop();
    return 0;
}

int index=0;
void display_callback(){

    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    /** exemple
    glRectd(index,20,index+2,22);
    index++;
    if(index>40)
    {
        index=0;
    }*/
    drawSnake();
    drawFood();
    glutSwapBuffers();
    if(gameOver)
    {
        char _score[10];
        itoa(score,_score,10);//convert integer to string and stores the result in the array _store
        char text[50]= "Your score: ";
        strcat(text,_score); //add the string _score to text
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
    }


}

void reshape_callback(int w,int h){

      glViewport(0,0,(GLsizei)w,(GLsizei)h);//pour le plan normal de la fenetre courante
      glMatrixMode(GL_PROJECTION);//la matrice de projection devient la matrice courante
      glLoadIdentity();//on initialise la matrice de projection
      glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);//glOrtho(gauche, droit, bas, haut, proche, loin);
      glMatrixMode(GL_MODELVIEW);//matrice de positionnement de la vue

}

void timer_callback(int)
{
    glutPostRedisplay();//pour rafraichir l'affichage
    //we want 10 frames in a seconde
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void keyboard_callback(int key,int,int)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN)
            sDirection=UP;
            break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
            break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
            break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
            break;
    }

}





