//
// Created by Stoyanov, Krusto (K.S.) on 6/11/2022.
//
#include "File.h"
#include <fstream>
namespace FikoEngine{

    File::File(const char *path,FileFormat format){
        this->m_Path = path;
        this->m_FileFormat = format;
    }
    void File::Init(const char* path, FileFormat format){
        m_Path = path;
        m_FileFormat = format;
    }
    std::vector<u8> FikoEngine::File::ReadBinaryData() {
        if(!m_Opened){
            std::fstream file(m_Path,std::ios::in | std::ios::binary);
            if(file.good()) {
                m_Opened = true;
            }else{
                return {};
            }
            file.seekg(0, std::ios::end);
            size_t length = file.tellg();
            file.seekg(0, std::ios::beg);
            std::vector<u8> buffer(length);
            file.read((char*)buffer.data(), length);
            file.close();
            m_Opened = false;

            return buffer;
        }
        return {};
    }
    std::string FikoEngine::File::ReadTextData() {
        if(!m_Opened){
            std::fstream file(m_Path,std::ios::in);
            if(file.good()) {
                m_Opened = true;
            }else{
                return std::string();
            }
            file.seekg(0, std::ios::end);
            size_t length = file.tellg();
            file.seekg(0, std::ios::beg);
            std::string buffer;
            buffer.resize(length);
            file.read(&buffer[0], length);
            file.close();
            m_Opened = false;
            return buffer;
        }
        return std::string();
    }
}