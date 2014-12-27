#include "Diff.h"
#include "Source.h"
#include <math.h>
#include <iostream>
#include <fstream>


using namespace std;

Equation_diff::Equation_diff()
{
    int choix = 0;
    cout << "Entree le pas de calcul"<<endl;
    cin >>  this->N;
    cout << "Temps maximal ?"<<endl;
    cin >>  this->borne_sup;
    cout << " Choisissez la source: sinus(1), pwm(2) ,triangulaire(3) ,rectangulaire(4) ,echelon(5)" << endl;
    cin >> choix;

    switch ( choix) // choix du type de source 
    {
        case 1 : signal = new Sinus(); break;
        case 2 : signal = new Carre(); break;
        case 3 : signal = new Triangulaire(); break;
        case 4 : signal = new Rectangulaire(); break;
        case 5 : signal = new Echelon(); break;

    }
}

Equation_diff::Equation_diff(double pas ,double borne)
{
    this->N=pas;
    this->borne_sup=borne;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ORDRE1/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ordre1::Ordre1()
{	cout << "Entree votre condition initiale"<<endl;
    cin >> this->condition1;
}

Ordre1::Ordre1(double condition)
{
    this->condition1=condition;
}


///////////////////////////////////////////////////FONCTION1///////////////////////////////////////////////////////////////
Fonction1::Fonction1()
{
}


double Fonction1::fonction_propre(double x , double t)
{
    return -3*x-3*t;
}

void Fonction1::resolution()
{
    double u = condition1;
    double borne = borne_sup/(N+1);

    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert

    if(fichier)
    {
        for(int i = 0 ; i<=N ; i++)
        {
            u = u + borne*fonction_propre(u,i*borne);

            cout<<u<<endl;
            fichier <<i*borne<<"\t"<< u<<"\t"<<fonction_exact(condition1,(i)*borne)<< endl;
        }
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }

    fichier.close();
}

double fonction_exact(double condition ,double x )
{
    return (condition-1./3.)*exp(-3*x)-x+1./3.;
}





////////////////////////////////////////////////RC///////////////////////////////////////////////////////////////////////////

RC::RC()
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 1nF, R=50Ohms) ou non (2) ?" <<endl;
    cin >> choix;
    if (choix == 2)
    {
        cout << "Entree votre valeur de C"<<endl;
        cin >> this->C;
        cout << "Entree votre valeur de R"<<endl;
        cin >> this->R;
    }
    else 
    {
        this->C=1e-9;
        this->R=50;

    }
}

RC::RC(double C, double R)
{
    this->C=C;
    this->R=R;
}


void RC::resolution()
{
    double p1=0;
    double p2=0;
    double p3=0;
    double p4=0;
    int choix =0;
    double u = condition1;
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert

    if(fichier)
    {
        cout << " Methode de resolution: Euler(1), Heun(2), Runge Kutta(3) "<<endl;
        cin >> choix;
        switch ( choix)
        {
            case 1 :
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        u = u + N*fonction_propre(u,signal->calcul_tension(i));

                        fichier <<i+N<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;

                    }
                }
                break;

            case 2 : //fonctionne HEUN !
                {

                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        u = u + N/2*(fonction_propre(u+u*N,signal->calcul_tension(i))+fonction_propre(u+N*fonction_propre(u+u*N,signal->calcul_tension(i+N)),signal->calcul_tension(i)));//N*fonction_propre(R,C,u,signal->calcul_tension(i));

                        fichier <<i+N<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;

                    }
                }
                break;
            case 3: // RUNGE fonctionne
                {

                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        p1= fonction_propre(u+u*N,signal->calcul_tension(i));
                        p2 = fonction_propre(u+p1*N,signal->calcul_tension(i));
                        p3 = fonction_propre(u+p2*N,signal->calcul_tension(i));
                        p4 = fonction_propre(u+p3*N,signal->calcul_tension(i));
                        u = u + N/6*(p1+2*p2+2*p3+p4);
                        //  cout<<u<<endl;

                        fichier <<i+N<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;

                    }
                }



                break;
            default:;
        }
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }


    fichier.close();
}

double RC::fonction_propre(double U , double Ve  )
{
    return (Ve-U)/(R*C);
}




double RC::fonction_exactRC(double t, double V0 , double R , double C )
{
    return V0*(1-exp(-t/(R*C)));
}



