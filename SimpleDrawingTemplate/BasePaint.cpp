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
}



void BasePaint::Cleanup()
{

}

void BasePaint::RecalculateWindowSizes()
{
	GetClientRect(this->hWnd, &this->windowRect);
	this->width = this->windowRect.right - this->windowRect.left;
	this->height = this->windowRect.bottom - this->windowRect.top;
	this->paintingWidth = this->width;
	this->paintingHeight = this->height;
	if (this->eDraw == Fullscreen)
	{
		this->ResizePainting(this->width, this->height);
	}
}

BasePaint::~BasePaint()
{
	Cleanup();
	ReleaseDC(this->hWnd, hdc);
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
}


