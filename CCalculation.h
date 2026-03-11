//Nigmatulin
//20250420
//ver 5.0

#pragma once
class CCalculation //объ€вление класса с именем CCalculation
{
public: //все члены доступные из других функций 
	CCalculation(); //конструктор
	~CCalculation(); //деструктор
	double GetY(double x, const Parameters& params); //выполн€ет вычисление значений синусоиды
	double GetLinearY(double x, const Parameters& params); //вычисление значений линейной функции
	double GetDifference(double x, const Parameters& params); //вычисление пересечений графиков
	double FindRoot(double left, double right, const Parameters& params, double epsilon, int& iterations); //поиск корн€
};

/*	double GetY(double x, double Par);*/ //выполн€ет вычисление значени€ переменной y