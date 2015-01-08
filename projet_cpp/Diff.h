#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED
#include "Source.h"

double fonction_exactRC(double, double);

class Equation_diff
{
    public:
        Equation_diff();
        Equation_diff(double,double);// constructeur parametrique
        virtual void resolution_Euler(){}; // methodes de résolution
        virtual void resolution_Heun(){};
        virtual void resolution_Runge(){};
        void resolution();
    protected:
        Source *signal; // pointeur vers la source
        double N;
        double borne_sup;
    private:
};



///////////////////////////////////////ORDRE 1 ////////////////////////////////////////////////

class Ordre1 : public Equation_diff
{
    public:
        Ordre1();
        Ordre1(double); // constructeur parametrique
        void resolution_Euler(); // methodes de résolution
        void resolution_Heun();
        void resolution_Runge();
    protected:
        double condition1;
        virtual double fonction_propre(double,double){};
    private:
};


class  Fonction1 : public Ordre1
{
    public:
        Fonction1();
    protected:
        double fonction_propre(double,double);
    private:
};

class  RC : public Ordre1
{
    public:
        RC();
        RC(double,double);
    protected:
        double fonction_propre(double,double);
    private:
        double R;
        double C;
};


class  RC_diode : public Ordre1
{
    public:
        RC_diode();
        RC_diode(double,double,double);
    protected:
        double fonction_propre(double,double);
    private:
        double R1;
        double R2;
        double C;
};


///////////////////////////////////////ORDRE 2 /////////////////////////////////////////////

class Ordre2 : public Equation_diff
{
    public:
        Ordre2();
        Ordre2(double,double);
        void resolution_Euler(); // methodes de résolution
        void resolution_Heun();
        void resolution_Runge();
    protected:
        double condition1;
        double condition2;
        virtual double fonction_propre(double,double,double)=0; 
    private:
};


class Fonction2 : public Ordre2
{
    public:
        Fonction2();
        Fonction2(double);
        double fonction_propre(double,double,double); // deux des arguments sont fictifs afin de correspondre aux autres fonctions propres qui ont 3 arguments
    protected:
    private:
        double lambda;
};


class RLC_serie : public Ordre2
{
    public:
        RLC_serie();
        RLC_serie(double,double,double);
    protected:
        double fonction_propre(double,double,double);
    private:
        double L;
        double C;
        double R;
};

class RLC_parallele : public Ordre2
{
    public:
        RLC_parallele();
        RLC_parallele(double,double,double);
    protected:
        double fonction_propre(double,double,double);
    private:
        double L;
        double C;
        double R;
};


#endif // DIFF_H_INCLUDED
