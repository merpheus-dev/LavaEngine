#include "Mathematics.h"

bool Lava::Mathematics::m_timeSet = false;
int Lava::Mathematics::GetRandom()
{
	if (!m_timeSet) {
		srand(time(0));
		m_timeSet = true;
	}
	return rand() % 100;
}
