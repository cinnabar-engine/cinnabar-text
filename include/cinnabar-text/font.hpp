#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/vec2.hpp>

#include <cinnabar-render/material.hpp>
#include <cinnabar-render/mesh.hpp>


namespace ce {
	class Font {
	 public:
		Font(const char* path, unsigned int pixel_width, unsigned int pixel_height, bool do3d = false);
		Font(const char* path, unsigned int pixel_size, bool do3d = false) : Font(path, pixel_size, pixel_size, do3d){};
		~Font();

		static FT_Library library;
		FT_Face face;

		typedef struct {
			glm::ivec2 size; // TODO: what is this?
			glm::ivec2 bearing; // TODO: what is this?
			unsigned int advance; // TODO: what is this?
			glm::vec2 scale; // TODO: what is this?
			Mesh* mesh;
			Texture* texture; // TODO: should a transform be used to store
		} Character;
		Character characters[256];

		bool is3d;

	 private:
		void generateCharacters(bool do3d);
	};

	namespace assetManager {
		FT_Error initFreeType();
		FT_Error closeFreeType();
		FT_Error getFont(std::string filename, ce::Font& font);
		FT_Error closeFont(Font* font);
	}
}
