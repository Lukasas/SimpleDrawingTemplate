#pragma once


#define DIRECTX 1
//#define GDI_PLUS_PAINT 1
#ifdef GDI_PLUS_PAINT
#include "GdiPlusPaint.h"
class PaintClass :
	public GdiPlusPaint
#elif DIRECTX
#include <Direct2DPaint.h>
class PaintClass :
	public Direct2DPaint
#else
#include "GdiPaint.h"
class PaintClass :
	public GdiPaint
#endif
{
public:
	PaintClass(HWND hWnd) : 

#ifdef GDI_PLUS_PAINT
		GdiPlusPaint(hWnd)
#elif DIRECTX
		Direct2DPaint(hWnd)
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

