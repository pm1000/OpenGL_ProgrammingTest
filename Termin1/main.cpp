// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <vector>
#include "Panzer.h"
#include "Kugel.h"
#include "Kamera.h"
#include <cmath>



// Objekte für die Szene vorbereiten
Panzer* panzer;
std::vector <Kugel*> kugeln;
Kamera* kamera;





void keyboard(unsigned char key, int x, int y) {
    std::cout << "key=" << key << std::endl;

    switch (key) {
    case 'a': panzer->setTurmWinkel(panzer->getTurmWinkel() + 2); break;
    case 'd': panzer->setTurmWinkel(panzer->getTurmWinkel() - 2); break;
    case 'w': panzer->setRohrWinkel(panzer->getRohrWinkel() - 2); break;
    case 's': panzer->setRohrWinkel(panzer->getRohrWinkel() + 2); break;
    case ' ': kugeln.push_back(panzer->schiessen()); break;
    case '0': kamera->setEyePosition(0, 2, 5); break;
    case '1': kamera->setEyePosition(-5, 2, 0); break;
    case '2': kamera->setEyePosition(5, 2, 0); break;
    case '3': kamera->setEyePosition(5, 5, 5); break;
    case '4': kamera->setEyePosition(-5, 5, -5); break;
    }
}




void SpecialKey(int key, int x, int y) {

    static float kameraWinkel = 0;
    static const double PI = 3.1415926535897932384626433832795;

    switch (key) {
    case GLUT_KEY_RIGHT: kameraWinkel = (kameraWinkel > 360) ? 0: kameraWinkel + 2; break;
    case GLUT_KEY_LEFT: kameraWinkel = (kameraWinkel < 0) ? 359 : kameraWinkel - 2; break;
    }

    float newZ = cosf(2 * PI * kameraWinkel / 360.0) * 5;
    float newX = sinf(2 * PI * kameraWinkel / 360.0) * 5;

    kamera->setEyePosition(newX, 2, newZ);
}





void Init()	{

    glClearColor(1.0, 1.0, 1.0, 1.0);

    //glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

	// Licht
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	// z-Buffer
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	// Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
	glEnable(GL_NORMALIZE);


	panzer = new Panzer(0.0, 0.0, 0.0, 0.0, 0.0);
    kugeln = std::vector<Kugel*>();
    kamera = new Kamera(0, 2, 5, 0, 0, 0);
}





void RenderScene() { //Zeichenfunktion
    
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Kamera positionieren
    kamera->show();

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
   glutSpecialFunc(SpecialKey);


   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
