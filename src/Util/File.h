//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include <vector>
#include <string>
#include "../Core/Definitions.h"

namespace FikoEngine
{
    enum class FileFormat { Regular, Binary };

    class File
    {
    public:
        File() = default;
        File(std::string_view path, FileFormat format);

    public:
        std::vector<u8> ReadBinaryData();
        std::vector<u8> ReadTextData();

    private:
        bool m_IsOpened{};
        FileFormat m_FileFormat{};
        std::string_view m_Path;
    };
}
