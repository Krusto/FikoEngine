#pragma once

#include "Definitions.h" // Isn't needed

namespace FikoEngine
{
	class Timestep
	{
	public:
		Timestep() = default;
		Timestep(float time);

	public:
		void setTime(float time);
		float ToMillis() const;
		float ToMicros() const;
		float Time() const;

	public:
		Timestep operator-(const Timestep& other);

	private:
		float m_Time{};
	};
}
