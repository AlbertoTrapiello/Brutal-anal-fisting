// Brutal-Anal-Fisting.cpp: define el punto de entrada de la aplicación de consola.
//
#include <iostream>
#include "Accion.h"


using namespace std;

int main()
{
	Gestión_tropas g;
	int option=0;
	int i = 0;
	do
	{
		g.print_options();
		option=g.get_option(cin);
		cout << "La opción ha sido: " << option << endl;
		i++;
	} while (i<3);
	system("PAUSE");
	return 0;
}