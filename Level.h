#pragma once
#include "structs.h"
#include "Vector2f.h"
#include <vector>
#include "Texture.h"

class Blocc;
class Object;
class Camera2D;
class CollisionObject;

class Level
{
public:
	Level(Window window);
	~Level();
	void Draw() const;
	void Update(float elapsedSec);

	
	
	Rectf GetBoundaries();
	void AddObject(Object* object);
	
	void LoadTestLevel();
	std::vector<Object*> GetAllObjects();
	Camera2D* GetSmoothCam();
	std::vector<CollisionObject*> GetCollisionObjects() const { return m_CollisionObjects; }

private:
	void RemoveObject(Object* object);

	void DrawBackground() const;
	void DrawForeground() const;

	Texture m_BackgroundTexture;
	Texture m_FenceTexture;
	Point2f m_FenceBottomLeft;
	Rectf m_Boundaries;
	std::vector <Object*> m_Objects;
	std::vector<CollisionObject*> m_CollisionObjects;

	Camera2D* m_SmoothCam;
};
