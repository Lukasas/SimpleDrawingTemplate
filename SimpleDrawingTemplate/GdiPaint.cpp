#include "GdiPaint.h"



GdiPaint::GdiPaint(HWND hWnd) : BasePaint(hWnd)
{
	SetupRenderer();
}

GdiPaint::~GdiPaint()
{
	Cleanup();
}

void GdiPaint::RecalculateWindowSizes()
{
	BasePaint::RecalculateWindowSizes();
	SetupRenderer();
}

void GdiPaint::Cleanup()
{
	if (!this->hdcmem)
	{
		SelectObject(this->hdcmem, this->oldhbmp);
		DeleteDC(this->hdcmem);
	}

	if (!this->hbmp)
	{
		DeleteObject(this->hbmp);
	}
}

void GdiPaint::Paint()
{
	BasePaint::Paint();
	StretchBlt(this->GetWindowDC(), 0, 0, this->GetWindowWidth(), this->GetWindowHeight(), this->hdcmem, 0, 0, this->GetPaintingWidth(), this->GetPaintingHeight(), SRCCOPY);
}

void GdiPaint::SetupRenderer()
{
	Cleanup();

	this->hdcmem = CreateCompatibleDC(GetWindowDC());
	this->hbmp = CreateCompatibleBitmap(GetWindowDC(), this->GetPaintingWidth(), this->GetPaintingHeight());

	this->oldhbmp = (HBITMAP)SelectObject(this->hdcmem, this->hbmp); 

	SelectObject(this->hdcmem, GetStockObject(DC_BRUSH));
	SelectObject(this->hdcmem, GetStockObject(DC_PEN));
}

HBRUSH GdiPaint::CreateBrush(COLORREF color)
{
	return CreateSolidBrush(color);
}

void GdiPaint::DestroyBrush(HBRUSH brush)
{
	DeleteObject(brush);
}

void GdiPaint::Line(int startX, int startY, int endX, int endY, COLORREF color)
{
	MoveToEx(this->hdcmem, startX, startY, NULL);
	SetPenColor(color);
	LineTo(this->hdcmem, endX, endY);
	ResetPenColor();
}

void GdiPaint::Pixel(int x, int y, COLORREF color)
{
	SetPixel(hdcmem, x, y, color);
}

void GdiPaint::SetBackground(COLORREF color)
{
	HBRUSH brush = CreateBrush(color);
	FillRect(this->hdcmem, &WindowRect(), brush);
	DestroyBrush(brush);

}

void GdiPaint::Rectangle(int x, int y, int width, int height, COLORREF pen)
{
	SetPenColor(pen);
	::Rectangle(this->hdcmem, x, y, x + width, y + height);
	ResetPenColor();
}

void GdiPaint::Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	HBRUSH tempBrush = CreateBrush(brush);
	Rectangle(x, y, width, height, pen);
	fillRectDrawing.left = x + 1;
	fillRectDrawing.top = y + 1;
	fillRectDrawing.right = x + width - 1;
	fillRectDrawing.bottom = y + height - 1;
	FillRect(hdcmem, &fillRectDrawing, tempBrush);
	DestroyBrush(tempBrush);

}

void GdiPaint::Ellipse(int x, int y, int width, int height, COLORREF pen)
{
	SetPenColor(pen);
	::Ellipse(this->hdcmem, x, y, x + width, y + height);
	ResetPenColor();
}

void GdiPaint::Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	SetBrushColor(brush);
	Ellipse(x, y, width, height, pen);
	ResetBrushColor();
}

void GdiPaint::SetPenColor(COLORREF color)
{
	this->penColorBackup = SetDCPenColor(this->hdcmem, color);
}

void GdiPaint::ResetPenColor()
{
	SetDCPenColor(this->hdcmem, this->penColorBackup);
}

void GdiPaint::SetPenTransparency(bool transparent)
{
	SelectObject(hdcmem, GetStockObject(transparent ? NULL_PEN : DC_PEN));
}

void GdiPaint::SetBrushColor(COLORREF color)
{
	this->brushColorBackup = SetDCBrushColor(this->hdcmem, color);
}

void GdiPaint::ResetBrushColor()
{
	SetDCPenColor(this->hdcmem, this->brushColorBackup);
}

void GdiPaint::SetBrushTransparency(bool transparent)
{
	SelectObject(hdcmem, GetStockObject(transparent ? NULL_BRUSH : DC_BRUSH));
}