////////////////////////////////////////////////RC_diode///////////////////////////////////////////////////////////////////////////
RC_diode::RC_diode()
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 1nF, R1=36 Ohms ,R2=180 Ohm) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entree votre valeur de C"<<endl;
        cin >> this->C;
        cout << "Entree votre valeur de R1"<<endl;
        cin >> this->R1;
        cout << "Entree votre valeur de R2"<<endl;
        cin >> this->R2;
    }
    else
    {
        this->C=1e-9;
        this->R1=36;
        this->R2=180;
    }

}

RC_diode::RC_diode(double R1,double R2,double C)
{

    this->R1=R1;
    this->R2=R2;
    this->C=C;
}


void RC_diode::resolution()
{
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert
    double u = condition1;
    double ve =0;
    int choix =0;
    double p1=0;
    double p2=0;
    double p3=0;
    double p4=0;
    cout << "Methode de resolution: Euler(1), Heun(2), Runge Kutta(3) "<<endl;
    cin >> choix;
    if(fichier)
    {
        switch(choix)
        {

            case 1 :// resolution selon Euler 
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        if((signal->calcul_tension(i)) > 0.6)
                        {
                            u = u + N*fonction_proprepass(u,signal->calcul_tension(i));
                        }

                        else
                        {
                            u = u + N*fonction_propre(u);
                        }
                        fichier <<i+N<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
                    }
                    break;
                }
            case 2 : // resolution selon Heun
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        ve = signal->calcul_tension(i);

                        if (ve >0.6)
                        {
                            u = u+N/2*(fonction_proprepass(u+u*N,ve)+fonction_proprepass(u+N*fonction_proprepass(u+u*N,signal->calcul_tension(i+N)),ve));
                        }
                        else
                        {
                            u = u+N/2*(fonction_propre(u+u*N)+fonction_propre(u+N*fonction_propre(u+u*N)));
                        }
                        fichier <<i+N<<"\t"<<u<<"\t"<<ve<< endl;
                    }

                    break;
                }

            case 3 : // resolution selon Runge Kutta
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {

                        ve = signal->calcul_tension(i);

                        if(ve > 0.6)
                        {
                            p1= fonction_proprepass(u+u*N,ve);
                            p2 = fonction_proprepass(u+p1*N,ve);
                            p3 = fonction_proprepass(u+p2*N,ve);
                            p4 = fonction_proprepass(u+p3*N,ve);
                        }

                        else
                        {
                            p1= fonction_propre(u+u*N);
                            p2 = fonction_propre(u+p1*N);
                            p3 = fonction_propre(u+p2*N);
                            p4 = fonction_propre(u+p3*N);
                        }

                        u = u + N/6*(p1+2*p2+2*p3+p4);

                        fichier <<i+N<<"\t"<<u<<"\t"<<ve<< endl;

                    }
                    break;
                }

        }	
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }



    fichier.close();
}


double RC_diode::fonction_propre(double U )
{
    return -U/(R2*C);
}

double RC_diode::fonction_proprepass(double U,double Ve  )
{
    return 1/(R1*C)*(Ve-0.6-((R1/R2)+1)*U);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ORDRE2/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ordre2::Ordre2()
{
    cout << "Entree votre premiere condition initiale"<<endl;
    cin >> this->condition1;
    cout << "Entree votre seconde condition initiale"<<endl;
    cin >> this->condition2;
}

Ordre2::Ordre2(double condition1 ,double condition2)
{
    this->condition1=condition1;
    this->condition2=condition2;
}

Fonction2::Fonction2()
{

    cout << "Entree votre lambda"<<endl;
    cin >> this->lambda;
}

Fonction2::Fonction2(double lambda)
{

    this->lambda=lambda;
}




void Fonction2::resolution()
{
    double u = condition1;
    double v = condition2;
    double U = 0;
    double V = 0;

    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert

    if(fichier)
    {
        for(double i = 0 ; i<=borne_sup ; i=i+N)
        {

            U = u + N*v;
            V = v + N*(-lambda*u);


            fichier <<i<<"\t"<<U<<"\t"<</*signal->calcul_tension(i)*/fonction_exacte(condition1,condition2,lambda,i)  << endl;
            u=U;
            v=V;
        }

    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }




    // on essaye d'ouvrir

    fichier.close();

}


double Fonction2::fonction_exacte(double U0,double V0,double lambda,double t)
{

    return V0/(sqrt(lambda))*sin(sqrt(lambda)*t)+U0*cos(sqrt(lambda)*t);

};

double Fonction2::fonction_propre(double U0,double V0,double lambda){return 0;};


//////////////////////////////////////////////////////RLC_serie////////////////////////////////////////////////////////////////////////////

RLC_serie::RLC_serie() 
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 0.1 nF, R=120 Ohms ,L=1 uH) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entree L"<<endl;
        cin >> this->L;
        cout << "Entree C"<<endl;
        cin >> this->C;
        cout << "Entree R"<<endl;
        cin >> this->R;
    }
    else
    {
        this->L=1e-6;
        this->C=1e-10;
        this->R=120;
    }
}

