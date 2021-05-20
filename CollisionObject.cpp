#include "pch.h"
#include "CollisionObject.h"

CollisionObject::CollisionObject(Level* level, const Rectf& destRect, const Rectf& hitbox)
	:Object(level)
	,m_Rect(destRect)
	,m_Hitbox()
	,m_OriginalHitbox(hitbox)
	,m_IsStatic(false)
	,m_IsTrigger(false)

{
	
}


void CollisionObject::Update(float elapsedSec)
{
	m_Hitbox = m_OriginalHitbox;
	m_Hitbox.left += m_Rect.left;
	m_Hitbox.bottom += m_Rect.bottom;
	
	for(CollisionObject* obj:m_Level->GetCollisionObjects())
	{
	
		if (utils::IsOverlapping(m_Hitbox, obj->GetHitbox()) && GetTag() != obj->GetTag())
		{
			if (!m_IsTrigger && !obj->GetIsTrigger() && !m_IsStatic)
			{
				utils::HitInfo info{};
				Point2f lineBottom{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom };
				Point2f lineBottomBitHigher{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom + m_Rect.height / 10.f };
				Point2f lineTop{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom + m_Rect.height };
				Point2f lineHalf{ m_Rect.left + m_Rect.width / 2.f, m_Rect.bottom + m_Rect.height / 2.f };
				Point2f lineRight{ m_Rect.left + m_Rect.width, m_Rect.bottom + m_Rect.height / 10.f };
				Point2f lineLeft{ m_Rect.left, m_Rect.bottom + m_Rect.height / 10.f };

				std::vector<Point2f> vertices;
				
				Point2f vertexOne{ obj->GetHitbox().left, obj->GetHitbox().bottom };
				Point2f vertexTwo{ obj->GetHitbox().left + obj->GetHitbox().width, obj->GetHitbox().bottom };
				Point2f vertexTree{ obj->GetHitbox().left + obj->GetHitbox().width, obj->GetHitbox().bottom + obj->GetHitbox().height};
				Point2f vertexFour{ obj->GetHitbox().left, obj->GetHitbox().bottom + obj->GetHitbox().height};

				vertices.push_back(vertexOne);
				vertices.push_back(vertexTwo);
				vertices.push_back(vertexTree);
				vertices.push_back(vertexFour);

				utils::DrawLine(lineHalf, lineTop);
				utils::DrawLine(lineBottom, lineHalf);
				
				if (utils::Raycast(vertices, lineBottom, lineBottomBitHigher, info))
				{
					m_Rect.bottom = info.intersectPoint.y;
				}
				if (utils::Raycast(vertices, lineHalf, lineTop, info))
				{
					m_Rect.bottom = info.intersectPoint.y - m_Rect.height;
				}
				if (utils::Raycast(vertices, lineBottomBitHigher, lineRight, info))
				{
					m_Rect.left = info.intersectPoint.x - m_Rect.width;
				}
				if (utils::Raycast(vertices, lineBottomBitHigher, lineLeft, info))
				{
					m_Rect.left = info.intersectPoint.x;
				}
				
			}
			
			OnCollision(obj);
		}
	}
}



