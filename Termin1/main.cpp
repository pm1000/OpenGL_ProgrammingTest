// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include "Panzer.h"

GLfloat rotate = 0.0;
GLboolean ccw = true;

GLfloat robotY = 0;
GLfloat robotX = 0;

Panzer* panzer;



void keyboard(unsigned char key, int x, int y) {
    GLfloat summand = 1;

    switch (key) {
    case 'a': robotY += 5*summand; break;
    case 'd': robotY -= 5*summand; break;
    case 'w': robotX += summand; break;
    case 's': robotX -= summand; break;
    }
}


void Init()	{

    rotate = 0.0;

    glutKeyboardFunc(keyboard);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

	panzer = new Panzer();
}


void RenderScene() { //Zeichenfunktion
    
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Kamera positionieren
    //gluLookAt(0.0, robotX, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Von Vorne
    //gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Von Rechts
    //gluLookAt(-5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Von Links
    //gluLookAt(5.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Perspektivisch
	gluLookAt(1., 1., 2., 0., 0., 0., 0., 1., 0.);
	

	panzer->show();
    // Alles frehen
    //glRotatef(robotY, 0.0, 1.0, 0.0);


   glutSwapBuffers();
}

void Reshape(int width,int height) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    //gluPerspective(60.0, 1.8, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
}


GLfloat summand = 0.4;

void Animate (int value)     { 
   std::cout << "value=" << value << std::endl;

   //Winkel anpassen
   /*rotate += (ccw) ? -summand : summand ;
   ccw = (rotate < -10) ? false : ccw;
   ccw = (rotate > 10) ? true : ccw;*/


   // RenderScene aufrufen
   glutPostRedisplay();

   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 500;
   glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv) {
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Yannick Brilmayer; Philipp Meier" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
