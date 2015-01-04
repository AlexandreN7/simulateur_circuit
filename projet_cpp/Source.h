#ifndef SOURCE_H
#define SOURCE_H
#include <iostream>

using namespace std;

class Source
{
	public:
		// Source(double tps_start , double amp , double offset);
		Source();
		//~Source();
		virtual double calcul_tension(double tps){return 0;};


	protected:
		double tps_start;
		double amp;
		double offset;

	private:
};

/////////////////////////////////////////////////////////
class Signal_Perio : public Source
{
	public:
		// Signal_Perio(double frequency);
		Signal_Perio();
		//~Signal_Perio();

		virtual double calcul_tension(double tps)=0;

	protected:
		double frequency;

	private:
};


class Signal_Noperio : public Source
{
	public:
		// Signal_Noperio(double duree);
		Signal_Noperio();
		// ~Signal_Noperio();


		virtual double calcul_tension(double tps)=0;

	protected:
		double duree;

	private:
};
////////////////////////////////////////////////////////


class Echelon : public Signal_Noperio
{
	public:
		Echelon();
		// ~Echelon();

		double calcul_tension(double tps);
	protected:

	private:
};

class Rectangulaire : public Signal_Noperio
{
	public:
		Rectangulaire();
		//  ~Rectangulaire();
		;
		double calcul_tension(double tps);
	protected:

	private:

};

class SolutionExacte1 : public Source
{
	public:
		SolutionExacte1();
		// ~Echelon();

		double calcul_tension(double tps);
	protected:

	private:
        double condition1;
};
class SolutionExacte2 : public Source
{
	public:
		SolutionExacte2();
		// ~Echelon();

		double calcul_tension(double tps);
	protected:

	private:
};
////////////////////////////////////////////////////////


class Sinus : public Signal_Perio
{
	public:
		Sinus();
		//  ~Sinus();

		double calcul_tension(double tps);

	protected:
	private:
};


class Triangulaire : public Signal_Perio
{
	public:
		Triangulaire();
		//  ~Triangulaire();

		double calcul_tension(double tps);

	protected:
	private:
};

class Carre : public Signal_Perio
{
	public:
		Carre();
		//	Carre(double,double,double,double,double);
		//   ~Carre();

		double calcul_tension(double tps);

	protected:
		double dc;

	private:
};





#endif // SOURCE_H
