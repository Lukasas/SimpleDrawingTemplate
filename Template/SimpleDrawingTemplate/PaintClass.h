#pragma once
//#define GDI_PLUS_PAINT
//#define DIRECTX
//#ifdef GDI_PLUS_PAINT
//
//#include "GdiPlusPaint.h"
//class PaintClass :
//	public GdiPlusPaint
//#elseif DIRECTX
//#else
//#include "GdiPaint.h"
//class PaintClass :
//	public GdiPaint
//#endif // GDI_PLUS_PAINT

#include "Direct2DPaint.h"
	class PaintClass :
	public Direct2DPaint
{
public:
	PaintClass(HWND hWnd) : 
//
//#ifdef GDI_PLUS_PAINT
//		GdiPlusPaint(hWnd)
//#else
//		GdiPaint(hWnd)
//#endif // GDI_PLUS_PAINT
	Direct2DPaint(hWnd)
	{
		SetDrawingMode(Fullscreen);
		Setup();
	}

	virtual void Setup();
	virtual void Render();

	virtual ~PaintClass();
};

