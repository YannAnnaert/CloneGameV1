#pragma once
#include "CollisionObject.h"
#include "Sprite.h"

class Moveable : public CollisionObject
{
public:
	Moveable(Level* level, Sprite* sprite,const Rectf& destRect,const Rectf& hitbox);
	~Moveable();
	void Draw() const override;
	void Update(float elapsedSec) override;
	
	
	enum class Orientation
	{
		left,
		right
	};


protected:
	
	Vector2f m_Speed;
	Sprite* m_Sprite;
	Vector2f m_Direction;
	Orientation m_CurentOrientation;
};
