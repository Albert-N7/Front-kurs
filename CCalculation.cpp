//Nigmatulin
//20250420
//ver 5.0

#include "pch.h"
#include "CCalculation.h"
#include <cmath>
CCalculation::CCalculation() //конструктор 
{

}
CCalculation::~CCalculation() //деструктор
{
}
double CCalculation::GetY(double x, const Parameters& params)
{
    double y1 = params.a * sin(params.b * x + params.c); // Первая часть уравнения
    return y1;                                     //вызывается первая функция
}
double CCalculation::GetLinearY(double x, const Parameters& params)
{
    double y2 = params.d * x + params.e;                // Вторая часть уравнения
    return y2;                                     //вызывается вторая функция
}

double CCalculation::GetDifference(double x, const Parameters& params)
{
    double y1 = GetY(x, params);         // Значение первой функции
    double y2 = GetLinearY(x, params);   // Значение второй функции
    return y1 - y2;                      // Разность функций
}

double CCalculation::FindRoot(double left, double right, const Parameters& params, double epsilon, int& iterations) 
{

    double mid = 0.0; //инициализируем переменную, которая будет использоваться для хранения среднего значения интервала [left, right] в каждой итерации
    iterations = 0; //вводим счётчик итераций
    const int MAX_ITERATIONS = 1000; // Максимальное количество итераций

    while ((right - left) / 2.0 > epsilon && iterations < MAX_ITERATIONS) //пока длина интервала[right - left] не станет меньше epsilon и число итераций не превысит максимум
    {
        mid = (left + right) / 2.0; //вычисляется середина текущего интервала

        // Используем сравнение с учетом абсолютной погрешности
        if (fabs(GetDifference(mid, params)) < epsilon) //если абсолютное значение в точке mid меньше заданной точности
        {
            return mid; //возвращаем значение mid (решение)
        }

        if (GetDifference(left, params) * GetDifference(mid, params) < 0) //если знаки противоположные, то корень находится в этом отрезке
        {
            right = mid; // и конец интервала становится равный mid
        }
        else //иначе
        {
            left = mid; //начало интервала становится равным mid
        }
        iterations++; //увеличивается количество итераций
    }
    // Если достигнут максимум итераций, mid является приближенным решением
    return mid;
}
