#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/vec2.hpp>

#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>


namespace ce {
	class Font {
	 public:
		Font(const char* path, glm::ivec2 pixel_size, bool do3d = false);
		Font(const char* path, unsigned int pixel_size, bool do3d = false) : Font(path, glm::ivec2(pixel_size), do3d){};
		~Font();

		static FT_Library library;
		FT_Face face;

		typedef struct {
			glm::ivec2 size; // TODO: what is this?
			glm::ivec2 bearing; // TODO: what is this?
			unsigned int advance; // TODO: what is this?
			glm::vec2 scale; // TODO: what is this?
			Mesh* mesh;
			Texture* texture;
		} Character;
		Character characters[256];

	 private:
		void cacheCharacters(bool do3d);
		void cacheCharacter(char c, bool do3d);
		int loadCharacter(char c);
		ce::Texture* fontToTexture();
	};

	namespace assetManager {
		FT_Error initFreeType();
		FT_Error closeFreeType();
		FT_Error getFont(std::string filename, ce::Font& font);
		FT_Error closeFont(Font* font);
	}
}
