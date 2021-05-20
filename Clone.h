#pragma once
#include "Moveable.h"
#include "Delay.h"
#include "Sprite.h"
#include "Vector2f.h"

class  Clone : public Moveable
{
public:
	Clone(Level* level);
	~Clone();
	void Update(float elapsedSec);

	void RunToggle();


	enum class ActionState
	{
		idle,
		walking,
		running,
		shooting,
		isHit,
		dying,
		dead,
		melee
	};


	void Movement(float elapsedSec);

private:

	float m_HorSpeed;
	float m_VerSpeed;
	float m_HorSpeedShift;


	ActionState m_ActionState;
	bool m_ToggleRun;


	Rectf m_SmallHitbox;
	Delay m_ShiftDelay;
	std::vector<Sprite*> m_Sprites;

	void MakeSpriteVector();
	void UpdateCurrentState(float elapsedSec);

	Point2f m_BarrelPos;
	void Shoot();
	bool m_HasShot = false;
	Delay m_ShootDelay;

	virtual void OnCollision(CollisionObject* collisionObject) {};

};