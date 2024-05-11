#pragma once

#include "../Lamina/include/misc_graphics/text.hpp"
#include "../Lamina/include/GL/opengl.hpp"
#include "../Lamina/include/Math/vector.hpp"
#include <iostream>
#include <string>

namespace lm
{
	//namespace priv {
	//	enum class GlyphType
	//	{
	//		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	//		a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u ,v, w, x, y, z,
	//		N0, N1, N2, N3, N4, N5, N6, N7, N8, N9
	//	};
	//	class Glyph
	//	{
	//		Glyph() : glyphData(nullptr) {};


	//		unsigned char* glyphData;
	//	};
	//}

	class Text
	{
	public:
		Text() : fontSize(10) {};
		Text(lm::vec2f _position) : fontSize(10), position(_position) {};

		void SetString(std::string string) { text = string; }
		void SetFont(float _fontSize) { fontSize = _fontSize; }
		void SetPosition(lm::vec2f _position) { position = _position; }
	private:
		lm::vec2f position;
		float fontSize;
		std::string text;
	};
}