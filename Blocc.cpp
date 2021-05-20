#include "pch.h"
#include "Blocc.h"
#include "CollisionObject.h"
#include "Bullet.h"

Blocc::Blocc(Rectf shape, Level* level)
	: CollisionObject(level, shape, Rectf{0,0,shape.width, shape.height})
{
	m_IsStatic = true;
}

void Blocc::Draw() const
{
	utils::SetColor(Color4f{ 0,0,1,1 });
	utils::FillRect(m_Rect);
}

RedBlocc::RedBlocc(Rectf shape,Level* level)
	:Blocc::Blocc(shape, level)
{
	
}

void RedBlocc::Draw() const
{
	utils::SetColor(Color4f{ 1,0,0,1 });
	utils::FillRect(m_Rect);
}

void Blocc::OnCollision(CollisionObject* collisionObject)
{
	if (dynamic_cast<Bullet*>(collisionObject))
	{
		collisionObject->SetIsReadyForRemoval(true);
	}
}
