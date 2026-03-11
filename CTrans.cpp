//Nigmatulin
//20250420
//ver 5.0


#include "pch.h"
#include "CTrans.h"
#define _USE_MATH_DEFINES
#include <math.h>
CTrans::CTrans() //конструктор
    : m_ScaleX(0) //коэффициент для преобразования координат по оси X
    , m_ScaleY(0)//коэффициент для преобразования координат по оси Y
    , m_center(0, 0) //центральная точка координат
{
}

CTrans::~CTrans() //деструктор 
{
}

void CTrans::SetTrancParam(int Xwidth, int Yheight) //настраивает параметры положения графика
{
    //double scX, scY;
    m_ScaleX = (double)(Xwidth - 2 * BORDER_W) / (2.0 * M_PI); // Масштаб по оси X
    m_ScaleY = (double)(Yheight - 2 * BORDER_W) / 8.0;         // Масштаб по оси Y
    m_center.x = Xwidth/2; // Координата X центра области
    m_center.y = Yheight / 2; // Координата Y центра области
}

CPoint CTrans::GetPoint(double X, const Parameters& params)
{
    CPoint Cur = Trans(X, params); //преобразует математические координаты (X, Y) в пиксельные
    return Cur;
}

CPoint CTrans::Trans(double X, const Parameters& params)
{
    double y = 0.0; //создается переменная y типа double

    if (params.d == 0.0 && params.e == 0.0) //если параметры d и e равны 0, то график синусоиды 
    {
        y = GetY(X, params); // Синусоида
    }
    else //если d и e не равны 0, то вычисляются значения линейной функции
    { 
        y = GetLinearY(X, params); // Линейная функция
    }
    int screenX = static_cast<int>(m_center.x + X * m_ScaleX); //преобразует X в пиксели
    int screenY = static_cast<int>(m_center.y - y * m_ScaleY);//преобразует Y в пиксели
    return CPoint(screenX, screenY); //создается точка с вычисленными координатами
}

double CTrans::ScreenToMathX(int screenX)
{
    return (screenX - m_center.x) / m_ScaleX; //переводим экранные координаты в математические
}
