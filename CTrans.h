//Nigmatulin
//20250420
//ver 5.0

#pragma once
#include "CCalculation.h"
class CTrans :
    public CCalculation //объявляется класс CTrans, который наследуется от класса CCalculation с доступом public
{
    public:
        CTrans(); //конструктор
        ~CTrans(); //деструктор
        void SetTrancParam(int Xwidth, int Yheight); //устанавливает параметры преобразования
public: 
    double m_ScaleX;  // Масштаб по X
    double m_ScaleY;  // Масштаб по Y
    CPoint m_center; //центральная точка 
public:
    CPoint GetPoint(double X, const Parameters& params); //вычисление координат точек
    CPoint Trans(double X, const Parameters& params); //преобразует значения в пиксели
    double ScreenToMathX(int screenX); //перевод экранных координат в математические
};


//CPoint GetPoint(double X, double Param); //вычисление координат точек
//CPoint Trans(double X, double Param); //преобразует значения в пиксели
 //double m_Scale; //масштабный коэффициент