#pragma once
#include "BasePaint.h"
class GdiPaint :
	public BasePaint
{
private:
	RECT fillRectDrawing;
	COLORREF penColorBackup;
	COLORREF brushColorBackup;

	HBRUSH CreateBrush(COLORREF color);
	void DestroyBrush(HBRUSH brush);
public:
	GdiPaint(HWND hWnd);
	virtual ~GdiPaint();


	/* Drawing Functions */

	void Line(int startX, int startY, int endX, int endY, COLORREF color = 0);
	void Pixel(int x, int y, COLORREF color = 0);
	void SetBackground(COLORREF color = 0);
	void Rectangle(int x, int y, int width, int height, COLORREF pen);
	void Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	void Ellipse(int x, int y, int width, int height, COLORREF pen);
	void Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	void SetPenColor(COLORREF color);
	void ResetPenColor();
	void SetPenTransparency(bool);
	void SetBrushTransparency(bool);

	void SetBrushColor(COLORREF color);
	void ResetBrushColor();
};

