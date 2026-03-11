//Nigmatulin
//20250420
//ver 5.0
// MFCApplication1Dlg.h: файл заголовка
//

#pragma once

#include "CArtist.h"
#include "afxwin.h"
#include <vector>
#include "CTrans.h"

#define ID_TIMERA 40 //макрос таймера, который используется для анимации графика
 
// Диалоговое окно CMFCApplication1Dlg
class CMFCApplication1Dlg : public CDialogEx
	, Idata //класс CMFCApplication1Dlg наследуется от CDialogEx и Idata
{
// Создание

protected:
	CCalculation m_Calculation; // Объект для вычислений
	Parameters params; // Параметры уравнения
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// стандартный конструктор
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif
	protected://следующие члены класса будут доступны только внутри самого класса и производных классов
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV
// Реализация
protected: //следующие члены класса будут доступны только внутри самого класса и производных классов
	HICON m_hIcon; //хранит иконку диалога
	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog(); //служит для выполнения дополнительной настройки окна перед его отображением
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam); //обрабатывает команды системы
	afx_msg void OnPaint(); //перерисовывает окно
	afx_msg HCURSOR OnQueryDragIcon(); // Курсор при перетаскивании окна
	DECLARE_MESSAGE_MAP() // Макрос для таблицы сообщений MFC
public: //доступные члены класса:
	afx_msg void OnBnClickedOk(); //обрабатывает нажатие кнопки ОК
	/*BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);*/
	CArtist m_artist; //объект класса CArtist, используется для рисования
	CEdit m_EditA; //объект класса CEdit, используется для представления текстового поля для ввода данных
	CEdit m_EditB;//объект класса CEdit, используется для представления текстового поля для ввода данных
	CEdit m_EditC;//объект класса CEdit, используется для представления текстового поля для ввода данных
	CEdit m_EditD;//объект класса CEdit, используется для представления текстового поля для ввода данных
	CEdit m_EditE;//объект класса CEdit, используется для представления текстового поля для ввода данных
	CEdit m_Edit2;
	afx_msg void OnEnChangeEditA(); //обрабатывает изменения текста в текстовом окне m_EditA
	afx_msg void OnEnChangeEditB();//аналогично для следующих
	afx_msg void OnEnChangeEditC();
	afx_msg void OnEnChangeEditD();
	afx_msg void OnEnChangeEditE();
	afx_msg void OnEnChangeEdit2();//обрабатывает изменения текста в текстовом окне точности
	size_t GetSinPoints(std::vector<CPoint>& vecPt);
	size_t GetLinearPoints(std::vector<CPoint>& vecPt);
	double m_A; //переменная типа double
	double m_B; //аналогично следующие
	double m_C;
	double m_D;
	double m_E;
	double m_ACC;
	int m_NumDigits;
protected: //следующие члены класса будут доступны только внутри самого класса и производных классов
	CTrans m_Trans; //объект класса CTrans, для преобразования координат
	std::vector<CPoint> m_vecPt; //вектор, хранящий точки синусоиды
	std::vector<CPoint> m_vecLinear; //вектор, хранящий точки линейной функции
protected:
	bool Calc(); //проверка выполнения вычислений
	bool bCreated = false;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy); //используется для изменения размера окна
	virtual size_t IGetSinPoints(std::vector<CPoint>& vec); //вызывается виртуальная функция для значений синусоиды
	virtual size_t IGetLinearPoints(std::vector<CPoint>& vec);//вызывается виртуальная функция для значений линейного графика
	afx_msg void OnTimer(UINT_PTR nIDEvent); //меняет параметры m_A m_B и т.д. с течением времени
	void OnBnClickedBtnAnime(); //включает или выключает анимацию
	afx_msg void OnCbnSelchangeComboCol(); //выбор цвета фона графика
protected:
	int SavePic(); //сохранения изображения
};
