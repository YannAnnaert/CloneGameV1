#include "pch.h"
#include "Moveable.h"

Moveable::Moveable(Level* level, Sprite* sprite,const Rectf& destRect,const Rectf& hitbox)
	:CollisionObject(level, destRect, hitbox)
	,m_Speed()
	,m_Sprite(sprite)
	,m_Direction()
	,m_CurentOrientation(Orientation::right)
{
	
}

Moveable::~Moveable()
{
	if(m_Sprite)
	{
		delete m_Sprite;
	}
}

void Moveable::Draw() const
{
	if(m_Sprite)
	{
		if (m_CurentOrientation == Orientation::left)
		{
			glPushMatrix();
			glTranslatef(m_Rect.width + 2 * m_Rect.left, 0.f, 0.f);
			glScalef(-1, 1, 1);
			m_Sprite->Draw(m_Rect);
			glPopMatrix();
		}
		else
		{
			m_Sprite->Draw(m_Rect);
		}
	}

}

void Moveable::Update(float elapsedSec)
{
	CollisionObject::Update(elapsedSec);

	if(!m_IsStatic)
	{
		m_Rect.left += m_Speed.x * elapsedSec * m_Direction.x;
		m_Rect.bottom += m_Speed.y * elapsedSec * m_Direction.y;

		if (m_Direction.x > 0)
		{
			m_CurentOrientation = Orientation::right;
		}
		if (m_Direction.x < 0)
		{
			m_CurentOrientation = Orientation::left;
		}
	}
}

