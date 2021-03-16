#ifndef __CAPS_INTERFACE_MATERIAL__
#define __CAPS_INTERFACE_MATERIAL__

#include "Texture.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Component.hpp"

class Material : public Component
{
public:
	virtual void SetColor(Vector3 color) = 0;
	virtual void SetMetallic(float metal) = 0;
	virtual void SetNormal(float normal) = 0;
	virtual void SetOclusion(float ao) = 0;
	virtual void SetAlbedoTexture(Texture * albedo) = 0;
	virtual void SetNormalTexture(Texture * normal) = 0;
	virtual void SetMetallicTexture(Texture * metal) = 0;
	virtual void SetOclusionTexture(Texture * oclu) = 0;
	virtual Vector3 GetColor() = 0;
	virtual float GetMetallic() = 0;
	virtual float GetNormal() = 0;
	virtual float GetOclusion() = 0;
	virtual Texture * GetAlbedoTexture() = 0;
	virtual Texture * GetNormalTexture() = 0;
	virtual Texture * GetMetallicTexture() = 0;
	virtual Texture * GetOclusionTexture() = 0;
	virtual int GetIndex() = 0;
	virtual bool GetLightActive() = 0;
	virtual void SetLightActive(bool state) = 0;
	virtual void SetHDR(float hdr) = 0;
	virtual void SetHDRTexture(Texture * hdr) = 0;
	virtual float GetHDR() = 0;
	virtual Texture * GetHDRTexture() = 0;
	virtual Vector2 GetOffset() = 0;
	virtual void SetOffset(Vector2 off) = 0;
};

#endif // !__CAPS_INTERFACE_MATERIAL__
