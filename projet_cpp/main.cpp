///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////PROJET C++//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////2ENA/////////////////////////////////////////////////////////////////////////////////
////////PROUX Alexandre////////LEBECHENNEC Nicolas/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include "Source.h"
#include "Diff.h"


void menu(void);


int main()
{
	menu();
	return 0;
}


void menu(void)
{
	int choix =0;
	cout<< " Bienvenue "<<endl;
	cout<< "Que voulez vous simuler ?"<<endl;
	cout<<endl;
	cout<< " 1/ Fonction type du premier ordre "<<endl;
	cout<< " 2/ Circuit RC "<<endl;
	cout<< " 3/ Circuit RC avec une diode en serie "<<endl;
	cout<< " 4/ Fonction type du 2nd ordre"<<endl;
	cout<< " 5/ RLC serie"<<endl;
	cout<< " 6/ RLC parallele"<<endl;
	cin>> choix;

	Equation_diff *simulation;

	switch (choix)
	{
		case 1:
			simulation = new Fonction1();
	break;
		case 2:
			cout<<"----====-------------"<<endl;
			cout<<"-     R             -"<<endl;
			cout<<"VE                 ___"<<endl;
			cout<<"-                C ___"<<endl;
			cout<<"-                   -"<<endl;
			cout<<"---------------------"<<endl;
			simulation = new RC();
			break;
		case 3:
			cout<<"----====-----|>----------====-----"<<endl;
			cout<<"-     R1            -      R2    -"<<endl;
			cout<<"VE                 ___           -"<<endl;
			cout<<"-                C ___           -"<<endl;
			cout<<"-                   -            -"<<endl;
			cout<<"----------------------------------"<<endl;
			simulation = new RC_diode;
			break;
		case 4:
			simulation = new Fonction2();
			break;
		case 5:
			cout<<"----====-----((((((--------"<<endl;
			cout<<"-     R        L          -"<<endl;
			cout<<"VE                       ___"<<endl;
			cout<<"-                      C ___"<<endl;
			cout<<"-                         -"<<endl;
			cout<<"---------------------------"<<endl;
			simulation = new RLC_serie();
			break;
		case 6:
			cout<<"----====---------------(((((((--"<<endl;
			cout<<"-     R           -      L     - "<<endl;
			cout<<"VE               ___           - "<<endl;
			cout<<"-              C ___           - "<<endl;
			cout<<"-                 -            -"<<endl;
			cout<<"--------------------------------"<<endl;
			simulation = new RLC_parallele();
			break;
		default :;	

	}

	simulation->resolution();
	cout<< " DONE "<<endl;
}
