#pragma once
//#define GDI_PLUS_PAINT
#ifdef GDI_PLUS_PAINT

#include "GdiPlusPaint.h"
class PaintClass :
	public GdiPlusPaint

#else
#include "GdiPaint.h"
class PaintClass :
	public GdiPaint
#endif // GDI_PLUS_PAINT
{
public:
	PaintClass(HWND hWnd) : 

#ifdef GDI_PLUS_PAINT
		GdiPlusPaint(hWnd)
#else
		GdiPaint(hWnd)
#endif // GDI_PLUS_PAINT
	{
		SetDrawingMode(Fullscreen);
		Setup();
	}

	virtual void Setup();
	virtual void Render();

	virtual ~PaintClass();
};

