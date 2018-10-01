#include "BasePaint.h"



BasePaint::BasePaint(HWND hWnd) :
	m_fDown(NULL),
	m_fUp(NULL),
	m_fMw(NULL),
	m_keyfDown(NULL),
	m_keyfUp(NULL)
{
	SetWindowHandle(hWnd);
	m_redrawinterval = 16;
	this->m_paintingWidth = this->m_paintingHeight = 0;
}

void BasePaint::ResizePainting(const int width, const int height)
{
	this->m_paintingWidth = width;
	this->m_paintingHeight = height;
}



void BasePaint::Cleanup()
{

}

void BasePaint::RecalculateWindowSizes()
{
	GetClientRect(this->m_hWnd, &this->m_windowRect);
	this->m_windowWidth = this->m_windowRect.right - this->m_windowRect.left;
	this->m_windowHeight = this->m_windowRect.bottom - this->m_windowRect.top;
	if (this->m_eDraw == Fullscreen)
	{
		this->ResizePainting(this->m_windowWidth, this->m_windowHeight);
	}
}

BasePaint::~BasePaint()
{
	Cleanup();
	ReleaseDC(this->m_hWnd, m_hdc);
}

void BasePaint::RegisterMouseEvent(MouseEventFn f, MouseEvent event)
{
	if (event == MouseDownEvent)
	{
		this->m_fDown = f;
	}
	else if (event == MouseUpEvent)
	{
		this->m_fUp = f;
	}
}

void BasePaint::RegisterMouseEvent(MouseWheelEventFn f, MouseEvent event)
{
	this->m_fMw = f;
}

void BasePaint::SendMousePressEvent(MouseButton mb, MouseEvent event, Position p, int deltaMouse)
{
	if (this->m_fDown != NULL || this->m_fUp != NULL)
	{
		p.x = p.x * GetPaintingWidth() / GetWindowWidth();
		p.y = p.y * GetPaintingHeight() / GetWindowHeight();
	}
	if (event == MouseDownEvent)
	{
		if (this->m_fDown != NULL)
		{
			this->m_fDown(mb, p);
		}
	}
	else if (event == MouseUpEvent)
	{
		if (this->m_fUp != NULL)
		{
			this->m_fUp(mb, p);
		}
	}
	else if (event == MouseWheelEvent)
	{
		if (this->m_fMw != NULL)
		{
			this->m_fMw(p, deltaMouse);
		}
	}
}

void BasePaint::RegisterKeyboardEvent(KeyboardEventFn f, KeyboardEvent event)
{
	if (event == KeyboardDownEvent)
	{
		this->m_keyfDown = f;
	}
	else if (event == KeyboardUpEvent)
	{
		this->m_keyfUp = f;
	}
}

void BasePaint::SendKeyboardPressEvent(int VK_KEY, KeyboardEvent event)
{
	if (event == KeyboardDownEvent)
	{
		if (this->m_keyfDown != NULL)
		{
			this->m_keyfDown(VK_KEY);
		}
	}
	else if (event == KeyboardUpEvent)
	{
		if (this->m_keyfUp != NULL)
		{
			this->m_keyfUp(VK_KEY);
		}
	}
}

void BasePaint::Paint()
{
	Render();
	Sleep(this->m_redrawinterval);
}


