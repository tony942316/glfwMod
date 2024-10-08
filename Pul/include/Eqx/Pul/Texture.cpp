export module Eqx.Pul.Texture;

import <Eqx/std.hpp>;

import <Eqx/TPL/glad/glad.hpp>;
import <Eqx/TPL/stb/stb_image.hpp>;

import <Eqx/Lib/Macros.hpp>;
import Eqx.Lib;

export namespace eqx
{
    class Texture
    {
    public:
        explicit inline Texture(std::string_view texPath) noexcept;

        explicit inline Texture(Texture&& other) noexcept;
        inline Texture& operator= (Texture&& other) noexcept;

        inline ~Texture() noexcept;

        Texture(const Texture&) = delete;
        Texture& operator= (const Texture&) = delete;

        inline void enable() const noexcept;
        inline void disable() const noexcept;

        static inline void enableSlot(unsigned int i) noexcept;

    private:
        unsigned int m_Tex;
    };
}

namespace eqx
{
    inline Texture::Texture(std::string_view texPath) noexcept
    {
        glGenTextures(1, &m_Tex);

        enable();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texPath.data(), &width, &height,
            &nrChannels, 0);
        eqx::ENSURE_HARD(data != nullptr,
            "Failed To Load Texture:"s + std::string{texPath});
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }

    inline Texture::Texture(Texture&& other) noexcept
        :
        m_Tex(std::move(other.m_Tex))
    {
        other.m_Tex = 0U;
    }

    inline Texture& Texture::operator= (Texture&& other) noexcept
    {
        std::swap(m_Tex, other.m_Tex);
        return *this;
    }

    inline Texture::~Texture() noexcept
    {
        if (m_Tex != 0)
        {
            glDeleteTextures(1, &m_Tex);
        }
    }

    inline void Texture::enable() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, m_Tex);
    }

    inline void Texture::disable() const noexcept
    {
        glBindTexture(GL_TEXTURE_2D, 0U);
    }

    inline void Texture::enableSlot(unsigned int i) noexcept
    {
        glActiveTexture(GL_TEXTURE0 + i);
    }

}
