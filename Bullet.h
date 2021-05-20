#pragma once
#include "Moveable.h"
#include "Sprite.h"
#include "DestroyableBlock.h"
#include "Blocc.h"

class Bullet : public Moveable
{
public:
	Bullet(Level* levelPointer, const Point2f& bulletPos,const Vector2f& direction, Sprite* sprite);

protected:
	int m_Damage;
	virtual void OnCollision(CollisionObject* collisionObject) { }
};

class BlueBullet : public Bullet
{
public:
	BlueBullet(Level* levelPointer, const Point2f& bulletPos, const Vector2f& direction);
};