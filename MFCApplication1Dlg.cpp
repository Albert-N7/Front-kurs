//Nigmatulin
//20250420
//ver 5.0
// MFCApplication1Dlg.cpp: файл реализации


#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "Idata.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <initguid.h>
DEFINE_GUID(imageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b, 0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CMFCApplication1Dlg



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/) 
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_A(0) //инициализация параметров
	, m_B(0)
	, m_C(0)
	, m_D(0)
	, m_E(0)
	, m_ACC(0.0001)
	, m_NumDigits(3)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX) //используется для синхронизации полей диалогового окна с переменными в классе
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_A, m_EditA);
	DDX_Control(pDX, IDC_EDIT_B, m_EditB);
	DDX_Control(pDX, IDC_EDIT_C, m_EditC);
	DDX_Control(pDX, IDC_EDIT_D, m_EditD);
	DDX_Control(pDX, IDC_EDIT_E, m_EditE);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx) //карта сообщений
	ON_WM_SYSCOMMAND() //обрабатывает системные команды
	ON_WM_PAINT()//обрабатывает перерисовку окна
	ON_WM_QUERYDRAGICON() //получение значка, при измененении положения окна
	ON_WM_SIZE() //обрабатывает изменения окна
	ON_WM_TIMER() //вызывает метод таймера
	ON_BN_CLICKED(IDC_BTN_ANIME, &CMFCApplication1Dlg::OnBnClickedBtnAnime) //вызывает анимацию
	ON_CBN_SELCHANGE(IDC_COMBO_COL, &CMFCApplication1Dlg::OnCbnSelchangeComboCol) //вызывает метод для изменения цвета фона
	ON_EN_CHANGE(IDC_EDIT_A, &CMFCApplication1Dlg::OnEnChangeEditA) // обрабатывает изменения текста в поле IDC_EDIT_A
	ON_EN_CHANGE(IDC_EDIT_B, &CMFCApplication1Dlg::OnEnChangeEditB)// обрабатывает изменения текста в поле IDC_EDIT_B
	ON_EN_CHANGE(IDC_EDIT_C, &CMFCApplication1Dlg::OnEnChangeEditC)// обрабатывает изменения текста в поле IDC_EDIT_C
	ON_EN_CHANGE(IDC_EDIT_D, &CMFCApplication1Dlg::OnEnChangeEditD)// обрабатывает изменения текста в поле IDC_EDIT_D
	ON_EN_CHANGE(IDC_EDIT_E, &CMFCApplication1Dlg::OnEnChangeEditE)// обрабатывает изменения текста в поле IDC_EDIT_E
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)//обрабатывает нажатие кнопки OK
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2) //обрабатывает изменение точности поиска корня
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplication1Dlg

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);

		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		bNameValid = strAboutMenu.LoadString(IDS_SAVEPIC);

		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDD_SAVEPIC, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	m_artist.SubclassDlgItem(IDD_ARTIST, this); //связь диалогового окна с объектом m_artist
	CRect rc; //Создается объект rc класса CRect
	m_artist.GetClientRect(&rc); //он хранит в себе координаты окна управления 
	m_Trans.SetTrancParam(rc.Width(), rc.Height());  //устанавливает параметры преобразования
	m_artist.SetIdataPtr(this); //метод который передает текущий объект в m_artist
	m_artist.SetCalculation(&m_Calculation, &params, &m_Trans); //связывает m_artist с объектами для расчета и преобразования
	m_artist.SetParams(&params); // Передаем параметры в CArtist
	CWinApp* pApp = AfxGetApp(); //получаем указатель на приложение
	m_A = pApp->GetProfileIntW(_T("Settings"), _T("Amplitude"), 10) / 10.; //получаем из приложения значение амплитуды
	CString strT; //создаем объект класса CString
	strT.Format(L"%.1f", m_A); //форматируем m_A в строку с одной цифрой после запятой
	m_EditA.SetWindowTextW(strT); // устанавливаем полученное значение как текст элемента управление m_EditA 
	int nSel = pApp->GetProfileIntW(_T("Settings"), _T("Combo"), 0); //получается значение переменной nSel и записывается в Combo
	
	m_B = pApp->GetProfileIntW(_T("Settings"), _T("Frequency"), 10) / 10.; //получаем из приложения значение частоты функции 
	strT.Format(L"%.1f", m_B); //форматируем m_B в строку с одной цифрой после запятой
	m_EditB.SetWindowTextW(strT);// устанавливаем полученное значение как текст элемента управление m_EditB
	
	m_C = pApp->GetProfileIntW(_T("Settings"), _T("Intersection"), 10) / 10.;//получаем из приложения значение пересечения с осью
	strT.Format(L"%.1f", m_C);//форматируем m_C в строку с одной цифрой после запятой
	m_EditC.SetWindowTextW(strT);// устанавливаем полученное значение как текст элемента управление m_EditC
	
	m_D = pApp->GetProfileIntW(_T("Settings"), _T("Rate"), 10) / 10.;//получаем из приложения значение скорости возрастания функции
	strT.Format(L"%.1f", m_D);//форматируем m_D в строку с одной цифрой после запятой
	m_EditD.SetWindowTextW(strT);// устанавливаем полученное значение как текст элемента управление m_EditD
	
	// Чтение m_E как строки – если значение отсутствует, используем "0"
	CString strPoint = pApp->GetProfileString(_T("Settings"), _T("Point"), _T("0"));
	// Проверяем, что прочитанное значение корректное:
	if (strPoint.IsEmpty())
	{
		strPoint = _T("0"); // Если значение отсутствует, используем "0"
	}
	// Преобразуем строку в целое число и делим на 10, чтобы получить m_E с нужным знаком
	m_E = _wtoi(strPoint) / 10.0;
	strT.Format(L"%.1f", m_E);
	m_EditE.SetWindowTextW(strT);
	
	m_ACC = pApp->GetProfileIntW(_T("Settings"), _T("Accuracy"), 10) / 10000.0; //получаем из приложения значение частоты функции 
	if (m_ACC <= 0.0) {
		m_ACC = 0.0001; // Значение по умолчанию, если точность недопустима
	}
	strT.Format(L"%.3f", m_ACC); //форматируем m_ACC в строку с тремя цифрами после запятой
	m_Edit2.SetWindowTextW(strT);// устанавливаем полученное значение как текст элемента управление m_Edit2

	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL); //возвращает элемент выбора цвета
	if (pCmb) //если pCmb не 0
	{
		pCmb->SetCurSel(0); //устанавливает первый элемент
		OnCbnSelchangeComboCol(); //обрабатывает изменения выбора цвета
	}
	bCreated = true; //окно готово к работе.
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (IDD_SAVEPIC == (nID & 0xFFF0))
	{
		SavePic();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication1Dlg::OnPaint() //метод OnPaint вызывается когда окно необходимо перерисовать 
{
	if (IsIconic()) //проверка свернуто ли окно
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON); //Получает ширину значка системы с помощью функции GetSystemMetrics
		int cyIcon = GetSystemMetrics(SM_CYICON); //Получает высоту значка сист	емы
		CRect rect; //Создается объект rect класса CRect
		GetClientRect(&rect); //заполняет объект rect координатами клиентской области окна
		int x = (rect.Width() - cxIcon + 1) / 2; //Вычисляется горизонтальная позиция
		int y = (rect.Height() - cyIcon + 1) / 2; //Вычисляется вертикальная позиция

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon); //Рисуется значок в вычисленной позиции (x, y)
	}
	else
	{
		CDialogEx::OnPaint(); //Если окно не свернуто вызывается функция OnPaint
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::OnEnChangeEditA() //обрабатывает изменения текста в текстовом окне m_EditA
{
	CString strT; //создаем объект strT класса CString
	m_EditA.GetWindowTextW(strT); //получаем текст из поля редактирования и сохраняем его в переменную strT
	m_A = _wtof(strT); //Преобразует строку strT в число с плавающей точкой. Результат сохраняется в переменной m_A
	params.a = m_A; // Обновляем параметры
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
}



void CMFCApplication1Dlg::OnEnChangeEditB()
{
	CString strT; //создаем объект strT класса CString
	m_EditB.GetWindowTextW(strT); //получаем текст из поля редактирования и сохраняем его в переменную strT
	m_B = _wtof(strT); //Преобразует строку strT в число с плавающей точкой. Результат сохраняется в переменной m_B
	params.b = m_B; // Обновляем параметры
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
}

void CMFCApplication1Dlg::OnEnChangeEditC()
{
	CString strT; //создаем объект strT класса CString
	m_EditC.GetWindowTextW(strT); //получаем текст из поля редактирования и сохраняем его в переменную strT
	m_C = _wtof(strT); //Преобразует строку strT в число с плавающей точкой. Результат сохраняется в переменной m_C
	params.c = m_C; // Обновляем параметры
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
}
void CMFCApplication1Dlg::OnEnChangeEditD()
{
	CString strT; //создаем объект strT класса CString
	m_EditD.GetWindowTextW(strT); //получаем текст из поля редактирования и сохраняем его в переменную strT
	m_D = _wtof(strT); //Преобразует строку strT в число с плавающей точкой. Результат сохраняется в переменной m_D
	params.d = m_D; // Обновляем параметры
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
}

void CMFCApplication1Dlg::OnEnChangeEditE()
{
	CString strT; //создаем объект strT класса CString
	m_EditE.GetWindowTextW(strT); //получаем текст из поля редактирования и сохраняем его в переменную strT
	m_E = _wtof(strT); //Преобразует строку strT в число с плавающей точкой. Результат сохраняется в переменной m_E
	params.e = m_E; // Обновляем параметры
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
}

void CMFCApplication1Dlg::OnEnChangeEdit2() //точность поиска корня
{
	CString strDigits; //Создаётся строковая переменная strDigits
	m_Edit2.GetWindowText(strDigits); //Значение, введённое пользователем в элемент управления m_Edit2 сохраняется в strDigits.


	int userPrecision = _wtoi(strDigits);	// Преобразуем введённую строку в целое число:


	if (userPrecision < 1) // Если пользователь ввёл отрицательное число или 0
	{
		//AfxMessageBox(_T("Введите положительное число знаков после запятой."));
		userPrecision = 3; // выводим значение по умолчанию 3
		m_Edit2.SetWindowText(_T("3"));
	}

	m_NumDigits = userPrecision;// Сохраним число знаков в переменной m_NumDigits:

	m_artist.SetPrecision(m_NumDigits);// Передаём значение в объект CArtist

	Calc(); //вызываем метод Calc()
	m_artist.Invalidate(); //область рисования "недействительная" -> обновление отображения
}

size_t CMFCApplication1Dlg::GetSinPoints(std::vector<CPoint>& vecPt) //функция, которая заполняет vecPt точками синусоиды
{
	vecPt = m_vecPt;
	return m_vecPt.size();
}

size_t CMFCApplication1Dlg::GetLinearPoints(std::vector<CPoint>& vecPt) //функция которая заполняет vecPt точками линейной функции
{
	vecPt = m_vecLinear;
	return m_vecLinear.size();
}

bool CMFCApplication1Dlg::Calc()
{
	m_vecPt.clear(); // Очищаем вектор точек
	m_vecLinear.clear(); // Очищаем вектор точек линейной функции

	CRect rc; //создается объект CRect
	m_artist.GetClientRect(&rc); // он заполняется размерами области рисования
	if (rc.Width() <= 2 * BORDER_W) return false; //проверка длины области рисования
	double step = (2.0 * M_PI) / (rc.Width() - 2 * BORDER_W); // Шаг для генерации точек
	int numPoints = static_cast<int>((2.0 * M_PI) / step); //количество точек генерации
	double scaleX = (rc.Width() - 2 * BORDER_W) / (2.0 * M_PI); //коэффициенты масштабирования для горизонтальной оси
	double scaleY = rc.Height() / 4.0; //высота области для рисования
	// Заполняем параметры для синусоиды
	Parameters sinParams; 
	sinParams.a = m_A;
	sinParams.b = m_B;
	sinParams.c = m_C;
	sinParams.d = 0.0; // Не используется для синусоиды
	sinParams.e = 0.0; // Не используется для синусоиды

	 //Заполняем параметры для линейной функции
	Parameters linearParams;
	linearParams.a = 0.0; // Не используется для линейной функции
	linearParams.b = 0.0; // Не используется для линейной функции
	linearParams.c = 0.0; // Не используется для линейной функции
	linearParams.d = m_D;
	linearParams.e = m_E;

	for (double X = -M_PI/*0.*/; X < /*2.0 **/ M_PI; X += step) //цикл от -пи до пи с шагом step
	{
		CPoint ptSin = m_Trans.Trans(X, sinParams); //вычисляется координата синусоиды
		m_vecPt.push_back(ptSin);//записывается в m_vecPt

		//// Точки для линейной функции
		CPoint ptLinear = m_Trans.Trans(X, linearParams); //определяется координата линейной функции
		m_vecLinear.push_back(ptLinear);//записывается в m_vecLinear
	}
	return !m_vecPt.empty() && !m_vecLinear.empty(); //возвращает true если есть хотя бы по одной точки
}

void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy); //вызывается реализация метода OnSize из базового класса CDialogEx
	if (bCreated)//проверка, создан ли диалог
	{
		CRect rc; //создаем объект rc
		m_artist.GetClientRect(&rc); //заполняем объект размерами клиентской области окна
		m_Trans.SetTrancParam(rc.Width(), rc.Height()); //устанавливаем параметры изменения окна
		Calc(); //вызывается метод Calc()

	}
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	m_A += 0.01; //увеличивает параметр синусоиды на 1 градус
	m_B += M_PI / 180;
	m_C += 0.01;
	m_D += 0.01; //изменяет наклон линейной функции на 0.01
	m_E -= 0.01;
	Calc(); //вызывается метод Calc
	m_artist.Invalidate(); //помечает область элемента управления m_artist как недействительную, что приводит к перерисовке этого элемента
	// Обновляем текст в контролах Edit согласно новым значениям
	CString str;

	str.Format(_T("%.2f"), m_A);
	m_EditA.SetWindowText(str);

	str.Format(_T("%.2f"), m_B);
	m_EditB.SetWindowText(str);

	str.Format(_T("%.2f"), m_C);
	m_EditC.SetWindowText(str);

	str.Format(_T("%.2f"), m_D);
	m_EditD.SetWindowText(str);

	str.Format(_T("%.2f"), m_E);
	m_EditE.SetWindowText(str);
	TRACE("Timer\n"); //вывод сообщения о работе таймера в меню окладки
	__super::OnTimer(nIDEvent); //вызывает реализацию метода OnTimer из базового класса
}

