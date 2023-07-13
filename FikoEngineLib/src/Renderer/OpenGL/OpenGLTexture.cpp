#include <glad/glad.h>

#include "OpenGLTexture.h"
#include <filesystem>
#include <iostream>
namespace FikoEngine {

    void OpenGLTexture::Load(std::string_view Path) {

        if (!std::filesystem::exists(Path))
            std::cout << (std::string(Path) + " does not exist!");

        m_Name = std::filesystem::path(Path).filename().string();

        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = nullptr;
        {
            data = stbi_load(Path.data(), &m_width, &m_height, &m_channels, 0);
        }

        m_State = TextureState::Loaded;
        GLenum internalFormat = 0, dataFormat = 0;
        if (m_channels == 4) {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
        } else if (m_channels == 3) {
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
        } else if (m_channels == 2) {
            internalFormat = GL_RG;
            dataFormat = GL_RG;
        } else if (m_channels == 1) {
            internalFormat = GL_RED;
            dataFormat = GL_RED;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::Load(char *data, uint32_t channels, uint32_t width, uint32_t height) {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        m_State = TextureState::Loaded;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4) {
            internalFormat = GL_RGBA;
            dataFormat = GL_RGBA;
        } else if (channels == 3) {
            internalFormat = GL_RGB;
            dataFormat = GL_RGB;
        } else if (channels == 1) {
            internalFormat = GL_ALPHA;
            dataFormat = GL_ALPHA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture::Bind(uint32_t slot) const {
        if (m_State == TextureState::Loaded) {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, m_id);
        }
    }

    void OpenGLTexture::Destroy() {
        m_State = TextureState::Unloaded;
        glDeleteTextures(1, &m_id);
    }

    OpenGLSkyboxTexture::OpenGLSkyboxTexture(std::string_view Path) {
        std::vector<std::string> faces(6);
        faces[0] = std::string(Path) + "left.png";
        faces[1] = std::string(Path) + "right.png";
        faces[2] = std::string(Path) + "top.png";
        faces[3] = std::string(Path) + "bottom.png";
        faces[4] = std::string(Path) + "front.png";
        faces[5] = std::string(Path) + "back.png";
        this->Load(faces);
    }

    void OpenGLSkyboxTexture::Load(std::vector<std::string> Path) {
        for (auto &path: Path) {
            if (!std::filesystem::exists(path))
                std::cout << (std::string(path) + " does not exist!");
        }

        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        for (uint32_t i = 0; i < Path.size(); ++i) {

            stbi_uc *data = nullptr;
            {
                data = stbi_load(Path[i].c_str(), &width, &height, &channels, 0);
            }

            GLenum internalFormat = 0, dataFormat = 0;
            if (channels == 4) {
                internalFormat = GL_RGBA;
                dataFormat = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB;
                dataFormat = GL_RGB;
            }
            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE,
                             data);
            } else {
                LOG_ERROR("Failed to load cubemap texture!");
            }
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void OpenGLSkyboxTexture::Bind() const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
    }

    void OpenGLSkyboxTexture::Destroy() {
        glDeleteTextures(1, &this->id);
    }
}