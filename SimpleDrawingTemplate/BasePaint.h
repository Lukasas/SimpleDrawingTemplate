#pragma once

#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

enum DrawingMode
{
	Fullscreen,
	Stretch
};

enum MouseButton
{
	RIGHT = 0x0204,
	MIDDLE = 0x0207,
	LEFT = 0x0201
};

enum MouseEvent
{
	MouseDown,
	MouseUp
};

struct Position
{
	size_t x;
	size_t y;
	Position() 
	{
		x = 0;
		y = 0;
	};
	Position(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Size
{
	size_t width;
	size_t height;
	Size()
	{
		width = 0;
		height = 0;
	}

	Size(size_t width, size_t height)
	{
		this->width = width;
		this->height = height;
	}
};

typedef void(*MouseEventFn)(MouseButton mb, Position p) ;

typedef char Mouse;

class BasePaint
{
private:
	HWND hWnd;
	HDC hdc;
	HBITMAP hbmp;
	HBITMAP oldhbmp;
	RECT windowRect;

	MouseEventFn fDown;
	MouseEventFn fUp;

	int width;
	int height;

	int paintingWidth;
	int paintingHeight;


	DrawingMode eDraw;
protected:
	HDC hdcmem;
public:

	BasePaint(HWND hWnd);

	inline int WindowWidth() const;
	inline int WindowHeight() const;

	inline int PaintingWidth() const;
	inline int PaintingHeight() const;

	inline void RecalculateWindowSizes();

	inline RECT WindowRect();
	void ResizePainting(const int width, const int height);
	virtual void CreateDrawingContent(const int width, const int height);
	inline void SetWindowHandle(HWND hWnd);

	void Cleanup();
	virtual ~BasePaint();

	virtual void Setup() = 0;
	virtual void Render() = 0;

	inline void SetDrawingMode(DrawingMode mode);


	void RegisterMouseEvent(MouseEventFn f, MouseEvent event);

	void SendMousePressEvent(MouseButton mb, MouseEvent event, Position p);

	virtual void Paint();

	/* Drawing Functions */

	virtual void Line(int startX, int startY, int endX, int endY, COLORREF color = 0) = 0;
	virtual void Pixel(int x, int y, COLORREF color = 0) = 0;
	virtual void SetBackground(COLORREF color = 0) = 0;
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen) = 0;
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush) = 0;
	
	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen) = 0;
	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush) = 0;

};

int BasePaint::WindowWidth() const 
{
	return this->width;
}

int BasePaint::WindowHeight() const
{
	return this->height;
}

int BasePaint::PaintingWidth() const
{
	return this->paintingWidth;
}

int BasePaint::PaintingHeight() const
{
	return this->paintingHeight;
}

inline void BasePaint::RecalculateWindowSizes()
{
	GetClientRect(this->hWnd, &this->windowRect);
	this->width = this->windowRect.right - this->windowRect.left;
	this->height = this->windowRect.bottom - this->windowRect.top;

	if (this->eDraw == Fullscreen)
	{
		this->ResizePainting(this->width, this->height);
	}
}

inline RECT BasePaint::WindowRect()
{
	return this->windowRect;
}

inline void BasePaint::SetWindowHandle(const HWND hWnd )
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	RecalculateWindowSizes();
	CreateDrawingContent(this->width, this->height);
}

inline void BasePaint::SetDrawingMode(DrawingMode mode)
{
	this->eDraw = mode;
}
