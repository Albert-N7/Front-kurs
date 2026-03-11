//Nigmatulin
//20250420
//ver 5.0
#pragma once
#include "pch.h"
#include <vector>
class Idata
{

public:
	Idata(); //конструктор
	virtual ~Idata() = default; //виртуальный деструктор
	virtual size_t IGetSinPoints(std::vector<CPoint>& vec) = 0; //принимает ссылку на вектор точек и заполняет его точками синусоиды
	virtual size_t IGetLinearPoints(std::vector<CPoint>& vec) = 0; //заполняет вектор точками линейной функции
};

