#pragma once

//										RED		GRN		BLU		ALPHA
#define LM_COLOR_RED		lm::Color{	255,	0,		0,		255}
#define LM_COLOR_GREEN		lm::Color{	0,		255,	0,		255}
#define LM_COLOR_BLUE		lm::Color{	0,		0,		255,	255}
#define LM_COLOR_ORANGE		lm::Color{	255,	255,	0,		255}
#define LM_COLOR_PURPLE		lm::Color{	255,	0,		255,	255}
#define LM_COLOR_CYAN		lm::Color{	0,		255,	255,	255}
#define LM_COLOR_WHITE		lm::Color{	255,	255,	255,	255}
#define LM_COLOR_GRAY		lm::Color{	100,	100,	100,	255}
#define LM_COLOR_BLACK		lm::Color{	0,		0,		0,		255}

#include <stdint.h>
#include <algorithm>

namespace lm
{
	struct ColorF
	{
		float r, g, b, a;
	};

	struct Color
	{
		uint8_t r, g, b, a;
	};

	ColorF GetFloatColor(Color color);
	Color Get8BitColor(ColorF color);
}
