#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Level* levelPointer, const Point2f& bulletPos,const Vector2f& direction, Sprite* sprite)
	:Moveable(levelPointer,sprite, Rectf(bulletPos.x, bulletPos.y, 70.f, 20.f), Rectf(0.f,0.f, 70.f, 20.f))
	,m_Damage(10)
{
	m_Speed.x = 450;
	m_Direction = direction;
	m_IsTrigger = true;
}

BlueBullet::BlueBullet(Level* levelPointer, const Point2f& bulletPos, const Vector2f& direction)
	:Bullet(levelPointer,bulletPos,direction, new Sprite("Resources/bullet.png", 1, 1))
{
	m_Damage = 10;
	m_Rect.width = 70;
	m_Rect.height = 20;

	
	m_OriginalHitbox.width = 70;		
	m_OriginalHitbox.height = 20;
}

