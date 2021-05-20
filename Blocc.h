#pragma once
#include "structs.h"
#include "CollisionObject.h"

class Blocc : public CollisionObject
{
public:
	Blocc(Rectf shape, Level* level);
	virtual ~Blocc() =default;
	virtual void Draw() const;
	virtual void Update(float elapsedSec) { CollisionObject::Update(elapsedSec); }
	
	

private:
	void OnCollision(CollisionObject* collisionObject) ;

protected:

	
};

class RedBlocc final :public Blocc
{
public:
	RedBlocc(Rectf shape, Level* level);
	virtual ~RedBlocc() = default;
	void Draw() const override;
	void Update (float elapsedSec) 
	{
		Blocc::Update(elapsedSec);
	}
private:

};