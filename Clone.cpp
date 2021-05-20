#include "pch.h"
#include "Clone.h"
#include "Level.h"
#include "Camera2D.h"
#include "Bullet.h"

Clone::Clone(Level* level)
	:Moveable(level, nullptr, Rectf(100,150,86,106), Rectf(0,0,86,106))
	,m_ActionState{ActionState::idle}
	,m_HorSpeed{125.f}
	,m_VerSpeed{75.f}
	,m_HorSpeedShift{175.f}
	,m_ToggleRun{false}
	,m_SmallHitbox{}
	,m_ShiftDelay{1.f}
	,m_BarrelPos()
	,m_ShootDelay(0.75f)
{
	MakeSpriteVector();
}

Clone::~Clone()
{
	for (int i = 0; i < int(m_Sprites.size()); i++)
	{
		delete m_Sprites[i];
		m_Sprites[i] = nullptr;
	}
	m_Sprite = nullptr;
}

void Clone::Update(float elapsedSec)
{
	Moveable::Update(elapsedSec);
	UpdateCurrentState(elapsedSec);
	
	m_Level->GetSmoothCam()->Track(Point2f{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom + 4.f * m_Rect.height / 3.f }, elapsedSec);
	m_ShiftDelay.Update(elapsedSec);
	RunToggle();
	Movement(elapsedSec);

	if (m_CurentOrientation == Orientation::left)
	{
		m_BarrelPos.x = m_Hitbox.left - 2 * m_Hitbox.width/3.f;
		m_BarrelPos.y = 3 * m_Hitbox.height / 5.f + m_Hitbox.bottom;
	}
	else
	{
		m_BarrelPos.x = m_Hitbox.width + m_Hitbox.left;
		m_BarrelPos.y = 3 * m_Hitbox.height / 5.f + m_Hitbox.bottom;
	}



	Shoot();
	m_ShootDelay.Update(elapsedSec);
	
}

void Clone::Movement(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (m_ActionState != ActionState::isHit && m_ActionState!=ActionState::shooting)
	{
		m_ActionState = ActionState::idle;
	}

	m_Direction.x = 0;
	m_Direction.y = 0;
	m_Speed.x = m_HorSpeed;
	m_Speed.y = m_HorSpeed;

	if (pStates[SDL_SCANCODE_RIGHT])
	{
		
		m_Direction.x = 1.0f;
		m_ActionState = ActionState::walking;
		m_CurentOrientation = Orientation::right;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		m_Direction.x = -1.0f;
		m_ActionState = ActionState::walking;

		m_CurentOrientation = Orientation::left;
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		m_Direction.y = 1.0f;

		m_ActionState = ActionState::walking;
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		m_Direction.y = -1.0f;

		m_ActionState = ActionState::walking;
	}

	if(m_ToggleRun && m_ActionState == ActionState::walking)
	{
		m_ActionState = ActionState::running;
		
		m_Speed.x = m_HorSpeedShift;
		if(abs(m_Direction.x) > 0)
		{
			m_Speed.y = m_HorSpeedShift;
		}
	}
	
	m_SmallHitbox.bottom = m_Rect.bottom + m_Rect.height / 3.f;
	m_SmallHitbox.left = m_Rect.left;
	m_SmallHitbox.width = m_Rect.width;
	m_SmallHitbox.height = m_Rect.height / 3.f;

}

void Clone::RunToggle()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	
	if (pStates[SDL_SCANCODE_LSHIFT] && !m_ShiftDelay.GetIsActive())
	{
		m_ToggleRun = !m_ToggleRun;
		m_ShiftDelay.Start();

	}
}

void Clone::MakeSpriteVector()
{
	m_Sprites.push_back(new Sprite{ "Resources/Clone00.png", 1, 1 });	//idle
	m_Sprites.push_back(new Sprite{ "Resources/Clone01.png", 8, 1 });	//walk
	m_Sprites.push_back(new Sprite{ "Resources/Clone03.png", 8, 1 });	//run
	m_Sprites.push_back(new Sprite{ "Resources/Clone02.png", 7, 1 });	//shoot
	m_Sprites.push_back(new Sprite{ "Resources/Clone04.png", 6, 1 });	//isHit
	m_Sprites.push_back(new Sprite{ "Resources/Clone05.png", 9, 1 });	//dying
	m_Sprites.push_back(new Sprite{ "Resources/Clone06.png", 1, 1 });	//dead
	m_Sprites.push_back(new Sprite{ "Resources/Clone07.png", 13, 1 });//melee
}

void Clone::UpdateCurrentState(float elapsedSec)
{
	m_Sprite = m_Sprites[int(m_ActionState)];
	m_Sprites[int(m_ActionState)]->Update(elapsedSec);
}

void Clone::Shoot() 
{
	int x{};
	int y{};
	float tempDirection{};
	
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))		//Check als linkermuis is ingedrukt
	{
		if(!m_HasShot && !m_ShootDelay.GetIsActive())					//Check als al geschoten is, zo ja nietmeer schieten zo nee schiet
		{
			m_ActionState = ActionState::shooting;
			m_ShootDelay.Start();
			m_HasShot = true;
			if(m_CurentOrientation== Orientation::left)
			{
				tempDirection = -1.f;
			}
			else
			{
				tempDirection = 1.f;
			}
			std::cout << "I'm shooting" << std::endl;
			
			m_Level->AddObject(new BlueBullet(m_Level, m_BarrelPos, Vector2f(tempDirection,0.f)));
		}
		
	}
	else
	{
		m_HasShot = false;
	}

}
