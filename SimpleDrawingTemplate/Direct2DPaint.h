#pragma once
#include "BasePaint.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <chrono>
#include <string>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Direct2DPaint : public BasePaint
{
private:
	IDWriteFactory * m_pWriteFactory;
	IDWriteTextFormat * m_pTextFormat;

	ID2D1Factory * m_pDirect2dFactory;
	ID2D1HwndRenderTarget * m_pRenderTarget;
	ID2D1SolidColorBrush * m_pBrush;
	
	// FPS stats
	std::chrono::time_point<std::chrono::steady_clock> start;
	bool m_showFPS;

	template<class Interface>
	void SafeRelease(Interface ** ppInterfaceToRelease);

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resources.
	void DiscardDeviceResource();

	void DrawFPSCounter();

public:
	Direct2DPaint(HWND hWnd);
	virtual ~Direct2DPaint();

	virtual void RecalculateWindowSizes();
	//virtual void Cleanup();
	virtual void Paint();
	virtual void SetupRenderer();

	/* Drawing Functions */

	virtual void Line(int startX, int startY, int endX, int endY, COLORREF color = 0);
	virtual void Pixel(int x, int y, COLORREF color = 0);
	virtual void SetBackground(COLORREF color = 0);
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen);
	virtual void Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen);
	virtual void Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush);

	virtual void Text(const char * const string, const Position & pos, COLORREF pen);


	void SetBrushColor(COLORREF color);
	
	inline void ShowFPSCounter(bool show);
};

template<class Interface>
inline void Direct2DPaint::SafeRelease(Interface ** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

inline void Direct2DPaint::ShowFPSCounter(bool show)
{
	this->m_showFPS = show;
}