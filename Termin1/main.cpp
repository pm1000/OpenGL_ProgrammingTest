// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <vector>
#include "Panzer.h"
#include "Kugel.h"
#include "Kamera.h"
#include <cmath>
#include "GL/SOIL.h"




// Objekte für die Szene vorbereiten
Panzer* panzer;
std::vector <Kugel*> kugeln;
Kamera* kamera;
GLuint ziel;





void keyboard(unsigned char key, int x, int y) {
    std::cout << "key=" << key << std::endl;

    switch (key) {
    case 'a': panzer->setTurmWinkel(panzer->getTurmWinkel() + 2); break;
    case 'd': panzer->setTurmWinkel(panzer->getTurmWinkel() - 2); break;
    case 'w': panzer->setRohrWinkel(panzer->getRohrWinkel() - 2); break;
    case 's': panzer->setRohrWinkel(panzer->getRohrWinkel() + 2); break;
    case ' ': kugeln.push_back(panzer->schiessen()); break;
	case '8': panzer->move('F'); break;
	case '2': panzer->move('B'); break;
	case '4': panzer->move('L'); break;
	case '6': panzer->move('R'); break;
	case '7': panzer->move('G'); break; //gerade drehen
    }
}




void SpecialKey(int key, int x, int y) {

    static float kameraWinkel = 0;
    static const double PI = 3.1415926535897932384626433832795;
	bool arrowSwitch = false;
    switch (key) {
    case GLUT_KEY_RIGHT: kameraWinkel = (kameraWinkel > 360) ? 0: kameraWinkel + 2;
		arrowSwitch = true; break;
    case GLUT_KEY_LEFT: kameraWinkel = (kameraWinkel < 0) ? 359 : kameraWinkel - 2; 
		arrowSwitch = true; break;
	//F keys
	case 1: kamera->setEyePosition(0, 2, 5); break;
	case 2: kamera->setEyePosition(-5, 2, 0); break;
	case 3: kamera->setEyePosition(5, 2, 0); break;
	case 4: kamera->setEyePosition(5, 5, 5); break;
	case 5: kamera->setEyePosition(-5, 5, -5); break;
    }

	if (arrowSwitch) {
		float newZ = cosf(2 * PI * kameraWinkel / 360.0) * 5;
		float newX = sinf(2 * PI * kameraWinkel / 360.0) * 5;

		kamera->setEyePosition(newX, 2, newZ);
	}
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
	GLfloat light_position[] = { 10.0, 10.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // Licht Nr. 0 rechts oben
	glEnable(GL_COLOR_MATERIAL);
	// z-Buffer
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	// Normalen fuer korrekte Beleuchtungs-Berechnung normalisieren
	glEnable(GL_NORMALIZE);

	panzer = new Panzer(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    kugeln = std::vector<Kugel*>();
    kamera = new Kamera(0, 2, 5, 0, 0, 0);
}





void RenderScene() { //Zeichenfunktion

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity ();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen


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

	// Rotierende Platte mit transparenter Textur
	glPushMatrix();
	//zielscheibe
	ziel = SOIL_load_OGL_texture("TREE1.PNG", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, ziel);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	
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
   glFlush();
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
   glutInitWindowSize( 1000, 1000 );         // Fenster-Konfiguration
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
