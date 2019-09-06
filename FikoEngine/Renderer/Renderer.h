#pragma once

#include "RenderCommand.h"

namespace FikoEngine {

	class Renderer
	{
	public:
		static void Init();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};


}