void CMFCApplication1Dlg::OnBnClickedBtnAnime()
{
	const int target_fps = 144; // Целевая частота кадров
	const int debug_factor = 1.6; // Поправочный коэффициент для Debug x86
	int delay_ms = static_cast<int>((1000 / target_fps) * debug_factor);
	CButton* pB = (CButton*)GetDlgItem(IDC_BTN_ANIME); //указатель на элемент управления
	if (pB) //если кнопка нажата выполняется: 
	{
		if (pB->GetCheck())//если кнопка "нажата"
		{
			SetTimer(ID_TIMERA, delay_ms, nullptr); //запускается таймер с интервалом в delay_ms миллисекунд
		}
		else
			KillTimer(ID_TIMERA); //если кнопка выключена таймер останавливается
	}
}

void CMFCApplication1Dlg::OnCbnSelchangeComboCol()
{
	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL);
	if (pCmb)
	{
		int nSel = pCmb->GetCurSel();
		switch (nSel)
		{
		case 0:
			// Тёмная тема:
			m_artist.SetBkColor(RGB(30, 30, 30));       // Тёмный фон
			m_artist.SetAxisColor(RGB(220, 220, 220));    // Светлые оси
			m_artist.SetSinColor(RGB(0, 128, 255));       // Синий для синусоиды
			m_artist.SetLinearColor(RGB(255, 165, 0));      // Оранжевый для линейной функции
			break;
		case 1:
			// Светлая тема:
			m_artist.SetBkColor(RGB(255, 255, 255));      // Белый фон
			m_artist.SetAxisColor(RGB(0, 0, 0));           // Чёрные оси
			m_artist.SetSinColor(RGB(0, 0, 200));          // Темно-синий для синусоиды
			m_artist.SetLinearColor(RGB(200, 0, 0));         // Красный для линейной функции
			break;
		case 2:
			// Лавандовая тема:
			m_artist.SetBkColor(RGB(230, 230, 250));       // Лавандовый фон
			m_artist.SetAxisColor(RGB(75, 0, 130));          // Тёмно-фиолетовые оси
			m_artist.SetSinColor(RGB(0, 160, 0));          // Тёмно-зелёный для синусоиды
			m_artist.SetLinearColor(RGB(220, 20, 60));       // Кримсон для линейной функции
			break;
		default:
			break;
		}
		m_artist.SetRedrawFlag(true);
		m_artist.RedrawWindow();
	}
}

