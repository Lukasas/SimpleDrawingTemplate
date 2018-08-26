#include "Direct2DPaint.h"

HRESULT Direct2DPaint::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pWriteFactory), reinterpret_cast<IUnknown**>(&m_pWriteFactory));


	m_pWriteFactory->CreateTextFormat(L"Verdana", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 12, L"", &m_pTextFormat);
	return hr;
}

HRESULT Direct2DPaint::CreateDeviceResources()
{
	HRESULT hr = S_OK;
	D2D1_SIZE_U size = D2D1::SizeU(this->GetPaintingWidth(), this->GetPaintingHeight());

	if (m_pRenderTarget)
	{
		m_pRenderTarget->Release();
	}

	// Create a Direct2D render target.
	hr = m_pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(this->GetWindowHandle(), size),
		&m_pRenderTarget
	);


	m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

	if (m_pBrush)
	{
		SafeRelease(&m_pBrush);
	}

	// Error Check HR
	hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);


	return hr;
}

void Direct2DPaint::DiscardDeviceResource()
{
	SafeRelease(&m_pBrush);
	SafeRelease(&m_pDirect2dFactory);
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pWriteFactory);
	SafeRelease(&m_pTextFormat);
}

void Direct2DPaint::DrawFPSCounter()
{
	Text(L"FPS: ", Position(10, 10), 0xffffff);
	Text(std::to_wstring(1000000000.0 / (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count())).c_str(), Position(50, 10), 0xffffff);
	start = std::chrono::steady_clock::now();

}


Direct2DPaint::Direct2DPaint(HWND hWnd) :
	BasePaint(hWnd),
	m_pBrush(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pTextFormat(NULL),
	m_pWriteFactory(NULL),
	m_showFPS(false)
{
	CreateDeviceIndependentResources();
	CreateDeviceResources();
}

Direct2DPaint::~Direct2DPaint()
{
	DiscardDeviceResource();
}

void Direct2DPaint::RecalculateWindowSizes()
{
	BasePaint::RecalculateWindowSizes();

	if (m_pRenderTarget)
	{
		// This method can fail, but it's okay to ignore because the error will be returned again the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(this->GetPaintingWidth(), this->GetPaintingHeight()));
	}
}

void Direct2DPaint::Paint()
{
	HRESULT hr = S_OK;


	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();

		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

		BasePaint::Paint();

		if (m_showFPS)
			DrawFPSCounter();
		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResource();
	}
}

void Direct2DPaint::SetupRenderer()
{

}

void Direct2DPaint::Line(int startX, int startY, int endX, int endY, COLORREF color)
{
	SetBrushColor(color);
	m_pRenderTarget->DrawLine(D2D1::Point2F(startX, startY), D2D1::Point2F(endX, endY), m_pBrush);
}

void Direct2DPaint::Pixel(int x, int y, COLORREF color)
{
	SetBrushColor(color);
	m_pRenderTarget->FillRectangle(D2D1::RectF(x, y, x + 1, y + 1), m_pBrush);
}

void Direct2DPaint::SetBackground(COLORREF color)
{
	m_pRenderTarget->Clear(D2D1::ColorF(color));
}

void Direct2DPaint::Rectangle(int x, int y, int width, int height, COLORREF pen)
{
	SetBrushColor(pen);
	m_pRenderTarget->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), m_pBrush);
}

void Direct2DPaint::Rectangle(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	SetBrushColor(brush);
	m_pRenderTarget->FillRectangle(D2D1::RectF(x, y, x + width, y + height), m_pBrush);
	Rectangle(x, y, width, height, pen);
}

void Direct2DPaint::Ellipse(int x, int y, int width, int height, COLORREF pen)
{
	SetBrushColor(pen);
	m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x + width / 2.0f, y + height / 2.0f), width / 2.0f, height / 2.f), m_pBrush);
}

void Direct2DPaint::Ellipse(int x, int y, int width, int height, COLORREF pen, COLORREF brush)
{
	SetBrushColor(brush);
	m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x + width / 2.0f, y + height / 2.0f), width / 2.0f, height / 2.f), m_pBrush);
	Ellipse(x, y, width, height, pen);
}

void Direct2DPaint::Text(const std::wstring & text, const Position & pos, COLORREF pen)
{
	SetBrushColor(pen);
	m_pRenderTarget->DrawTextA(
		text.c_str(),
		text.length(),
		m_pTextFormat,
		D2D1::RectF(pos.x, pos.y, GetPaintingWidth(), GetPaintingHeight()),
		m_pBrush);
}

void Direct2DPaint::SetBrushColor(COLORREF color)
{
	m_pBrush->SetColor(D2D1::ColorF(color));
}
