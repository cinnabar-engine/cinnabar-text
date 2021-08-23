#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/vec2.hpp>

#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>


namespace ce {
	struct Font {
		FT_Library library;
		FT_Face face;
		struct Character {
			char c;
			glm::ivec2 size, bearing;
			unsigned int advance;
			glm::vec2 scale;
			Material* material;
			Mesh* mesh;
			std::vector<glm::vec2> points;
		} characters[256] = {};
	};

	namespace assetManager {
		void getFont(std::string filename, ce::Font*& font);
		void closeFont(Font* font);
	}
}