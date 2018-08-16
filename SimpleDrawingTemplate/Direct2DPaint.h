#pragma once
#include "BasePaint.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "d2d1.lib")

class Direct2DPaint : public BasePaint
{
private:
	ID2D1Factory * m_pDirect2dFactory;
	ID2D1HwndRenderTarget * m_pRenderTarget;
	ID2D1SolidColorBrush * m_pBrush;

	template<class Interface>
	void SafeRelease(Interface ** ppInterfaceToRelease);

	// Initialize device-independent resources.
	HRESULT CreateDeviceIndependentResources();

	// Initialize device-dependent resources.
	HRESULT CreateDeviceResources();

	// Release device-dependent resources.
	void DiscardDeviceResource();

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


	void SetBrushColor(COLORREF color);
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
