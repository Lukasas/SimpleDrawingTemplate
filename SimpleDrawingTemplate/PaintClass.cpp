#include "PaintClass.h"
#include <math.h>
#define M_PI 3.14159265358979323846

float x, y;

float a;
float add;
bool over = true;
void PaintClass::Setup()
{
	a = 20;
	add = 0.4;
}

void PaintClass::Render()
{
	SetBackground(0);
	
	Rectangle(20, 20, 50, 50, 0x00FF00, 0xFF0000);
	// Draw Something Amazing !
	for (float t = 0; t < 2 * M_PI; t += add)
	{
		x = (a * sqrt(2) * cos(t)) / (pow(sin(t), 2) + 1);
		y = (a * sqrt(2) * cos(t) * sin(t)) / (pow(sin(t), 2) + 1.0f);

		x *= -10.0f;
		y *= 10.0f;

		x += GetWindowWidth() / 2;
		y += GetWindowHeight() / 2;
		Pixel(x, y, 0xffffff);
	}

	if (over)
		add -= 0.001;
	else
		add += 0.001;

	if (add < 0.01 || add > 0.4)
		over = !over;
}

PaintClass::~PaintClass()
{
}
