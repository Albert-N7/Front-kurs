// CArtist.cpp: файл реализации
//

#include "pch.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "CArtist.h"

// CArtist

IMPLEMENT_DYNAMIC(CArtist, CStatic)
//: bRedraw(true)
//, m_MemDc(nullptr)
//, m_BitMap(nullptr)
CArtist::CArtist()
{
	// Значения по умолчанию:
	m_bkCol = RGB(255, 255, 255);      // белый фон
	m_AxisColor = RGB(0, 0, 0);          // чёрные оси
	m_SinColor = RGB(0, 0, 255);         // синий график синуса
	m_LinearColor = RGB(255, 0, 0);      // красный график линейной функции
}
CArtist::~CArtist()
{
	if (m_MemDc) //если указатель не равен нулю
		delete m_MemDc; //происходит очистка памяти
	if (m_BitMap) //если указатель не равен нулю 
		delete m_BitMap; //очистка выделенной памяти
}



BEGIN_MESSAGE_MAP(CArtist, CStatic)
	ON_WM_PAINT() //отрисовка окна
	ON_WM_SIZE() //изменение окна 
	ON_WM_LBUTTONDOWN() // Добавляем обработчик клика мыши
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()



// обработчики сообщений CArtist
void CArtist::SetParams(Parameters* params) {
	m_params = params; // Сохраняем указатель на параметры
}

void CArtist::SetRedrawFlag(bool flag)
{
	bRedraw = flag; //присваивает значение параметра flag
}

