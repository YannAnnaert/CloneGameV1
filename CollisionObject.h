#pragma once
#include "Object.h"

class CollisionObject :public Object
{
public:

	CollisionObject(Level* level, const Rectf& destRect, const Rectf& hitbox);
	void Update(float elapsedSec) override;

	

	Rectf GetShape() const { return m_Rect; }
	Rectf GetHitbox() const { return m_Hitbox; }
	bool GetIsTrigger() const { return m_IsTrigger; }
	bool GetIsStatic() const { return m_IsStatic; }

protected:
	virtual void OnCollision(CollisionObject* collisionObject) = 0;
	
	Rectf m_Rect;
	Rectf m_OriginalHitbox;
	Rectf m_Hitbox;
	
	bool m_IsStatic;
	bool m_IsTrigger;
};
