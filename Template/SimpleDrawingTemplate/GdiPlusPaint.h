#pragma once
#include "BasePaint.h"
#include <gdiplus.h>
#pragma comment (lib, "gdiplus.lib")

class GdiPlusPaint :
	public BasePaint
{
private:
	Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
	ULONG_PTR						gdiplusToken;
	Gdiplus::Graphics				*pGraphics;
	Gdiplus::Graphics				*pMemGraphics;
	Gdiplus::Bitmap					*bmp;
	Gdiplus::BitmapData				*bd;
	
	Gdiplus::Pen					*pen;
	Gdiplus::SolidBrush				*brush;

	Gdiplus::Color					tempColor;
public:
	GdiPlusPaint(HWND hWnd);
	virtual ~GdiPlusPaint();
	
	virtual void CreateDrawingContent(const int width, const int height);
	virtual void Paint();
	/* Drawing Functions */

	void Line(int startX, int startY, int endX, int endY, COLORREF color = 0);
	void Pixel(int x, int y, COLORREF color = 0);
	void SetBackground(COLORREF color = 0);
	void Rectangle(int x, int y, int width, int height, COLORREF pen);
	void Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	void Ellipse(int x, int y, int width, int height, COLORREF pen);
	void Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	void SetPenColor(COLORREF color);
	void SetBrushColor(COLORREF color);
};

