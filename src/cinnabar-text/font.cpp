#include <cinnabar-text/font.hpp>

#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/asset_manager.hpp>

std::map<std::string, ce::Font> font_cache;

ce::Font* ce::assetManager::getFont(std::string filename) {
	if (!font_cache.count(filename)) { // if the font is not cached
		font_cache[filename] = {};
	}
	ce::Font* font = &font_cache[filename];

	if (FT_Init_FreeType(&font->library)) {
		LOG_ERROR("Error initialising FreeType.");
	}
	LOG_SUCCESS("Successfully initialised FreeType.");

	if (FT_New_Face(font->library, filename.c_str(), 0, &font->face)) {
		LOG_ERROR("Error obtaining font face: %s", filename.c_str());
	}
	LOG_SUCCESS("Successfully obtained font face: %s", filename.c_str());

	return font;
}


void ce::assetManager::closeFont(ce::Font* font) {
	FT_Done_Face(font->face);
	FT_Done_FreeType(font->library);
}