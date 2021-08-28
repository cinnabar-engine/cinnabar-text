#include <cinnabar-text/font.hpp>

#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/asset_manager.hpp>

FT_Library ce::Font::library;

float
	font_resolution = 100.0f,
	modal_scale = 1.f / (20.f * font_resolution);

ce::MeshFile createPlane(float width, float height, glm::vec2 origin) {
	float left = -width * origin.x,
			right = width + left,
			up = -height * origin.y,
			down = height + up;
	return {
		{

			{glm::vec3(left, up, 0), glm::vec3(0, 1.f, 0), glm::vec2(0, 1.f)},
			{glm::vec3(right, up, 0), glm::vec3(0, 1.f, 0), glm::vec2(1.f, 1.f)},
			{glm::vec3(left, down, 0), glm::vec3(0, 1.f, 0), glm::vec2(0, 0)},
			{glm::vec3(right, down, 0), glm::vec3(0, 1.f, 0), glm::vec2(1.f, 0)},
		},
		{0, 1, 2, 2, 1, 3},
	};
}


ce::Font::Font(const char* path, glm::ivec2 pixel_size, bool do3d) {
	if (FT_New_Face(ce::Font::library, path, 0, &this->face)) {
		LOG_ERROR("Error obtaining font face: %s", path);
	} else {
		LOG_SUCCESS("Successfully obtained font face: %s", path);
	}

	if (FT_Set_Pixel_Sizes(this->face, pixel_size.x, pixel_size.y)) {
		LOG_ERROR("Error setting font size.");
	} else {
		LOG_SUCCESS("Successfully set font size.");
	}

	cacheCharacters(do3d);
}
ce::Font::~Font() {
	ce::assetManager::closeFont(this);
}


void ce::Font::cacheCharacters(bool do3d) {
	for (unsigned char c = 1; c < 128; c++)
		cacheCharacter(c, do3d);
}
void ce::Font::cacheCharacter(char c, bool do3d) {
	if (loadCharacter(c))
		return;

	glm::ivec2 size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	characters[c].size = size;
	characters[c].bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	characters[c].advance = face->glyph->advance.x;
	characters[c].texture = fontToTexture();

	glm::vec2 scale(modal_scale),
		dimensions(
			size.x * scale.x,
			size.y * scale.y);

	characters[c].mesh = new ce::Mesh(createPlane(dimensions.x, dimensions.y, glm::vec2(0)));
}
int ce::Font::loadCharacter(char c) {
	if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
		LOG_ERROR("Error loading character: %c", c);
		return 1;
	} else {
		LOG_SUCCESS("Successfully loaded character: %c", c);
		return 0;
	}
}
ce::Texture* ce::Font::fontToTexture() {
	GLenum type = GL_TEXTURE_2D;
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ce::Texture* texture = new ce::Texture(face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, type);

	return texture;
}


FT_Error ce::assetManager::initFreeType() {
	auto err = FT_Init_FreeType(&ce::Font::library);
	if (err) {
		LOG_ERROR("Error initialising FreeType.");
	} else {
		LOG_SUCCESS("Successfully initialised FreeType.");
	}
	return err;
}
FT_Error ce::assetManager::closeFreeType() {
	return FT_Done_FreeType(ce::Font::library);
}

FT_Error ce::assetManager::getFont(std::string filename, ce::Font& font) {
	auto err = FT_New_Face(ce::Font::library, filename.c_str(), 0, &font.face);
	if (err) {
		LOG_ERROR("Error obtaining font face: %s", filename.c_str());
	} else {
		LOG_SUCCESS("Successfully obtained font face: %s", filename.c_str());
	}
	return err;
}
FT_Error ce::assetManager::closeFont(ce::Font* font) {
	return FT_Done_Face(font->face);
}

/*
void ce::Font::createCharacter3D(char c) {
	//Create mesh of character

	/*
			typedef struct  FT_Outline_
			{
				short       n_contours;       number of contours in glyph        
				short       n_points;         number of points in the glyph      
				FT_Vector*  points;           the outline's points               
				char*       tags;             the points flags                   
				short*      contours;         the contour end points             
				int         flags;            outline masks                      
			} *//*

	std::vector<glm::vec2> points;
	for (FT_Vector p : font->face->glyph->outline.points) {
		glm::vec2 point(p.x, p.y);
		points.push_back(point);
	}


	ce::Mesh* mesh = new ce::Mesh(createPlane(.01f, .01f, glm::vec2(0)));
}
*/