void CArtist::OnPaint()
{
	CPaintDC dc(this);           // Контекст устройства для экрана
	CRect rc;
	GetClientRect(&rc);          // Получаем размеры клиентской области

	// Создаем регион отсечения 
	CRgn reg;
	reg.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 20, 20); //прямоугольник с закругленными углами
	dc.SelectClipRgn(&reg); //ограничивает область рисования этим регионом

	// Создаем совместимый DC и битовую карту для off-screen буферизации
	CDC memDC; //создает совместимый контекст устройства для off-screen рисования
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap; //создаем битовую карту
	bitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height()); //делаем её такого размера, как область рисования 
	CBitmap* pOldBmp = memDC.SelectObject(&bitmap); //выбираем созданную битовую карту в off - screen контекст.Это позволяет рисовать в памяти, а не напрямую на экране.

	memDC.FillSolidRect(&rc, m_bkCol);//Заполняем фон off-screen контексте выбранным фоновым цветом

	//Рисуем оси с использованием m_AxisColor
	{
		CPen penAxis; //Создается объект CPen penAxis — перо для рисования осей.
		penAxis.CreatePen(PS_SOLID, 3, m_AxisColor); //сплошная линия, размер 3, цвет m_AxisColor
		CPen* pOldPen = memDC.SelectObject(&penAxis); //Сохраняется указатель на предыдущее перо
		memDC.MoveTo(rc.left + BORDER_W, rc.CenterPoint().y); //переносит "карандаш" в точку, расположенную слева
		memDC.LineTo(rc.right - BORDER_W, rc.CenterPoint().y); //проводит линию до точки, расположенной справа
		memDC.MoveTo(rc.CenterPoint().x, rc.top + BORDER_W); //аналогично
		memDC.LineTo(rc.CenterPoint().x, rc.bottom - BORDER_W);
		memDC.SelectObject(pOldPen); //Восстанавливаем старое перо, которое было выбрано ранее
	}
	
	{      
		CFont font;  // Создаем шрифт для подписей
		font.CreatePointFont(90, _T("Arial")); // 90 - приблизительный размер (9pt), Arial
		CFont* pOldFont = memDC.SelectObject(&font); //Старый шрифт сохраняется, затем новый шрифт выбирается в контекст memDC

		COLORREF oldTextColor = memDC.SetTextColor(m_AxisColor);// Устанавливаем цвет текста равным цвету оси
		
		CPen tickPen;// Создаем перо для рисования масштаба с тем же цветом оси
		tickPen.CreatePen(PS_SOLID, 1, m_AxisColor); //сплошная линия, 1 размер, цвет совпадающий с цветом осей
		CPen* pOldPenTick = memDC.SelectObject(&tickPen); //сохраняем старое перо, выбираем новое в контексте memDC
		// Определяем центр координат (ось проходит через центр окна)
		int xOrigin = rc.CenterPoint().x;
		int yOrigin = rc.CenterPoint().y;

		// Отрисовка делений по оси X 
		// Вычисляем математические границы для оси X
		double maxMathX = (rc.right - xOrigin - BORDER_W) / m_Trans->m_ScaleX; //Вычисляется выражение с учетом перевода пикселей в математические единицы
		double minMathX = (rc.left + BORDER_W - xOrigin) / m_Trans->m_ScaleX; //Аналогично вычисляется левая граница
		double xStep = 0.5; // фиксированный шаг 

		// Подписи справа от оси (mathX > 0)
		for (double mathVal = xStep; mathVal <= maxMathX; mathVal += xStep) //Цикл проходит по значениям от xStep до maxMathX с шагом xStep — для положительной части оси X.
		{
			int xPos = xOrigin + static_cast<int>(round(mathVal * m_Trans->m_ScaleX)); //Вычисляется экранная координата xPos для данного математического значения mathVal с учетом масштабного коэффициента
			// Рисуем небольшой отрезок вверх и вниз
			memDC.MoveTo(xPos, yOrigin - 5);
			memDC.LineTo(xPos, yOrigin + 5);

			CString label; //создаем строку 
			label.Format(_T("%.1f"), mathVal); //которая будет отвечать за запись чисел масштаба осей
			memDC.TextOut(xPos - 10, yOrigin + 8, label); //выводиться число, смещенное на несколько пикселей, чтобы не накладывалось
		}
		// Подписи слева от оси (mathX < 0)
		for (double mathVal = -xStep; mathVal >= minMathX; mathVal -= xStep) //аналогично для x<0
		{
			int xPos = xOrigin + static_cast<int>(round(mathVal * m_Trans->m_ScaleX));
			memDC.MoveTo(xPos, yOrigin - 5);
			memDC.LineTo(xPos, yOrigin + 5);

			CString label;
			label.Format(_T("%.1f"), mathVal);
			memDC.TextOut(xPos - 10, yOrigin + 8, label);
		}

		//Отрисовка делений по оси Y с фиксированным шагом 0.5
		//Вычисляем математические границы для оси Y
		double maxMathY = (yOrigin - rc.top - BORDER_W) / m_Trans->m_ScaleY;
		double minMathY = -(rc.bottom - yOrigin - BORDER_W) / m_Trans->m_ScaleY;
		double yStep = 0.5; // фиксированный шаг 0.5

		// Деления и подписи для оси Y вверх (mathY > 0)
		for (double mathVal = yStep; mathVal <= maxMathY; mathVal += yStep)
		{
			int yPos = yOrigin - static_cast<int>(round(mathVal * m_Trans->m_ScaleY));
			memDC.MoveTo(xOrigin - 5, yPos);
			memDC.LineTo(xOrigin + 5, yPos);

			CString label;
			label.Format(_T("%.1f"), mathVal);
			memDC.TextOut(xOrigin - 40, yPos - 5, label);
		}
		// Деления и подписи для оси Y вниз (mathY < 0)
		for (double mathVal = -yStep; mathVal >= minMathY; mathVal -= yStep)
		{
			int yPos = yOrigin - static_cast<int>(round(mathVal * m_Trans->m_ScaleY));
			memDC.MoveTo(xOrigin - 5, yPos);
			memDC.LineTo(xOrigin + 5, yPos);

			CString label;
			label.Format(_T("%.1f"), mathVal);
			memDC.TextOut(xOrigin - 40, yPos - 5, label);
		}

		// Восстанавливаем прежний текстовый цвет и шрифт
		memDC.SelectObject(pOldPenTick);
		memDC.SetTextColor(oldTextColor);
		memDC.SelectObject(pOldFont);
	}
	//Рисуем графики (синусоиду и линейную функцию) на off-screen DC
	if (m_Idata)
	{
		// Рисуем синусоиду:
		{
			CPen penSin; //создадим ручку, которая будет отвечать за рисование синусоиды
			penSin.CreatePen(PS_SOLID, 3, m_SinColor); //сплошная линия, 3 размер, с цветом m_SinColor
			CPen* pOldPen = memDC.SelectObject(&penSin);//сохраним прошлую ручку, и выберем для синуса
			std::vector<CPoint> sinPoints; //создадим динамический массив для точек синусоиды
			size_t sz = m_Idata->IGetSinPoints(sinPoints);//получает количество точек синусоиды и сохраняет их в sinPoint
			if (sz > 0)//если sz > 0 выполняется цикл:
			{
				memDC.MoveTo(sinPoints[0]); //перо устанавливается в начальной точке 
				for (auto pt : sinPoints) // цикл который проходит по всем точкам вектора sinPoint и записывает их в Pt
					memDC.LineTo(pt); //рисуется линия из начальной точки к текущей, после чего перо переходит в только назначенную точку
			}
			memDC.SelectObject(pOldPen); //выбирается старое перо
		}
		// Рисуем линейный график:
		{
			CPen penLinear; //аналогично для линейной функции
			penLinear.CreatePen(PS_SOLID, 3, m_LinearColor);
			CPen* pOldPen = memDC.SelectObject(&penLinear);
			std::vector<CPoint> linearPoints;
			size_t ln = m_Idata->IGetLinearPoints(linearPoints);
			if (ln > 0)
			{
				memDC.MoveTo(linearPoints[0]);
				for (auto pt : linearPoints)
					memDC.LineTo(pt);
			}
			memDC.SelectObject(pOldPen);
		}
	}

	//Рисуем рамку с закругленными углами в off-screen DC,
	//чтобы избежать мерцания при анимации и обеспечить корректное заполнение всех углов.
	{
		CPen penFrame; // Создаем перо для рамки
		penFrame.CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); //сплошная линия, 2 размер, цвет черный
		CPen* pOldPen = memDC.SelectObject(&penFrame); //выбираем ручку, сохраняя предыдущее значение
		
		HBRUSH hOldBrush = (HBRUSH)memDC.SelectStockObject(NULL_BRUSH);// Используем NULL-кисть, чтобы не было заливки внутри рамки
		// Для корректной отрисовки всех углов немного записываем рамку внутрь
		CRect rcBorder = rc; 
		rcBorder.DeflateRect(1, 1);
		memDC.RoundRect(&rcBorder, CPoint(20, 20));

		// Восстанавливаем кисть и перо
		memDC.SelectObject(hOldBrush);
		memDC.SelectObject(pOldPen);
	}

	//копируем все из off-screen DC в основной контекст устройства за один вызов BitBlt
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(pOldBmp); //Отменяем выбор битовой карты в памяти
}


