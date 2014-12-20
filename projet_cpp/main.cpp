#include <iostream>
#include "Source.h"
#include "Diff.h"




int main()
{
	// valeur par defaut

	double N = 1e-9; // Pas de calcul
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


  /*  Carre signal;
	for (double i = 0 ; i< 1 ; i=i+0.01)
	{
    signal.calcul_tension(i);

	}*/
        
 

   // Equation_diff *patate;
   // patate = new Equation_diff();
   // patate->resolution();

   Equation_diff *patate;
   patate=new RC();
   patate->resolution();

//	   Equation_diff *patate;
//   patate=new RLC_parallele();
 // patate->resolution();
    return 0;
}
