#pragma once

#include <Windows.h>
#include <Shlwapi.h>
#include <string>
#include <random>
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
	MouseDownEvent,
	MouseUpEvent,
	MouseWheelEvent
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


using MouseWheelEventFn = auto(*) (Position p, int deltaWheel) -> void;
using MouseEventFn = auto(*) (MouseButton mb, Position p) -> void;
using Mouse = char;

class __declspec(dllexport) BasePaint
{
private:
	HWND m_hWnd;
	HDC m_hdc;
	RECT m_windowRect;

	MouseEventFn m_fDown;
	MouseEventFn m_fUp;
	MouseWheelEventFn m_fMw;

	int m_windowWidth;
	int m_windowHeight;

	int m_paintingWidth;
	int m_paintingHeight;


	DrawingMode m_eDraw;

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
	void RegisterMouseEvent(MouseWheelEventFn f, MouseEvent event);
	void SendMousePressEvent(MouseButton mb, MouseEvent event, Position p, int deltaMouse = 0);

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
	return this->m_windowWidth;
}

int BasePaint::GetWindowHeight() const
{
	return this->m_windowHeight;
}

int BasePaint::GetPaintingWidth() const
{
	return this->m_paintingWidth;
}

int BasePaint::GetPaintingHeight() const
{
	return this->m_paintingHeight;
}


inline RECT BasePaint::WindowRect()
{
	return this->m_windowRect;
}

inline HWND BasePaint::GetWindowHandle() const
{
	return this->m_hWnd;
}

inline HDC BasePaint::GetWindowDC() const
{
	return this->m_hdc;
}

inline void BasePaint::SetWindowHandle(const HWND hWnd)
{
	this->m_hWnd = hWnd;
	this->m_hdc = GetDC(hWnd);
	RecalculateWindowSizes();
}

inline void BasePaint::SetDrawingMode(DrawingMode mode)
{
	this->m_eDraw = mode;
}


inline int BasePaint::GetRedrawInterval() const
{
	return this->m_redrawinterval;
}

inline void BasePaint::SetRedrawInterval(const int interval)
{
	this->m_redrawinterval = interval;
}