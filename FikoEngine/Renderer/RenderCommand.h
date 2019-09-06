#pragma once

#include "RendererAPI.h"

namespace FikoEngine {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

	private:
		static RendererAPI* s_RendererAPI;
	};

}
