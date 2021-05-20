#pragma once
#include "Level.h"

class Object
{
public:
	Object(Level* level) :m_Level{ level } {
		m_Counter++;
		m_Tag = m_Counter;
	};
	virtual ~Object() = default;
	virtual void Draw() const {}
	virtual void Update(float elapsedSec){}
	int GetTag() const { return m_Tag; }  
	
	bool GetIsReadyForRemoval() const { return m_ReadyForRemoval; }
	void SetIsReadyForRemoval(bool x) { m_ReadyForRemoval = x; }

private:

	int m_Tag;
	static int m_Counter;

protected:
	bool m_ReadyForRemoval = false;
	Level* m_Level;
};