void CArtist::OnSize(UINT nType, int cx, int cy) //обработчик изменения размера окна
{
	CStatic::OnSize(nType, cx, cy); //вызываем OnSize()
	bRedraw = true; //при следующем вызове OnPaint() окно перерисовывается
}

void CArtist::SetCalculation(CCalculation* calc, Parameters* params, CTrans* trans) //задает объекты с которыми будет работать CArtist 
{
	m_Calculation = calc; //получает переданный объект, для работы с математическими вычислениями
	m_params = params; //получает параметры из структуры 
	m_Trans = trans; // получает объект, который используется для преобразования координат
}
 

void CArtist::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_params) {
		AfxMessageBox(_T("Параметры не заданы."));
		return;
	}
	// Проверяем, равны ли все параметры 0
	if (m_params->a == 0.0 && m_params->b == 0.0 && m_params->c == 0.0 &&
		m_params->d == 0.0 && m_params->e == 0.0)//если параметры равны 0 выводим:
	{
		AfxMessageBox(_T("Графики не определены (параметры равны 0)."));
		return;
	}

	double clickX = m_Trans->ScreenToMathX(point.x); // Преобразуем координаты экрана в математические

	// Задаем интервал поиска вокруг точки клика
	double searchRadius = 1.0; // радиус поиска в обе стороны
	double left = clickX - searchRadius; //поиск слева
	double right = clickX + searchRadius; //поиск справа
	double step = 0.1; // шаг проверки наличия смены знака
	int iterations = 0; //количество итераций
	double closestRoot = 0.0; //переменная, в которой хранится ближайший корень
	double minDistance = DBL_MAX; //минимальное расстояние от найденного корня до клика, сначала устанавливаем максимально возможное значение, чтобы найденные были всегда меньше
	bool rootFound = false; //проверка найден ли корень 
	double epsilon = 0.5 * pow(10.0, -GetPrecision()); //вычисляем значение переменной, которая отвечает за точность поиска корня
	// Проходим по всему интервалу с заданным шагом 
	for (double x = left; x <= right; x += step) 
	{
		if (m_Calculation->GetDifference(x, *m_params) *
			m_Calculation->GetDifference(x + step, *m_params) <= 0)//проверка на смену знака. Если произведение меньше или равно нулю, значит есть корень 
		{ 

			//Поиск корня методом деления пополам 
			double root = m_Calculation->FindRoot(x, x + step, *m_params, epsilon, iterations);
	/*		double root = m_Calculation->FindRoot(x, x + step, *m_params, m_params->acc, iterations);*/
			double distance = fabs(root - clickX); //вычисление расстояния от корня до точки клика
			// Проверяем, является ли найденный корень ближайшим к точке клика
			if (distance < minDistance) //если расстояние от найденного корня до точки клика меньше текущего минимального расстояния, обновляются значения
			{
				minDistance = distance;
				closestRoot = root;
				rootFound = true; 
			}

	
			x += step; // Переходим к следующему интервалу
		}
	}

	if (rootFound) //если был найден хотя бы один корень 
	{
		CString message;
		int precision = GetPrecision();
		message.Format(_T("Ближайший корень: %.*f\nКоличество итераций: %d"), precision, closestRoot, iterations);
		AfxMessageBox(message);
	}
	else //иначе 
	{
		AfxMessageBox(_T("В выбранной области корней не найдено."));
	}

	CStatic::OnLButtonDown(nFlags, point); // вызывается базовая обработка клика мыши
}

BOOL CArtist::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// Настраиваем коэффициент масштабирования. Можно выбрать желаемый коэффициент изменения
	const double zoomFactor = 1.1; // 10% приближение/отдаление за одну "шаг"

	if (zDelta > 0) // Колесико вращается в сторону приближения
	{
		m_Trans->m_ScaleX *= zoomFactor;
		m_Trans->m_ScaleY *= zoomFactor;
	}
	else if (zDelta < 0) // Колесико вращается для отдаления
	{
		m_Trans->m_ScaleX /= zoomFactor;
		m_Trans->m_ScaleY /= zoomFactor;
	}

	// При необходимости можно пересчитать центр или другие параметры преобразования здесь.
	// Затем инициируем перерисовку.
	Invalidate();  // сообщает системе, что требуется перерисовка, что вызовет OnPaint()

	// Сообщаем, что событие обработано
	return TRUE;
}