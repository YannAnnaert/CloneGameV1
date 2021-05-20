#include "pch.h"
#include "DestroyableBlock.h"
#include "CollisionObject.h"
#include "Bullet.h"
#include "Object.h"
#include "Blocc.h"


DestroyableBlock::DestroyableBlock(Rectf shape, Level* level)
	:Moveable(level, nullptr, shape, Rectf{ 0, 0, shape.width, shape.height })
{
	
}



void DestroyableBlock::Draw() const
{
	Moveable::Draw();
	utils::SetColor(Color4f{ 0,1,1,1 });
	utils::FillRect(m_Rect);
}

void DestroyableBlock::OnCollision(CollisionObject* collisionObject)
{
	if(dynamic_cast<Bullet*>(collisionObject))
	{
		m_ReadyForRemoval = true;
		collisionObject->SetIsReadyForRemoval(true);
	}
	else if(dynamic_cast<Blocc*>(collisionObject))
	{
		utils::HitInfo info{};
		Point2f horLineBegin{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom + m_Rect.height /2.f};
		Point2f horLineEnd{ m_Rect.left + m_Rect.width, m_Rect.bottom + m_Rect.height / 2.f };
		
		std::vector<Point2f> vertices;

		Point2f vertexOne{ collisionObject->GetHitbox().left, collisionObject->GetHitbox().bottom };
		Point2f vertexTwo{ collisionObject->GetHitbox().left + collisionObject->GetHitbox().width, collisionObject->GetHitbox().bottom };
		Point2f vertexTree{ collisionObject->GetHitbox().left + collisionObject->GetHitbox().width, collisionObject->GetHitbox().bottom + collisionObject->GetHitbox().height };
		Point2f vertexFour{ collisionObject->GetHitbox().left, collisionObject->GetHitbox().bottom + collisionObject->GetHitbox().height };

		vertices.push_back(vertexOne);
		vertices.push_back(vertexTwo);
		vertices.push_back(vertexTree);
		vertices.push_back(vertexFour);

		if (utils::Raycast(vertices, horLineBegin, horLineEnd, info))
		{
		
		}
	}
}
