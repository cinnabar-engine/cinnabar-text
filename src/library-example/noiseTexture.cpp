#include <library-example/noise_texture.hpp>

#include <cstdlib>
#include <stdexcept>

#include <cinnabar-render/assets.hpp>

namespace ceNt {
	ce::TextureFile generateNoiseTexture(int width, int height, int channelCount) {
		// TODO: output the actual channelcount given when cinnabar supports other texture formats
		size_t textureSize = width * height * 4;
		unsigned char* textureData = (unsigned char*)malloc(textureSize);

		if (channelCount <= 0 || channelCount > 4)
			throw std::invalid_argument("Invalid channel count");

		for (size_t i = 0; i < textureSize; i++) {
			if (i % 4 >= channelCount) {
				if (i % 4 == 3)
					textureData[i] = 255;
				else
					textureData[i] = 0;
			} else
				textureData[i] = (char)rand();
		}

		return (ce::TextureFile){textureData, width, height, 4};
	}
}
