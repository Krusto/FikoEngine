//
// Created by Stoyanov, Krusto (K.S.) on 6/5/2022.
//

#include "Timestep.h"

namespace FikoEngine
{
	Timestep::Timestep(float time)
		: m_Time{ time }
	{}

	void Timestep::setTime(float time)
	{
		m_Time = time;
	}

	float Timestep::ToMillis() const
	{
		return m_Time * static_cast<float>(1000);
	}

	float Timestep::ToMicros() const
	{
		return m_Time * static_cast<float>(1000000);
	}

	float Timestep::Time() const
	{
		return m_Time;
	}

	Timestep Timestep::operator-(const Timestep& other)
	{
		return Timestep(m_Time - other.Time());
	}
}
