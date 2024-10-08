export module Eqx.Pul.Tests.TxQuad;

import <Eqx/std.hpp>;

import <Eqx/TPL/glm/glm.hpp>;

import Eqx.Lib;
import Eqx.Pul;

namespace tests::txquad
{
    constinit auto m_Shader = std::optional<eqx::Shader>{};
    constinit auto m_Texture = std::optional<eqx::Texture>{};
    constinit auto m_TxQuad = eqx::TxQuad{};

    export inline void run() noexcept;
    export inline void init(const eqx::Window& window) noexcept;
    export inline void term() noexcept;
}

namespace tests::txquad
{
    inline void run() noexcept
    {
        eqx::renderer::draw(m_Shader.value(), m_TxQuad);
        m_TxQuad.setPos(eqx::mouse::getPosition());
    }

    inline void init(const eqx::Window& window) noexcept
    {
        m_Texture.emplace("Resources/Textures/BrickWall.png"sv);

        m_Shader.emplace(eqx::Shader::parse(
            "Resources/Shaders/TxQuad/vs.glsl"sv,
            "Resources/Shaders/TxQuad/fs.glsl"sv));

        auto proj = glm::ortho(
            0.0f, static_cast<float>(window.getWidth()),
            -1.0f * static_cast<float>(window.getHeight()), 0.0f,
            0.0f, 1000.0f);

        m_Shader->setMat4("u_Projection", proj);

        m_TxQuad.setRect(eqx::Rectangle<float>{0.0f, 0.0f, 50.0f, 50.0f});
        m_TxQuad.setZ(10.0f);
        m_TxQuad.setTexture(*m_Texture);
    }

    inline void term() noexcept
    {
        m_Shader.reset();
        m_Texture.reset();
    }
}
