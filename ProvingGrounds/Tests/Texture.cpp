export module Eqx.Pul.Tests.Texture;

import <Eqx/std.hpp>;

import Eqx.Lib;
import Eqx.Pul;

namespace tests::texture
{
    constinit auto m_Shader = std::optional<eqx::Shader>{};
    constinit auto m_Vertices = std::optional<eqx::VertexArray>{};
    constinit auto m_Texture = std::optional<eqx::Texture>{};

    export inline void run() noexcept;
    export inline void init() noexcept;
    export inline void term() noexcept;
}

namespace tests::texture
{
    inline void run() noexcept
    {
        eqx::renderer::draw(m_Shader.value(), m_Vertices.value(),
            m_Texture.value());
    }

    inline void init() noexcept
    {
        auto vertices = std::array<float, 20>{
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
        };

        auto indices = std::array<unsigned int, 6>{
            0, 1, 3,
            1, 2, 3
        };

        auto attr = std::array<unsigned int, 2>{3, 2};

        m_Vertices.emplace(attr);
        m_Vertices->addVertices(vertices);
        m_Vertices->addIndices(indices);

        m_Shader.emplace(eqx::Shader::parse(
            "Resources/Shaders/Texture/vs.glsl"sv,
            "Resources/Shaders/Texture/fs.glsl"sv));

        m_Shader->setInt("texture0"sv, 0);

        m_Texture.emplace("Resources/Textures/BrickWall.png"sv);
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Vertices.reset();
        m_Texture.reset();
    }
}
