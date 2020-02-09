#pragma once
#include <time.h>
#include <iostream>
namespace Lava {
	class Mathematics {
	public:
		static int GetRandom();
	private:
		static bool m_timeSet;
	};
}