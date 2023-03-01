﻿#pragma once
#include <glad/glad.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <string>
#include <Windows.h>
#include <filesystem>

class FileDialogs {
public:
	static std::filesystem::path OpenFolder(GLFWwindow* window);
	static std::filesystem::path OpenFile(GLFWwindow* window,const char* filter);
	static std::string SaveFile(const char* filter);
};