#pragma once

#include <cinnabar-core/transform.hpp>

#include <cinnabar-render/camera.hpp>
#include <cinnabar-render/material.hpp>
#include <cinnabar-render/render_engine.hpp>

#include <cinnabar-text/font.hpp>

namespace ce {
	class Text {
		typedef struct {
			ce::Font::Character* character;
			ce::Transform* transform; // only position is used but using the transform class allows parenting
		} CharacterInstance;

	 public:
		// no overload is given for a Font path because it would be impossible to delete the Font
		Text(std::string content, ce::Font* font);

		void setText(std::string content);

		void render(RenderEngine* renderEngine, Transform* transform, ce::Camera* camera, ce::Material* material);

	 private:
		std::string m_content;
		glm::vec2 m_cursor;
		ce::Font* m_font;
		std::vector<CharacterInstance> m_characters;

		void pushChar(char c);

		static int bindChar(ce::Font* font, char c);
		static ce::Font::Character* getCharacter(ce::Font* font, char c);
	};
}
