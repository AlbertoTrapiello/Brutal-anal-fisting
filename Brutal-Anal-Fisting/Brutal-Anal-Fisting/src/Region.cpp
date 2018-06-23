#include "Region.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;


Region::Region()
{
}


Region::~Region()
{
	if (z != NULL)
	{
		for (int i = 0; i < lenght; i++)
			delete[] z[i];
		delete z;
	}
}

void Region::read_file(std::string s)
{
	ifstream f("Regiones.txt", istream::in);
	string str;
	string aux;
	string aux1;
	char token;

	if (!f)
	{
		cout << "el fichero no se ha abierto correctamente" << endl;
		return;
	}
	else
	{

		while (!f.eof())
		{
			getline(f, aux1);
			cout << " aux1:" << str;
			if (s == aux1)
			{
				z = new Zones*[1];
				lenght = 0;
				while (str != "end")
				{
					stringstream sstr;
					getline(f, str);
					sstr << str;
					cout << "lenght=" << lenght << " str:" << str;
					z[lenght] = new Zones;
					sstr >> z[lenght]->x1 >> z[lenght]->y1 >> z[lenght]->x2 >> z[lenght]->y2;
					cout << " x1:" << z[lenght]->x1 << " y1:" << z[lenght]->y1 << " x2:" << z[lenght]->x2 << " y2:" << z[lenght]->y2 << endl;
					lenght++;
				}
			}
		}
		f.close();
	}
}

