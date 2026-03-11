//Nigmatulin
//20250420
//ver 5.0
#pragma once
#include "CCalculation.h"
#include "CTrans.h"
#include "Idata.h"
class CArtist : public CStatic
{
	DECLARE_DYNAMIC(CArtist)
public:
	CArtist();
	virtual ~CArtist();
	void SetParams(Parameters* params);
protected:
	DECLARE_MESSAGE_MAP()
public:
	// Методы установки цветов:
	void SetBkColor(COLORREF col) { m_bkCol = col; } //цвет фона
	void SetAxisColor(COLORREF col) { m_AxisColor = col; } //цвет осей
	void SetSinColor(COLORREF col) { m_SinColor = col; } //цвет синусоиды
	void SetLinearColor(COLORREF col) { m_LinearColor = col; } //цвет линейной функции
protected:
	// Цвета для рисования
	COLORREF m_bkCol;       // Фон
	COLORREF m_AxisColor;   // Оси
	COLORREF m_SinColor;    // График синуса
	COLORREF m_LinearColor; // График линейной функции
public:
	afx_msg
	void SetRedrawFlag(bool flag); //устанавливаем флаг перерисовки
	afx_msg void OnPaint(); //вызывается при перерисовки элемента управления
	void SetIdataPtr(Idata* pData) { m_Idata = pData; } //устанавливает указатель на объект данных
protected:
	Idata* m_Idata = nullptr;
	bool bRedraw = true; //флаг перерисовки
	CDC* m_MemDc = nullptr; //Указатель на контекст устройства памяти
	CBitmap* m_BitMap = nullptr; //Указатель на растровое изображение
public:
	afx_msg void OnSize(UINT nType, int cx, int cy); //Вызывается, когда изменяется размер элемента управления
	void SetCalculation(CCalculation* calc, Parameters* params, CTrans* trans); // устанавливает указатели на объекты, которые участвуют в расчетах
	void OnLButtonDown(UINT nFlags, CPoint point); //Вызывается, когда пользователь нажимает левую кнопку мыши над элементом управления
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void SetRedraw() { bRedraw = true; } //использовано для принудительного обновления элемента управления
private:
	CCalculation* m_Calculation; // Указатель на объект вычислений
	CTrans* m_Trans; // Указатель на объект трансформации координат
	Parameters* m_params; // Указатель на параметры уравнения
public:
	void SetPrecision(int precision) { m_NumDigits = precision; } //Метод установки точности вывода данных
	int GetPrecision() const { return m_NumDigits; } //Метод получения текущего значения точности. Он возвращает значение переменной-члена m_NumDigits
protected:
	int m_NumDigits; // число знаков после запятой для вывода
};


