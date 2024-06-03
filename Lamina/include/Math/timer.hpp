#ifndef LM_TIMER
#define LM_TIMER

#include <chrono>
#include <iostream>

#define LM_NANOSECONDS		0b00001
#define LM_MICROSECONDS		0b00010
#define LM_MILISECONDS		0b00100
#define LM_SECONDS			0b01000
#define LM_MINUTES			0b10000

namespace lm
{
	class Timer
	{
	public:
		Timer() : startTime(std::chrono::steady_clock::now()) {};

		void Restart()
		{
			startTime = std::chrono::steady_clock::now();
		}

		float GetTime(int type)
		{
			float time = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - startTime).count();
			switch (type)
			{
			case LM_NANOSECONDS:
				return time;
				break;
			case LM_MICROSECONDS:
				return time / 1000;
				break;
			case LM_MILISECONDS:
				return time / 1000000;
				break;
			case LM_SECONDS:
				return time / 1000000000;
				break;
			default:
				std::cout << "invalid parameters" << std::endl;
				return 0;
				break;
			}
		}
	private:
		std::chrono::time_point<std::chrono::steady_clock> startTime;
	};
}
#endif // !LM_TIMER