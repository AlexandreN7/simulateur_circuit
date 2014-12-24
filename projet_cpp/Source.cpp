#include "Source.h"
#include <math.h>

////////////////////////////////////////////////////////////////

Source::Source()
{
	//ctor
}

/*Source::~Source()
  {
//dtor
}*/
////////////////////////////////////////////////////////////////////




Signal_Noperio::Signal_Noperio()
{
	//ctor
}

/*Signal_Noperio::~Signal_Noperio()
  {
//dtor
}*/





Signal_Perio::Signal_Perio()
{
	//ctor
}


/*Signal_Perio::~Signal_Perio()
  {
//dtor
}*/

/////////////////////////////////////////////////////////////////////////////////////////////


Echelon::Echelon()
{
	int choix =0;
	cout << "Voulez vous la source echelon par defaut (1) ou manuelle (2)" << endl;
	cout <<endl;
	cin >> choix;
	if (choix == 2)
	{
		cout << "entrer le temps de start" <<endl;
		cin >> this->tps_start;
		cout << "entrer l'amplitude" <<endl;
		cin >> this->amp;
		cout << "entrer l'offset" <<endl;
		cin >> this->offset;
	}

	else
	{

		this->offset=0;// par defaut l'offset est nul
		this->amp=1; // l'amplitude est de 1
		this->tps_start=0; // on commence à 0 
	}
}



double Echelon::calcul_tension(double tps)
{
	double valeur = offset;

	if (tps >tps_start)
	{
		valeur = amp+offset;
	}
	else
	{
		valeur=offset;
	}
	return valeur;
}
/*Echelon::~Echelon()
  {
//dtor
}*/

Rectangulaire::Rectangulaire()
{
	int choix = 0;
	cout << "Voulez vous la source rectangulaire par defaut (1) ou manuelle (2)" << endl;
	cout <<endl;
	cin >> choix;
	if (choix == 2)
	{
		cout << "entrer le temps de start" <<endl;
		cin >> this->tps_start;
		cout << "entrer l'amplitude" <<endl;
		cin >> this->amp;
		cout << "entrer l'offset" <<endl;
		cin >> this->offset;
		cout << "entrer la duree" <<endl;
		cin >> this->duree;
	}
	else
	{
		this->tps_start=70e-9;
		this->amp=1;
		this->offset=0;
		this->duree=100e-9;
	}
}

double Rectangulaire::calcul_tension(double tps)
{
	double valeur;
	if ( (tps>tps_start) && (tps<(tps_start+duree))) {
		valeur=offset+amp;
	}

	else {
		valeur = offset;
	}

	return valeur;
}
/*Rectangulaire::~Rectangulaire()
  {
//dtor
}*/

//////////////////////////////////////////////////////////////////////////////////////////////

Sinus::Sinus()
{
	int choix =0;
	cout << "Voulez vous la source sinusoidale par defaut (1) ou manuelle (2)" << endl;
	cout <<endl;
	cin >> choix;
	if (choix == 2)
	{
		cout << "entrer le temps de start" <<endl;
		cin >> this->tps_start;
		cout << "entrer l'amp" <<endl;
		cin >> this->amp;
		cout << "entrer l'offset" <<endl;
		cin >> this->offset;
		cout << "entrer la frequence" <<endl;
		cin >> this->frequency;
	}
	else
	{
		this->tps_start=0; // commence à 0 par defaut
		this->amp=1;  // amplitude de 1
		this->offset=0 ;
		this->frequency=10e6;// 10MHz
	}
}


double Sinus::calcul_tension(double tps)
{
	cout << amp*sin(2*3.14*frequency*(tps + tps_start))+offset<<endl;
	return amp*sin(2*3.14*frequency*(tps + tps_start))+offset;
}
/*Sinus::~Sinus()
  {
//dtor
}*/

Triangulaire::Triangulaire()
{
	int choix =0;
	cout << "Voulez vous la source rectangulaire par defaut (1) ou manuelle (2)" << endl;
	cout <<endl;
	cin >> choix;
	if (choix == 2)
	{
		cout << "entrer le temps de start" <<endl;
		cin >> this->tps_start;
		cout << "amplitude ?" <<endl;
		cin >> this->amp;
		cout << "offset ?" <<endl;
		cin >> this->offset;
		cout << "frequence ?" <<endl;
		cin >> this->frequency;
	}
	else 
	{
		this->tps_start=0;
		this->amp=1;
		this->offset=0;
		this->frequency=10e6; //10 MHz
	}
}




double Triangulaire::calcul_tension(double tps)
{
	double valeur = 0;
	double periode = 1/frequency;

	if (tps >0)
	{
		if ( tps<tps_start)
		{
			tps=tps+periode;
			return offset;
		}
		if (fmod(tps-tps_start,periode) < 0.5*periode)
		{
			valeur = 2*amp*fmod(tps-tps_start,periode)/periode+offset;
		}
		else {
			valeur = -2*amp*fmod(tps-tps_start,periode)/periode+2*amp+offset;
		}

	}
	return valeur;
}
/*Triangulaire::~Triangulaire()
  {
//dtor
}*/

Carre::Carre()
{
	int choix =0;
	cout << "Voulez vous la source carre par defaut (1) ou manuelle (2)" << endl;
	cout <<endl;
	cin >> choix;
	if (choix == 2)
	{
		cout << "entrer le temps de start" <<endl;
		cin >> this->tps_start;
		cout << "amplitude ?" <<endl;
		cin >> this->amp;
		cout << "offset ?" <<endl;
		cin >> this->offset;
		cout << "frequence ?" <<endl;
		cin >> this->frequency;
		cout << "duty cycle ?" <<endl;
		cin >> this->dc;
	}
	else 
	{
		this->tps_start=0;
		this->amp=1;
		this->offset=0;
		this->frequency=10e6; //10 MHz
		this->dc=0.5; // signal créneau
	}
}




double Carre::calcul_tension(double tps)
{
	double valeur = offset;
	double periode = 1/frequency;

	if (tps >0)
	{
		if ( tps<tps_start)
		{
			tps=tps+periode;
			return offset;	
		}
		if (fmod(tps-tps_start,periode) < dc*periode)
		{
			valeur = amp+offset;
		}
		else {
			valeur = offset;
		}

	}
	return valeur;
}
/*Carre::~Carre()
  {
//dtor
}*/
















