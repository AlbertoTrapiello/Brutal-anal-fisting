#pragma once
#include <iostream>
#include <math.h>

using namespace std;

class IAcci�n
{
public:
	int id;
	int submenu;
	virtual ostream& print_options (ostream& o = cout)=0;
	virtual int get_option(istream& i) = 0;//gestiona la oci�n elegida por elusuario. Inicialmente por teclado posteriormente con rat�n
	virtual int check(int option) = 0;//checkea la viabilidad de la acci�n

};


class Gesti�n_tropas : public  IAcci�n
{
public:
	bool atacar;

	Gesti�n_tropas();
	ostream& print_options(ostream& o = cout);
	int get_option(istream& i);
	int check(int option);
};

class Comercio : protected IAcci�n
{
public:
	ostream& print_options(ostream& o = cout);
	int get_option(istream& i);
	int check(int option);
};

class Diplomacia : protected IAcci�n
{
public:
	ostream& print_options(ostream& o = cout);
	int get_option(istream& i);
	int check(int option);
};
class Acci�n_Engine
{
	IAcci�n* a;
public:
	Acci�n_Engine(IAcci�n* a): a(a) {}
	ostream & operator<<(ostream& o);
	ostream& print_options(ostream& o = cout);
	int get_option(istream& i = cin);
	int check(int option);
};