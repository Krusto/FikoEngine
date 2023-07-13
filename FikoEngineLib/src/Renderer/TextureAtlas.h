#pragma once
#include <cstdint>
#include <Renderer/Texture.h>
#define N_TEXTURES_PER_ROW 8

namespace FikoEngine {
    class TextureAtlas {
    public:
        TextureAtlas(const std::string &texturePath, uint32_t texturesPerRow) {
            //texture = Texture::Create(texturePath);
            this->texturesPerRow = (float) texturesPerRow;
            //this->cellSize = texture->width() / texturesPerRow;
            unitSize = 1.0f / (float) texturesPerRow;
            pixelSize = 1.0f / (float) this->cellSize;

        }

        TextureAtlas(Ref<Texture> texture, uint32_t texturesPerRow) {
//        this->texture = texture;
            this->texturesPerRow = (float) texturesPerRow;
            this->cellSize = texture->width() / texturesPerRow;
            unitSize = 1.0f / (float) texturesPerRow;
            pixelSize = 1.0f / (float) this->cellSize;
        }

        void Destroy() {
            //this->texture->Destroy();
        }

        std::vector<glm::vec2> GetTextureCoords(const glm::ivec2 &location) const {
            float xMin = (location.x * unitSize);
            float yMin = (location.y * unitSize);

            float xMax = (xMin + unitSize);
            float yMax = (yMin + unitSize);

            return {
                    {xMax, yMax},
                    {xMin, yMax},
                    {xMin, yMin},
                    {xMax, yMin}
            };
        }

        std::vector<glm::vec2> GetTextureCoords(const unsigned int &location) const {
            int y = location / (int) texturesPerRow;
            int x = location % (int) texturesPerRow;
            float xMin = (x * unitSize);
            float yMin = (y * unitSize);

            float xMax = (xMin + unitSize);
            float yMax = (yMin + unitSize);

            return {
                    {xMax, yMax},
                    {xMin, yMax},
                    {xMin, yMin},
                    {xMax, yMin}
            };
        }

    protected:
        ///Ref<Texture> texture;
        uint32_t cellSize{};
        float texturesPerRow{};
        float unitSize{};
        float pixelSize{};
    };
}