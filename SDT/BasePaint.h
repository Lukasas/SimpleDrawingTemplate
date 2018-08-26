#pragma once

#include <Windows.h>
#include <Shlwapi.h>
#include <string>
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
	size_t x = 0;
	size_t y = 0;

	Position(size_t x, size_t y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Size
{
	size_t width = 0;
	size_t height = 0;
	Size(size_t width, size_t height)
	{
		this->width = width;
		this->height = height;
	}
};


using MouseEventFn = auto(*) (MouseButton mb, Position p) -> void;
using Mouse = char;

class __declspec(dllexport) BasePaint
{
private:
	HWND hWnd;
	HDC hdc;
	RECT windowRect;

	MouseEventFn fDown;
	MouseEventFn fUp;

	int width;
	int height;

	int paintingWidth;
	int paintingHeight;


	DrawingMode eDraw;

	int m_redrawinterval;
protected:
public:

	BasePaint(HWND hWnd);

	inline int GetWindowWidth() const;
	inline int GetWindowHeight() const;

	inline int GetPaintingWidth() const;
	inline int GetPaintingHeight() const;


	inline RECT WindowRect();
	void ResizePainting(const int width, const int height);
	inline HWND GetWindowHandle() const;
	inline void SetWindowHandle(HWND hWnd);

	inline HDC GetWindowDC() const;

	virtual void Cleanup();
	virtual void RecalculateWindowSizes();
	virtual ~BasePaint();

	virtual void SetupRenderer() = 0;
	virtual void Setup() = 0;
	virtual void Render() = 0;


	inline void SetDrawingMode(DrawingMode mode);


	void RegisterMouseEvent(MouseEventFn f, MouseEvent event);

	void SendMousePressEvent(MouseButton mb, MouseEvent event, Position p);

	virtual void Paint();

	inline int GetRedrawInterval() const;
	inline void SetRedrawInterval(const int interval);
	/* Drawing Functions */

	virtual void Line(int startX, int startY, int endX, int endY, COLORREF color = 0) = 0;
	virtual void Pixel(int x, int y, COLORREF color = 0) = 0;
	virtual void SetBackground(COLORREF color = 0) = 0;
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen) = 0;
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush) = 0;

	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen) = 0;
	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush) = 0;

	virtual void Text(const std::wstring & text, const Position & pos, COLORREF pen) = 0;
};

int BasePaint::GetWindowWidth() const
{
	return this->width;
}

int BasePaint::GetWindowHeight() const
{
	return this->height;
}

int BasePaint::GetPaintingWidth() const
{
	return this->paintingWidth;
}

int BasePaint::GetPaintingHeight() const
{
	return this->paintingHeight;
}


inline RECT BasePaint::WindowRect()
{
	return this->windowRect;
}

inline HWND BasePaint::GetWindowHandle() const
{
	return this->hWnd;
}

inline HDC BasePaint::GetWindowDC() const
{
	return this->hdc;
}

inline void BasePaint::SetWindowHandle(const HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	RecalculateWindowSizes();
}

inline void BasePaint::SetDrawingMode(DrawingMode mode)
{
	this->eDraw = mode;
}


inline int BasePaint::GetRedrawInterval() const
{
	return this->m_redrawinterval;
}

inline void BasePaint::SetRedrawInterval(const int interval)
{
	this->m_redrawinterval = interval;
}