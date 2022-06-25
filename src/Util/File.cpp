//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include "File.h"
#include <fstream>
namespace FikoEngine{

    File::File(std::string_view path, FileFormat format)
        : m_Path{ path }
        , m_FileFormat{ format }
    {}

    std::vector<u8> File::ReadBinaryData() 
    {
        if(!m_IsOpened)
        {
            std::fstream file(m_Path, std::ios::in | std::ios::binary);
            file.good() ? m_IsOpened = true : return {};
            
            file.seekg(0, std::ios::end);
            const std::size_t length = file.tellg();
            file.seekg(0, std::ios::beg);
            
            std::vector<u8> buffer(length);
            file.read(static_cast<char*>(buffer.data()), length); // Doesn't need to be casted because the underlying type 
            //of the vector is an std::uint8_t*, esentially the same as the type we are trying to cast to. Redundant
            file.close();
            
            m_IsOpened = false;
            return buffer;
        }
        return {};
    }
    
    std::vector<u8> File::ReadTextData() 
    {
        if(!m_IsOpened)
        {
            std::fstream file(m_Path, std::ios::in);
            file.good() ? m_IsOpened = true : return {};
            
            file.seekg(0, std::ios::end);
            const std::size_t length = file.tellg();
            file.seekg(0, std::ios::beg);
            
            std::vector<u8> buffer(length);
            file.read(buffer.data(), length);
            file.close();
            
            m_IsOpened = false;

            return buffer;
        }
        return {};
    }
}