RLC_serie::RLC_serie(double R,double L,double C) 
{
    this->L=L;
    this->C=C;
    this->R=R;
}

double RLC_serie::fonction_propre(double u,double v,double t)
{
    return (t-u)/(L*C)-(R/L)*v;
}


void RLC_serie::resolution()
{
    int choix=0;
    double u = condition1;
    double v = condition2;
    double U = 0;
    double V = 0;
    double p1=0;
    double p2=0;
    double p3=0;
    double p4=0;
    double l1=0;
    double l2=0;
    double l3=0;
    double l4=0;
    double ve =0;
    cout << "Methode de resolution: Euler(1), Heun(2), Runge Kutta(3) " <<endl;
    cin >> choix;
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert

    if(fichier)
    {
        switch (choix)
        {
            case 1: 
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        ve =signal->calcul_tension(i);
                        U = u + N*v;
                        V = v + N*(fonction_propre(u,v,ve));
                        fichier <<i<<"\t"<<U<<"\t"<<ve<< endl;
                        u=U;
                        v=V;
                    }
                }
                break;

            case 2 : 
                {
                    for(double i = 0 ; i<=borne_sup ; i=i+N)
                    {
                        p1= v;
                        l1= fonction_propre(u,v,signal->calcul_tension(i));

                        p2= (v+N*l1/2);
                        l2= fonction_propre(u+N*p1/2,v+N*l1/2,signal->calcul_tension(i+N));

                        u=u+N/2*(p1+p2);
                        v=v+N/2*(l1+l2);

                        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
                    }
                }
                break;
            case 3 : 
                {
                    for(double i = 0; i<= borne_sup ; i=i+N)
                    {
                        p1= N*v;
                        l1= N*fonction_propre(u,v,signal->calcul_tension(i+N));

                        p2= N*(v+l1/2);
                        l2= N*fonction_propre(u+p1/2,v+l1/2,signal->calcul_tension(i+N));

                        p3= N*(v+l2/2);
                        l3= N*fonction_propre(u+p2/2,v+l2/2,signal->calcul_tension(i+N));

                        p4= N*(v+l3);
                        l4= N*fonction_propre(u+p3,v+l3,signal->calcul_tension(i+N));

                        u=u+1/6*(p1+2*p2+2*p3+p4);
                        v=v+1/6*(l1+2*l2+2*l3+l4);

                        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;


                    }
                    break;
                }
            default :;

        }   // on essaye d'ouvrir
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }







    fichier.close();

}

/////////////////////////////////RLC_PARALLELE///////////////////////////////////////////////////////

RLC_parallele::RLC_parallele() 
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C=0.1 uF, R=1.2 Ohms ,L=10 nH) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entree L"<<endl;
        cin >> this->L;
        cout << "Entree C"<<endl;
        cin >> this->C;
        cout << "Entree R"<<endl;
        cin >> this->R;
    }
    else
    {
        this->L=10e-9;
        this->C=1e-7;
        this->R=1.2;
    }
}

double RLC_parallele::fonction_propre(double u,double v,double t)
{
    return  (t-v)/(R*C)-u/(C*L);
}



RLC_parallele::RLC_parallele(double R,double L,double C) 
{
    this->L=L;
    this->C=C;
    this->R=R;
}



void RLC_parallele::resolution()
{
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en �criture avec effacement du fichier ouvert
    double u = condition1;
    double v = condition2;
    double U = 0;
    double V = 0;
    double ve =0;
    if(fichier)
    {
        for(double i = 0 ; i<=borne_sup ; i=i+N)
        {
            ve = signal->calcul_tension(i);
            U = u + N*v;
            V = v + N*fonction_propre(u,v,(signal->calcul_tension(i+N)-ve)/N);
            fichier <<i<<"\t"<<U<<"\t"<<ve<< endl;
            u=U;
            v=V;
        }      
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    }
    fichier.close();
}

