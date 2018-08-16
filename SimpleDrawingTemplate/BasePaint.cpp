#include "BasePaint.h"



BasePaint::BasePaint(HWND hWnd)
{
	SetWindowHandle(hWnd);
	fDown = NULL;
	fUp = NULL;
}

void BasePaint::ResizePainting(const int width, const int height)
{
	this->paintingWidth = width;
	this->paintingHeight = height;

	CreateDrawingContent(this->paintingWidth, this->paintingHeight);
}

void BasePaint::CreateDrawingContent(const int width, const int height)
{
	Cleanup();	

	this->hdcmem = CreateCompatibleDC(GetDC(this->hWnd));
	this->hbmp = CreateCompatibleBitmap(GetDC(this->hWnd), width, height);

	this->oldhbmp = (HBITMAP)SelectObject(this->hdcmem, this->hbmp); 

	SelectObject(this->hdcmem, GetStockObject(DC_BRUSH));
	SelectObject(this->hdcmem, GetStockObject(DC_PEN));
}


void BasePaint::Cleanup()
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

BasePaint::~BasePaint()
{
	Cleanup();
}

void BasePaint::RegisterMouseEvent(MouseEventFn f, MouseEvent event)
{
	if (event == MouseDown)
	{
		this->fDown = f;
	}
	else if (event == MouseUp)
	{
		this->fUp = f;
	}
}

void BasePaint::SendMousePressEvent(MouseButton mb, MouseEvent event, Position p)
{
	if (event == MouseDown)
	{
		if (this->fDown != NULL)
		{
			this->fDown(mb, p);
		}
	}
	else if (event == MouseUp)
	{
		if (this->fUp != NULL)
		{
			this->fUp(mb, p);
		}
	}
}

void BasePaint::Paint()
{
	Render();
	
	StretchBlt(this->hdc, 0, 0, this->width, this->height, this->hdcmem, 0, 0, this->paintingWidth, this->paintingHeight, SRCCOPY);
	
}


