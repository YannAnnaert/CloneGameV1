#pragma once
#include "Moveable.h"

class DestroyableBlock : public Moveable
{
public:
	DestroyableBlock(Rectf shape, Level* level);
	~DestroyableBlock() = default;
	void Draw() const override;
	void Update(float elapsedSec) { Moveable::Update(elapsedSec); }

private:
protected:
	virtual void OnCollision(CollisionObject* collisionObject);


};