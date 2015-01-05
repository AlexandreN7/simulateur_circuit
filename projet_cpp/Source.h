#ifndef SOURCE_H
#define SOURCE_H
#include <iostream>

using namespace std;

class Source
{
	public:
		Source();
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
		Signal_Perio();
		virtual double calcul_tension(double tps)=0;
	protected:
		double frequency;
	private:
};


class Signal_Noperio : public Source
{
	public:
		Signal_Noperio();
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
		double calcul_tension(double tps);
	protected:
	private:
};

class Rectangulaire : public Signal_Noperio
{
	public:
		Rectangulaire();
		double calcul_tension(double tps);
	protected:
	private:
};

class SolutionExacte1 : public Source // astuce qui permet de superpositionner la solution exacte de la fonction 1
{
	public:
		SolutionExacte1();
		double calcul_tension(double tps);
	protected:
	private:
        double condition1;
};
class SolutionExacte2 : public Source // astuce qui permet de superpositionner la solution exacte de la fonction 1
{
	public:
		SolutionExacte2();
		double calcul_tension(double tps);
	protected:
	private:
        double condition1;
        double condition2;
        double lambda;
};
////////////////////////////////////////////////////////

class Sinus : public Signal_Perio
{
	public:
		Sinus();
		double calcul_tension(double tps);
	protected:
	private:
};

class Triangulaire : public Signal_Perio
{
	public:
		Triangulaire();
		double calcul_tension(double tps);
	protected:
	private:
};

class Carre : public Signal_Perio
{
	public:
		Carre();
		double calcul_tension(double tps);
	protected:
		double dc;// duty cycle
	private:
};
#endif // SOURCE_H
