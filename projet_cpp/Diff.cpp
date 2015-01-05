///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Fichier contenant les methodes des classes définies dans Diff.h
//Dans l'ordre :
//-Equation_Diff
//-Ordre1
//-Fonction1
//-RC
//-RC_diode
//-Ordre2
//-Fonction2
//-RLC_serie
//-RLC_parallele
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#include "Diff.h"
#include "Source.h"
#include <math.h>
#include <iostream>
#include <fstream>


using namespace std;

Equation_diff::Equation_diff()
{
    int choix = 0;
    cout << "Entrer le pas de calcul"<<endl;
    cin >>  this->N;
    cout << "Qul est le temps maximal ?"<<endl;
    cin >>  this->borne_sup;
    cout << "Choisissez la source: sinus(1), pwm(2) ,triangulaire(3) ,rectangulaire(4) ,echelon(5), SolutionFonction1(6), SolutionFonction2(7)" << endl;
    cin >> choix;

    switch ( choix) // choix du type de source 
    {
        case 1 : signal = new Sinus(); break;
        case 2 : signal = new Carre(); break;
        case 3 : signal = new Triangulaire(); break;
        case 4 : signal = new Rectangulaire(); break;
        case 5 : signal = new Echelon(); break;
        case 6 : signal = new SolutionExacte1(); break;
        case 7 : signal = new SolutionExacte2(); break;
    }
}

Equation_diff::Equation_diff(double pas ,double borne)
{
    this->N=pas;
    this->borne_sup=borne;
}

