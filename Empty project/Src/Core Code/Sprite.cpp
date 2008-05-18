#include ".\sprite.h"

Sprite::Sprite(void)
{
}

Sprite::~Sprite(void)
{
}

Object *Sprite::CreateObject()
{
	return new Sprite;
}

ObjectType Sprite::GetObjectType() const
{
	return ObjectSprite;
}