#include <cinnabar-text/font.hpp>

#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-render/asset_manager.hpp>

FT_Library ce::Font::library;

ce::Font::Font(const char* path, unsigned int pixel_width, unsigned int pixel_height, bool do3d)
	: is3d(do3d) {
	if (FT_New_Face(ce::Font::library, path, 0, &this->face)) {
		LOG_ERROR("Error obtaining font face: %s", path);
	} else {
		LOG_SUCCESS("Successfully obtained font face: %s", path);
	}

	if (FT_Set_Pixel_Sizes(this->face, pixel_width, pixel_height)) {
		LOG_ERROR("Error setting font size.");
	} else {
		LOG_SUCCESS("Successfully set font size.");
	}

	generateCharacters(do3d);
}
ce::Font::~Font() {
	ce::assetManager::closeFont(this);
}


void ce::Font::generateCharacters(bool do3d) {
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
int ce::Text::bindChar(ce::Font* font, char c) {
	if (FT_Load_Char(font->face, c, FT_LOAD_RENDER)) {
		LOG_ERROR("Error loading character: %c", c);
		return 1;
	}
	LOG_SUCCESS("Successfully loaded character: %c", c);
	return 0;
}

ce::Texture* fontToTexture(FT_Face font_face) {
	GLenum type = GL_TEXTURE_2D;
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ce::Texture* texture = new ce::Texture(font_face->glyph->bitmap.buffer, font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows, GL_RED, type);

	return texture;

	//bind();
	//glGenTextures(1, &m_texture);


	//unbind();

	// if (this->loadData(font_face->glyph->bitmap.buffer, font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows, GL_RED)) {
	// 	LOG_SUCCESS("Loaded texture");
	// } else
	// 	LOG_ERROR("TEXTURE_LOADING_FAILED");
}

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
		{
			0,
			1,
			2,
			2,
			1,
			3,
		},
	};
}


ce::Font::Character* ce::Text::getCharacter(Font* font, char c) {
	ce::Font::Character* character = font->characters[c];
	if (character->c != c) {
		if (bindChar(font, c))
			return NULL;

		glm::ivec2 size(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
			bearing(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top);
		unsigned int advance = font->face->glyph->advance.x;
		ce::Texture* fontTexture = fontToTexture(font->face);
		ce::Material* material = new ce::Material("texture-tint");
		material->setTexture(fontTexture);

		glm::vec2 scale(modal_scale),
			dimensions(
				size.x * scale.x,
				size.y * scale.y);

		ce::Mesh* mesh = new ce::Mesh(createPlane(dimensions.x, dimensions.y, glm::vec2(0)));

		*character = {
			c,
			size,
			bearing,
			advance,
			scale,
			material,
			mesh};
	}
	return character;
}

ce::Font::Character* ce::Text::getCharacter3D(Font* font, char c) {
	ce::Font::Character* character = &font->characters[c];
	if (character->c != c) {
		if (bindChar(font, c))
			return NULL;

		glm::ivec2 size(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
			bearing(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top);
		unsigned int advance = font->face->glyph->advance.x;

		glm::vec2 scale(modal_scale),
			dimensions(
				size.x * scale.x,
				size.y * scale.y);


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
			} */
/*
		FT_Outline outline = font->face->glyph->outline;
		std::vector<glm::vec2> points;
		for (unsigned int i = 0; i < outline.n_points; i++) {
			FT_Vector p = outline.points[i];
			glm::vec2 point(p.x, p.y);
			points.push_back(point);
		}


		ce::Mesh* mesh = new ce::Mesh(createPlane(.01f, .01f, glm::vec2(0)));

		*character = {
			c,
			size,
			bearing,
			advance,
			scale,
			NULL,
			mesh,
			points};
	}
	return character;
}
*/