void Equation_diff::resolution()// fonction qui permet le choix des methodes de résolutions
{
    int choix =0;
    cout << " Methode de resolution: Euler(1), Heun(2), Runge Kutta(3) "<<endl;
    cin >> choix;
    switch ( choix)
    {
        case 1 :
            resolution_Euler();
            break;
        case 2 :        
            resolution_Heun();
            break;
        case 3: // RUNGE fonctionne
            resolution_Runge();
            break;
        default:;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ORDRE1/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ordre1::Ordre1()
{	cout << "Entrer votre condition initiale"<<endl;
    cin >> this->condition1;
}

Ordre1::Ordre1(double condition)
{
    this->condition1=condition;
}

void Ordre1::resolution_Euler(){

    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    double u = condition1;
    for(double i = 0 ; i<=borne_sup ; i=i+N)
    {
        u = u+N*fonction_propre(u,i);
        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
    }
    fichier.close();
}
void Ordre1::resolution_Heun(){
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    double u = condition1;
    double p1,p2;

    for(double i = 0 ; i<=borne_sup ; i=i+N)
    {
        p1 =fonction_propre(u+u*N,i);
        p2 =fonction_propre(u+N*p1,i+N);
        u= u+N/2*(p1+p2);
        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
    }
    fichier.close();

}
void Ordre1::resolution_Runge(){
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    double u = condition1;
    double p1,p2,p3,p4;

    for(double i = 0 ; i<=borne_sup ; i=i+N)
    {
        p1= fonction_propre(u+u*N,i);
        p2 = fonction_propre(u+p1*N,i);
        p3 = fonction_propre(u+p2*N,i);
        p4 = fonction_propre(u+p3*N,i);
        u = u + N/6*(p1+2*p2+2*p3+p4);
        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
    }
    fichier.close();
}

///////////////////////////////////////////////////FONCTION1///////////////////////////////////////////////////////////////
Fonction1::Fonction1()
{
}

double Fonction1::fonction_propre(double u , double i)
{
    double valeur = (-3*u-3*i);
    return valeur;
}

////////////////////////////////////////////////RC///////////////////////////////////////////////////////////////////////////

RC::RC()
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 1nF, R=50Ohms) ou non (2) ?" <<endl;
    cin >> choix;
    if (choix == 2)
    {
        cout << "Entrer votre valeur de C"<<endl;
        cin >> this->C;
        cout << "Entrer votre valeur de R"<<endl;
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

double RC::fonction_propre(double u , double i )
{
    return (signal->calcul_tension(i)-u)/(R*C);
}


////////////////////////////////////////////////RC_diode///////////////////////////////////////////////////////////////////////////
RC_diode::RC_diode()
{
    int choix=0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 1nF, R1=36 Ohms ,R2=180 Ohm) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entrer votre valeur de C"<<endl;
        cin >> this->C;
        cout << "Entrer votre valeur de R1"<<endl;
        cin >> this->R1;
        cout << "Entrer votre valeur de R2"<<endl;
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

double RC_diode::fonction_propre(double U,double i )
{
    double ve =signal->calcul_tension(i);
    if (ve<0.6){
        return -U/(R2*C);
    }
    else {
        return 1/(R1*C)*(ve-0.6-((R1/R2)+1)*U);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////ORDRE2/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ordre2::Ordre2()
{
    cout << "Entrer votre condition initiale sur u"<<endl;
    cin >> this->condition1;
    cout << "Entrer votre condition initiale sur u'"<<endl;
    cin >> this->condition2;
}

Ordre2::Ordre2(double condition1 ,double condition2)
{
    this->condition1=condition1;
    this->condition2=condition2;
}

void Ordre2::resolution_Euler(){
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    double u = condition1;
    double v = condition2;
    double U,V;
    for(double i = 0 ; i<=borne_sup ; i=i+N)
    {
        U = u + N*v;
        V = v + N*fonction_propre(u,v,i);
        fichier <<i<<"\t"<<U<<"\t"<<signal->calcul_tension(i)<< endl;
        u=U;
        v=V;
    }

}
void Ordre2::resolution_Heun(){
    double p1,p2,l1,l2; // intermediaires de calcul
    double u = condition1;
    double v = condition2;

    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    for(double i = 0 ; i<=borne_sup ; i=i+N)
    {
        p1= v;//etape 1
        l1= fonction_propre(u,v,i);

        p2= (v+N*l1);//etape 2
        l2= fonction_propre(u+N*p1,v+N*l1,i+N);

        u=u+N/2*(p1+p2);//calcul a n+1
        v=v+N/2*(l1+l2);

        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
    }
}

void Ordre2::resolution_Runge(){

    double p1,p2,p3,p4,l1,l2,l3,l4; // intermediaire de calcul
    double u = condition1;
    double v = condition2;
    ofstream fichier("Simulation.txt", ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert
    for(double i = 0; i<= borne_sup ; i=i+N)
    {
        p1= v;
        l1= fonction_propre(u,v,i);

        p2= (v+N*l1/2);
        l2= fonction_propre(u+N*p1/2,v+N*l1/2,i+N/2);

        p3= (v+N*l2/2);
        l3= fonction_propre(u+N*p2/2,v+N*l2/2,i+N/2);

        p4= (v+N*l3);
        l4= fonction_propre(u+N*p3,v+N*l3,i+N);

        u=u+N/6*(p1+2*p2+2*p3+p4);
        v=v+N/6*(l1+2*l2+2*l3+l4);

        fichier <<i<<"\t"<<u<<"\t"<<signal->calcul_tension(i)<< endl;
    }
}

////////////////////////////////Classe fille de Ordre2 //////////////////////////////
Fonction2::Fonction2()
{
    cout << "Entrer le lambda"<<endl;
    cin >> this->lambda;
}

Fonction2::Fonction2(double lambda)
{
    this->lambda=lambda;
}


double Fonction2::fonction_propre(double u,double fictif1,double fictif2 )
{
    double valeur=-lambda*u;
    return valeur;
}

//////////////////////////////////////////////////////RLC_serie////////////////////////////////////////////////////////////////////////////

RLC_serie::RLC_serie() 
{
    int choix =0;
    cout<< " Voulez vous les valeurs des composants par defaut (1) (C= 0.1 nF, R=120 Ohms ,L=1 uH) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entrer L"<<endl;
        cin >> this->L;
        cout << "Entrer C"<<endl;
        cin >> this->C;
        cout << "Entrer R"<<endl;
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

double RLC_serie::fonction_propre(double u,double v,double i)
{
    return ((signal->calcul_tension(i)-u)/(L*C)-(R/L)*v);
}

/////////////////////////////////RLC_PARALLELE///////////////////////////////////////////////////////

RLC_parallele::RLC_parallele() 
{
    int choix =0;
    cout<< "Voulez vous les valeurs des composants par defaut (1) (C=0.1 uF, R=1.2 Ohms ,L=10 nH) ou non (2) ?" <<endl;
    cin >> choix;

    if (choix ==2)
    {
        cout << "Entrer L"<<endl;
        cin >> this->L;
        cout << "Entrer C"<<endl;
        cin >> this->C;
        cout << "Entrer R"<<endl;
        cin >> this->R;
    }
    else
    {
        this->L=10e-9;
        this->C=1e-7;
        this->R=1.2;
    }
}

double RLC_parallele::fonction_propre(double u,double v,double i)
{
    return  ((signal->calcul_tension(i+N)-signal->calcul_tension(i))/N-v)/(R*C)-u/(C*L);
}



RLC_parallele::RLC_parallele(double R,double L,double C) 
{
    this->L=L;
    this->C=C;
    this->R=R;
}
