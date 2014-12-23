#include <iostream>
#include "Source.h"
#include "Diff.h"


void menu(void);


int main()
{
	// valeur par defaut

/*	double N = 1e-9; // Pas de calcul
	double borne_sup = 500e-9; // Temps max
	double condition1 = 0; // Première condition initiale 
	double condition2 = 0; // Seconde condition initiale
	double R = 50; // Resistance circuit RC
	double C = 1e-9; // Condensateur circuit RC et RC_diode
	double R1 = 36; // Première resistance du circuit RC_diode
	double R2 = 180; // Seconde resistance du circuit RC_diode
	double lambda = 1;
	double R3 = 120; // Resistance du circuit RLC_série
	double C1 = 0.1e-9; // Condensateur du circuit RLC_série
	double L = 1e-6; // Bobine du circuit RLC_série
	double R4 = 1.2; // Resistance du circuit RLC_parallèle
	double C2 = 0.1e-6; // Condensateur du circuit RLC_parallèle
	double L1 = 10e-9; // Bobine du circuit RLC_parallèle
*/
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
