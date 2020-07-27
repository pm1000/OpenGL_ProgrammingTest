// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <vector>
#include "Panzer.h"
#include "Kugel.h"



// Objekte für die Szene vorbereiten
Panzer* panzer;
std::vector <Kugel*> kugeln;





void keyboard(unsigned char key, int x, int y) {
    std::cout << "key=" << key << std::endl;

    switch (key) {
    case 'a': panzer->setTurmWinkel(panzer->getTurmWinkel() + 2); break;
    case 'd': panzer->setTurmWinkel(panzer->getTurmWinkel() - 2); break;
    case 'w': panzer->setRohrWinkel(panzer->getRohrWinkel() - 2); break;
    case 's': panzer->setRohrWinkel(panzer->getRohrWinkel() + 2); break;
    case ' ': kugeln.push_back(panzer->schiessen()); break;
    }
}





void Init()	{

    glClearColor(1.0, 1.0, 1.0, 1.0);

    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

	panzer = new Panzer(0.0, 0.0, -5.0, 0.0, 0.0);
    kugeln = std::vector<Kugel*>();
}





void RenderScene() { //Zeichenfunktion
    
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Kamera positionieren
	gluLookAt(2.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Boden zeichnen
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f(100.0, 0.0, 100.0);
    glVertex3f(100.0, 0.0, -100.0);
    glEnd();
	
    // Panzer-Zeichenfunktion aufrufen, vorher Panzer ein bisschen nach hinten verschieben
    glPushMatrix();
	panzer->show();
    glPopMatrix();


    // Alle Kugeln, die existieren zeichnen lassen
    for (int i = kugeln.size()-1; i >= 0; i--) {
        Kugel* k = kugeln[i];
        k->show();
    }


   glutSwapBuffers();
}





void Reshape(int width,int height) {

    // Set the current ratio for the current window resolution
    double aspect = (float) width / (float) height;
    std::cout << "width=" << width << " height=" << height << " aspect=" << aspect << std::endl;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    gluPerspective(60.0, aspect, 0.1, 40.0);
    glMatrixMode(GL_MODELVIEW);
}





void animate (int value)     { 
   std::cout << "value=" << value << std::endl;

   // RenderScene aufrufen
   glutPostRedisplay();

   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 10;
   glutTimerFunc(wait_msec, animate, ++value);
}





int main(int argc, char **argv) {

   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
   glutInitWindowSize( 600, 600 );         // Fenster-Konfiguration
   glutCreateWindow( "Yannick Brilmayer; Philipp Meier" );   // Fenster-Erzeugung


   // Zeichen und Reaktionsfunktionen bekannt machen
   glutDisplayFunc(RenderScene);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(keyboard);


   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
