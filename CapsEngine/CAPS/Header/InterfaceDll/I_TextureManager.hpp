#ifndef __CAPS_INTERFACE_TEXTURE_MANAGER__
#define __CAPS_INTERFACE_TEXTURE_MANAGER__

#include "Texture.hpp"

class I_TextureManager
{
public:
	virtual Texture * CreateTexture(const char * path) = 0;
	virtual void DestroyTexture(Texture * texture) = 0;
	virtual Texture * getNullTextures() = 0;
};

#endif //!__CAPS_INTERFACE_TEXTURE_MANAGER__