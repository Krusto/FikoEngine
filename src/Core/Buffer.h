#pragma once
#include <cstdint>
#include <memory>
#include <cassert>
#include <cstring>

using byte = uint8_t;
struct Buffer
{
	void* Data;
	u32 Size;

	Buffer()
		: Data(nullptr), Size(0)
	{
	}

	Buffer(void* data, u32 size)
		: Data(data), Size(size)
	{
	}

	static Buffer Copy(const void* data, u32 size)
	{
		Buffer buffer;
		buffer.Allocate(size);
		memcpy(buffer.Data, data, size);
		return buffer;
	}

	void Allocate(u32 size)
	{
		delete[] Data;
		Data = nullptr;

		if (size == 0)
			return;

		Data = new byte[size];
		Size = size;
	}

	void Release()
	{
		delete[] Data;
		Data = nullptr;
		Size = 0;
	}

	void ZeroInitialize()
	{
		if (Data)
			memset(Data, 0, Size);
	}

	template<typename T>
	T& Read(u32 offset = 0)
	{
		return *(T*)((byte*)Data + offset);
	}

	byte* ReadBytes(u32 size, u32 offset)
	{
		assert(offset + size <= Size);
		byte* buffer = new byte[size];
		memcpy(buffer, (byte*)Data + offset, size);
		return buffer;
	}

	void Write(void* data, u32 size, u32 offset = 0)
	{
		assert(offset + size <= Size);
		memcpy((byte*)Data + offset, data, size);
	}

	operator bool() const
	{
		return Data;
	}

	byte& operator[](int index)
	{
		return ((byte*)Data)[index];
	}

	byte operator[](int index) const
	{
		return ((byte*)Data)[index];
	}

	template<typename T>
	T* As()
	{
		return (T*)Data;
	}

	inline u32 GetSize() const { return Size; }
};