#include "pch.h"
#include "Level.h"
#include "Object.h"
#include "Blocc.h"
#include "Clone.h"
#include "Camera2D.h"
#include "CollisionObject.h"
#include "DestroyableBlock.h"

Level::Level(Window window)
	: m_BackgroundTexture{ "Resources/background.png" }
	, m_FenceTexture{ "Resources/Fence.png" }
	, m_FenceBottomLeft{ 200,190 }
	, m_Boundaries{ 0,0, m_BackgroundTexture.GetWidth(), m_BackgroundTexture.GetHeight() }
	
	

{
	m_SmoothCam = new Camera2D{ Point2f{0,0}, window };
	LoadTestLevel();
}

Level::~Level()
{
	for (int i = 0; i < int( m_Objects.size()); i++)
	{
		delete m_Objects[i];
		m_Objects[i] = nullptr;
	}
	delete m_SmoothCam;
	m_SmoothCam = nullptr;
}

void Level::Draw() const
{
	DrawBackground();
	
	
	DrawForeground();
}

void Level::Update(float elapsedSec)
{
	Vector2f testVelo{};
	
	for (int i = 0; i < int(m_Objects.size()); i++)
	{
		m_Objects[i]->Update(elapsedSec);
	}

	for (int i = 0; i < int(m_Objects.size()); i++)
	{
		if(m_Objects[i]->GetIsReadyForRemoval())
		{
			RemoveObject(m_Objects[i]);
		}
	}
}

void Level::DrawBackground() const
{
	//m_BackgroundTexture.Draw();
}

void Level::DrawForeground() const
{
	//m_FenceTexture.Draw(m_FenceBottomLeft);
	for (int i = 0; i < int(m_Objects.size()); i++)
	{
		m_Objects[i]->Draw();
	}
}

Rectf Level::GetBoundaries()
{
	return m_Boundaries;
}

void Level::AddObject(Object* object)
{
	m_Objects.push_back(object);

	if(dynamic_cast<CollisionObject*>(object))
	{
		m_CollisionObjects.push_back((dynamic_cast<CollisionObject*>(object)));
	}
}

void Level::RemoveObject(Object* object)
{
	for (int i = 0; i <int(m_CollisionObjects.size()); i++)
	{
		if (m_CollisionObjects[i]->GetTag() == object->GetTag())
		{
			m_CollisionObjects[i] = m_CollisionObjects.back();
			m_CollisionObjects.pop_back();
		}
	}
	for (int i = 0; i <int( m_Objects.size()); i++)
	{
		if (m_Objects[i]->GetTag() == object->GetTag())
		{
			m_Objects[i] = m_Objects.back();
			m_Objects.pop_back();
		}
	}

	/*if (m_Objects.size() > 0)
	{
		m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), [&](Object* obj)		/
			{
				return object->GetTag() == obj->GetTag();
			}), m_Objects.end());
	}*/
	delete object;
}

void Level::LoadTestLevel()
{
	AddObject(new Clone{ this });

	for (int i{}; i < 10; ++i)
	{
		AddObject(new Blocc{ Rectf{float(i * 100),50,100,100}, this });
	}
	for (int i{}; i < 10; ++i)
	{
		AddObject(new RedBlocc{ Rectf{float(i * 100),350,100,100}, this });
	}

	AddObject(new DestroyableBlock{ Rectf{500, 150, 100,100}, this });

	AddObject(new RedBlocc{ Rectf{0,250,100,100}, this });
	AddObject(new Blocc{ Rectf{0,150,100,100}, this });
	AddObject(new RedBlocc{ Rectf{900,250,100,100}, this });
	AddObject(new Blocc{ Rectf{900,150,100,100}, this });

}

std::vector<Object*> Level::GetAllObjects()
{
	return m_Objects;
}

Camera2D* Level::GetSmoothCam()
{
	return m_SmoothCam;
}