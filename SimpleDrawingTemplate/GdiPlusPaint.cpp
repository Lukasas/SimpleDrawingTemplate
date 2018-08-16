#include "GdiPlusPaint.h"

using namespace Gdiplus;


GdiPlusPaint::GdiPlusPaint(HWND hWnd) : BasePaint(hWnd)
{
	GdiplusStartup(&this->gdiplusToken, &this->gdiplusStartupInput, NULL);
	
	this->pen = new Pen(Color(255, 0, 0, 0));
	this->brush = new SolidBrush(Color(255, 0, 0, 0));
	this->bmp = NULL;
	this->pGraphics = NULL;
	this->pMemGraphics = NULL;
	this->bd = new BitmapData();
}

void GdiPlusPaint::Line(int startX, int startY, int endX, int endY, COLORREF color)
{
	SetPenColor(color);
	this->pMemGraphics->DrawLine(pen, startX, startY, endX, endY);
}

void GdiPlusPaint::Pixel(int x, int y, COLORREF color) 
{
	if (x > WindowWidth() || y > WindowHeight() || x < 0 || y < 0)
		return;
	this->bmp->LockBits(NULL, ImageLockModeWrite, this->bmp->GetPixelFormat(), bd);
	((int*)bd->Scan0)[x + WindowWidth() * y] = 0xFF000000 | color;
	this->bmp->UnlockBits(bd);
}
	 
void GdiPlusPaint::SetBackground(COLORREF color)
{
	SetBrushColor(color);
	this->pMemGraphics->FillRectangle(brush, 0, 0, this->WindowWidth(), this->WindowHeight());
}

void GdiPlusPaint::Rectangle(int x, int y, int width, int height, COLORREF pen) 
{
	SetPenColor(pen);
	this->pMemGraphics->DrawRectangle(this->pen, x, y, width, height);
}

void GdiPlusPaint::Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	SetBrushColor(brush);
	this->pMemGraphics->FillRectangle(this->brush, x, y, width, height);
	Rectangle(x, y, width, height, pen);
}

void GdiPlusPaint::Ellipse(int x, int y, int width, int height, COLORREF pen)
{
	SetPenColor(pen);
	this->pMemGraphics->DrawEllipse(this->pen, x, y, width, height);
}

void GdiPlusPaint::Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	SetBrushColor(brush);
	this->pMemGraphics->FillEllipse(this->brush, x, y, width, height);
	Ellipse(x, y, width, height, pen);
}

void GdiPlusPaint::SetPenColor(COLORREF color)
{
	tempColor.SetFromCOLORREF(color);
	pen->SetColor(tempColor);
}

void GdiPlusPaint::SetBrushColor(COLORREF color)
{
	tempColor.SetFromCOLORREF(color);
	brush->SetColor(tempColor);
}

GdiPlusPaint::~GdiPlusPaint()
{
	if (this->brush)
		delete this->brush;
	if (this->pen)
		delete this->pen;
	if (this->bmp)
		delete this->bmp;
	if (this->pGraphics)
		delete this->pGraphics;
	if (this->pMemGraphics)
		delete this->pMemGraphics;

	if (this->bd)
		delete bd;

	GdiplusShutdown(this->gdiplusToken);
}

void GdiPlusPaint::CreateDrawingContent(const int width, const int height)
{
	if (this->pGraphics)
		delete this->pGraphics;
	if (this->pMemGraphics)
		delete this->pMemGraphics;
	if (this->bmp)
		delete this->bmp;

	BasePaint::CreateDrawingContent(width, height);
	bmp = new Bitmap(width, height);
	this->pMemGraphics = Graphics::FromImage(bmp);
	this->pGraphics = Graphics::FromHDC(hdcmem);
}

void GdiPlusPaint::Paint()
{
	//BitBlt(hdcmem, 0, 0, WindowWidth(), WindowHeight(), this->graphics->GetHDC(), 0, 0, SRCCOPY);
	pGraphics->DrawImage(bmp, 0, 0);
	BasePaint::Paint();
}