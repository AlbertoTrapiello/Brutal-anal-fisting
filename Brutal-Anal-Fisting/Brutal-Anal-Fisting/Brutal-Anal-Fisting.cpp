// Brutal-Anal-Fisting.cpp: define el punto de entrada de la aplicación de consola.
//


#include "ETSIDI.h"
#include "glut.h"
#include "Mundo.h"
#include <iostream>


using namespace std;

using namespace ETSIDI;

Mundo mundo;
bool c = true;//ayuda a que no pille los dos clicks 

enum { MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON };
enum { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };

//los callback, funciones que seran llamadas automaticamente por la glut
//cuando sucedan eventos
//NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void onDraw(void); //esta funcion sera llamada para dibujar
void onTimer(int value); //esta funcion sera llamada cuando transcurra una temporizacion
void onKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla	
void onSpecialKeyboardDown(int key, int x, int y); //cuando se pulse una tecla especial	
void OnMouseClick(int button, int state, int x, int y);

int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas GLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("MiJuego");

	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	//Registrar los callbacks
	glutMouseFunc(OnMouseClick);
	glutDisplayFunc(onDraw);
	glutTimerFunc(25, onTimer, 0);//le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutKeyboardFunc(onKeyboardDown);
	glutSpecialFunc(onSpecialKeyboardDown);
	


	mundo.inicializa();
	if (mundo.fin_partida())
		return 0;


	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();

	return 0;
}

void onDraw(void)
{
	//Borrado de la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	mundo.dibuja();
	//Al final, cambiar el buffer (redibujar)
	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}
void onKeyboardDown(unsigned char key, int x_t, int y_t)
{
	//poner aqui el código de teclado
	mundo.tecla(key);

	glutPostRedisplay();
}
void onSpecialKeyboardDown(int key, int x, int y)
{
	mundo.teclaEspecial(key);
	//glutPostRedisplay();
}
void onTimer(int value)
{
	//no borrar estas lineas
	
	mundo.turn();
	glutTimerFunc(25, onTimer, 0);
	glutPostRedisplay();
}


void onMenu(int opcion) {
	switch (opcion) {
	case gest_tropas:
	{
		mundo.idr = 1;
		break;
	}

	case comercio:
	{
		mundo.idr = 2;
		//pensar algo que haga que Accion Engine no apunte a una Accion si no que apunte a un Comercio
		break;
	}
	case Diplom:
	{
		mundo.idr = 3;
		break;
	}
	case mejorar:
	{
		mundo.idr = 4;
		break;
	}
	case Atacar:
	{
		mundo.idr = 5;
		break;
	}
	case Defender:
	{
		mundo.idr = 6;
		break;
	}
	case Generar_tropas:
	{
		mundo.idr = 7;
		break;
	}
	case Alianza:
	{
		mundo.idr = 8;
		break;
	}
	case Guerra:
	{
		mundo.idr = 9;
		break;
	}
	case Ataque:
	{
		mundo.idr = 10;
		break;
	}
	case Defensa:
	{
		mundo.idr = 11;
		break;
	}
	case Agricultura:
	{
		mundo.idr = 12;
		break;
	}
	}
	glutPostRedisplay();
	mundo.click = true;
}

void creacionMenu(void)
{
	int menuPrincipal, menutropas, menudiplomacia, menumejoras;

	menutropas = glutCreateMenu(onMenu);
	glutAddMenuEntry("Atacar", Atacar);//si se pulsa Atacar, idr será igual a 5, conociendo esta informacion, podemos gestionar las distintas acciones
	glutAddMenuEntry("Defender", Defender);
	glutAddMenuEntry("Generar", Generar_tropas);
	menudiplomacia = glutCreateMenu(onMenu);
	glutAddMenuEntry("Alianza", Alianza);
	glutAddMenuEntry("Guerra", Guerra);
	menumejoras = glutCreateMenu(onMenu);
	glutAddMenuEntry("Ataque", Ataque);
	glutAddMenuEntry("Defensa", Defensa);
	glutAddMenuEntry("Agricultura", Agricultura);
	menuPrincipal = glutCreateMenu(onMenu);
	glutAddSubMenu("Gestion de Tropas", menutropas);
	glutAddMenuEntry("Comercio", comercio);
	glutAddSubMenu("Diplomacia", menudiplomacia);
	glutAddSubMenu("Mejoras", menumejoras);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void OnMouseClick(int b, int state, int x, int y)
{
	//////////////
	//captures clicks with mouse with or without special keys (CTRL or SHIFT)
	//gives control to board scene

	bool down = (state == GLUT_DOWN);
	int button;

	if (c)
	{
		if (b == GLUT_LEFT_BUTTON)
		{
			button = MOUSE_LEFT_BUTTON;
			//cout << "MOUSE_LEFT_BUTTON " << "\nX = " << x << "Y = " << y << endl;
		}
		if (b == GLUT_RIGHT_BUTTON)
		{
			button = MOUSE_RIGHT_BUTTON;
			//cout << "MOUSE_RIGHT_BUTTON " << "\nX = " << x << "Y = " << y << endl;
		}
		if (b == GLUT_MIDDLE_BUTTON)
		{
			button = MOUSE_MIDDLE_BUTTON;
			//cout << "MOUSE_MIDDLE_BUTTON " << "\nX = " << x << "Y = " << y << endl;
		}
		if (mundo.get_menu() == 3)
			creacionMenu();
		mundo.raton(button, x, y);
		int specialKey = glutGetModifiers();
		bool ctrlKey = (specialKey & GLUT_ACTIVE_CTRL) ? true : false;
		bool sKey = specialKey & GLUT_ACTIVE_SHIFT;
	}
	c = !c;
	glutPostRedisplay();
}





