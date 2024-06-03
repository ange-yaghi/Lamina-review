#ifndef LM_CONSTANTS
#define LM_CONSTANTS

#define PI			3.141592653589793238462643383279
#define TAU			6.283185307179586476925286766559

#define PI_FLOAT	(float)3.141592653589793238462643383279
#define TAU_FLOAT	(float)6.283185307179586476925286766559

namespace lm
{
	namespace constants
	{
		template<typename t_var>
		t_var RadToDeg(t_var angle)
		{
			return angle * (180 / (t_var)PI);
		}

		template<typename t_var>
		t_var DegToRad(t_var angle)
		{
			return angle * ((t_var)PI / 180);
		}
	}
}
#endif // !LM_CONSTANTS