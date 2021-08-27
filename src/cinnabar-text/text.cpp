#include <cinnabar-text/text.hpp>

#include <stdio.h>
#include <string.h>
#include <vector>

#include <cinnabar-core/tpnt_log.h>
#include <cinnabar-core/transform.hpp>
#include <cinnabar-render/assets.hpp>
#include <cinnabar-render/render_engine.hpp>

#include <cinnabar-text/font.hpp>

float
	font_resolution = 100.0f,
	modal_scale = 1.f / (20.f * font_resolution);

ce::Text::Text(std::string content, ce::Font* font)
	: m_font(font), m_cursor(0) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	setText(content);
}

void ce::Text::setText(std::string content) {
	auto content_len = content.length(); // TODO: get correct type
	m_content = content;
	LOG_INFO("Setting text (%d):%s", content_len, content.c_str());

	m_characters.clear();
	// TODO: set size of m_characters to content_len
	m_cursor = glm::vec2(0);
	for (auto letter : content) // TODO: write correct type
		pushChar(letter);
}

void ce::Text::render(ce::RenderEngine* renderEngine, ce::Transform* transform, ce::Camera* camera, ce::Material* material) {
	for (auto charInstance : m_characters) { // TODO: write correct type
		charInstance.transform->setParent(transform); // TODO: do this when creating the characters, check that the function saves the parent as a pointer with transform

		if (charInstance.character->mesh) {
			if (!material) {
				material
			}
			if (charInstance.character->texture) {
				
			}

			renderEngine->render(
				charInstance.character->mesh,
				material,
				charInstance.transform,
				camera);
		}
	}
}

void ce::Text::pushChar(char c) {
	ce::Transform* transform = new ce::Transform();
	ce::Font::Character* character = m_make_3d ? getCharacter3D(m_font, c) : getCharacter(m_font, c);
	if (!character)
		return;
	transform->setPosition(
		m_cursor.x + character->bearing.x * character->scale.x,
		m_cursor.y - (character->size.y - character->bearing.y) * character->scale.y,
		0.0f);

	m_characters.push_back({character, transform});

	m_cursor.x += (character->advance >> 6) * character->scale.x;
}
