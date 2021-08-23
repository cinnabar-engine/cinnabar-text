#include <cinnabar-text/font.hpp>

#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/asset_manager.hpp>

void ce::assetManager::getFont(std::string filename, ce::Font& font) {

	if (FT_Init_FreeType(&font.library)) {
		LOG_ERROR("Error initialising FreeType.");
	}
	LOG_SUCCESS("Successfully initialised FreeType.");

	if (FT_New_Face(font.library, filename.c_str(), 0, &font.face)) {
		LOG_ERROR("Error obtaining font face: %s", filename.c_str());
	}
	LOG_SUCCESS("Successfully obtained font face: %s", filename.c_str());
}


void ce::assetManager::closeFont(ce::Font* font) {
	FT_Done_Face(font->face);
	FT_Done_FreeType(font->library);
}