size_t CMFCApplication1Dlg::IGetSinPoints(std::vector<CPoint>& vec)
{
	return GetSinPoints(vec);
}
size_t CMFCApplication1Dlg::IGetLinearPoints(std::vector<CPoint>& vec)
{
	return GetLinearPoints(vec);
}



int CMFCApplication1Dlg::SavePic() //сохранение изображения
{
	CDC MemDc;
	CBitmap BitMap;
	CDC* pDca = m_artist.GetDC();     // Получаем контекст устройства для объекта m_artist, из которого нужно сохранить изображение
	MemDc.CreateCompatibleDC(pDca);  // Создаем контекст памяти, совместимый с pDca
	CRect rc;
	m_artist.GetClientRect(&rc); // получаем размеры клиентской области m_artist
	BitMap.CreateCompatibleBitmap(pDca, rc.Width(), rc.Height());  // Создаем битовую карту, совместимую с pDca и с размерами клиентской области
	HGDIOBJ ob = MemDc.SelectObject(&BitMap);  // Выбираем созданную битовую карту в контекст памяти
	MemDc.BitBlt(0, 0, rc.Width(), rc.Height(), pDca, 0, 0, SRCCOPY);  // Копируем изображение из контекста m_artist в контекст памяти
	m_artist.ReleaseDC(pDca); // Освобождаем контекст устройства, ранее полученный через GetDC()
	MemDc.SelectObject(ob); // Восстанавливаем выбранный объект
	//static wchar_t szFilter[] = _T("BMP files (*.bmp)|.bmp|", "||"); // Задаем фильтр для диалогового окна выбора файла (BMP файлы)
	static wchar_t szFilter[] = _T("BMP files (*.bmp)|*.bmp||");
	CFileDialog dlg(FALSE, _T("bmp"), NULL, 6, szFilter);
	if (IDOK == dlg.DoModal())   // Если пользователь подтвердит выбор файла (нажмет ОК)
	{
		CImage image;   // Создаем объект CImage и прикрепляем к нему HBITMAP
		image.Attach(HBITMAP(BitMap)); //связывает объект CImage с растровым изображением, для того чтобы использовать функциональность класса CImage	
		CString strFull = dlg.GetOFN().lpstrFile;   // Получаем полный путь и имя файла, выбранного пользователем
		HRESULT hr = image.Save(strFull, imageFormatBMP);   // Сохраняем изображение в формате BMP по указанному пути
		if (S_OK == hr) //если операция прошла успешно
		{ 
			AfxMessageBox(_T("Изображение успешно сохранено!"), MB_ICONINFORMATION);
		}
	}
	else
		AfxMessageBox(_T("Вы забыли сохранить изображение!:("), MB_ICONINFORMATION);
	return 0;
}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	CWinApp* pApp = AfxGetApp(); //указатель на объект приложения
	pApp->WriteProfileInt(_T("Settings"), _T("Amplitude"), floor(m_A * 10 + .5)); //сохраняем параметр амплитуда
	pApp->WriteProfileInt(_T("Settings"), _T("Frequency"), floor(m_B * 10 + .5)); //сохраняем параметр частоты
	pApp->WriteProfileInt(_T("Settings"), _T("Intersection"), floor(m_C * 10 + .5)); //сохраняем параметр пересечения
	pApp->WriteProfileInt(_T("Settings"), _T("Rate"), floor(m_D * 10 + .5)); //сохраняем параметр скорости изменения линейной функции
	
	CString strPoint; //создаем объект CString для размещения текстового представления.
	strPoint.Format(_T("%d"), static_cast<int>(floor(m_E * 10 + 0.5))); // Результат переводим в строковое представление с помощью метода Format.
	pApp->WriteProfileString(_T("Settings"), _T("Point"), strPoint); // Сохраняем значение параметра "Point" в секции "Settings" как строку.

	pApp->WriteProfileInt(_T("Settings"), _T("AccuracyDigits"), m_NumDigits); //сохраняем параметр, который обозначает количество знаков после запятой
	pApp->WriteProfileInt(_T("Settings"), _T("Accuracy"), static_cast<int>(m_ACC * 10000.0)); //сохраняем параметр точности
	
	CComboBox* pCmb = (CComboBox*)GetDlgItem(IDC_COMBO_COL); //ищем элемент управления и возвращаем его значение
	if (pCmb)
	{
		int nSel = pCmb->GetCurSel(); //возвращает индекс выбранного элемента
		pApp->WriteProfileInt(_T("Settings"), _T("Combo"), nSel); //данный индекс записывается в реестр с именем Combo
	}
	CDialogEx::OnOK(); //вызывается базовая реализация кнопки "OK"
}

//BOOL CMFCApplication1Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	/*CPoint pt;
//	::GetCursorPos(&pt);*/
//	m_artist.ScreenToClient(&pt);
//	CRect rc;
//	m_artist.GetClientRect(&rc);
//	if (rc.PtInRect(pt))
//	{
//		/*if(zDelta>0)*/
//		switch (nFlags)
//		{
//		case 0: m_Trans.Shift(0, zDelta / 10); break;
//		case 4: m_Trans.Shift(zDelta / 10, 0); break;
//		case 8: m_Trans.Shift(0, zDelta / 10, 0); break;
//		}
//		
//		Calc();
//		m_artist.RedrawWindow();
//	}
//	return __super::OnMouseWheel(nFlags, zDelta, pt); 
//}

	