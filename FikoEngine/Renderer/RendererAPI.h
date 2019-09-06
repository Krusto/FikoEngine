#pragma once

namespace FikoEngine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,Vulkan = 2
		};
	public:
		virtual void Init() = 0;
		virtual void Clear() = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};

}