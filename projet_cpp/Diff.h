#ifndef DIFF_H_INCLUDED
#define DIFF_H_INCLUDED
#include "Source.h"

double fonction_exact(double,double);
double fonction_exactRC(double, double);

class Equation_diff
{
	public:
		Equation_diff();
		Equation_diff(double,double);// constructeur parametrique
		virtual void resolution(){};

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
		virtual void resolution(){};
	protected:
		double condition1;
	private:
};


class  Fonction1 : public Ordre1
{
	public:
		Fonction1();
		void resolution();
	protected:
		double fonction_propre(double , double);
	private:



};

class  RC : public Ordre1
{
	public:
		RC();
		RC(double,double);
		void resolution();
	protected:
		double fonction_propre( double , double);
		double fonction_exactRC(double, double  , double , double );
	private:

		double R;
		double C;

};


class  RC_diode : public Ordre1
{
	public:
		RC_diode();
		RC_diode(double,double,double);
		void resolution();
	protected:
		double fonction_propre( double ); // la diode est non passante
		double fonction_proprepass( double , double); // la diode est passante
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
		virtual void resolution(){};


	protected:
		double condition1;
		double condition2;
	private:

};


class Fonction2 : public Ordre2
{
	public:

		Fonction2();
		Fonction2(double);
		void resolution();
	protected:
		double fonction_exacte(double);
		double fonction_propre(double);
	private:
		double lambda;


};


class RLC_serie : public Ordre2
{
	public:

		RLC_serie();
		RLC_serie(double,double,double);
		void resolution();
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
		void resolution();
	protected:
        double fonction_propre(double,double,double);

	private:

		double L;
		double C;
		double R;
};


#endif // DIFF_H_INCLUDED
