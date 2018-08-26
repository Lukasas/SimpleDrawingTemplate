#include "BasePaint.h"



BasePaint::BasePaint(HWND hWnd)
{
	SetWindowHandle(hWnd);
	fDown = NULL;
	fUp = NULL;
	m_redrawinterval = 16;
	this->paintingWidth = this->paintingHeight = 0;
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
	Sleep(this->m_redrawinterval);
}


