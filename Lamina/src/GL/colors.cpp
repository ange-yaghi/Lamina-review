#include "../Lamina/include/GL/colors.hpp"

lm::Color lm::Get8BitColor(lm::ColorF color)
{
	return Color{
		static_cast<uint8_t> (std::clamp(color.r, 0.f, 1.f) * 255),
		static_cast<uint8_t> (std::clamp(color.g, 0.f, 1.f) * 255),
		static_cast<uint8_t> (std::clamp(color.b, 0.f, 1.f) * 255),
		static_cast<uint8_t> (std::clamp(color.a, 0.f, 1.f) * 255) };
}

lm::ColorF lm::GetFloatColor(lm::Color color)
{
	return ColorF{
		(float)color.r / 255,
		(float)color.g / 255,
		(float)color.b / 255,
		(float)color.a / 255 };
}