#pragma once
#include <map>

struct Rectf 
{
};
class Texture { public: void Draw(); };

class Player
{
public:
	Player(){}
	virtual ~Player();
	
	virtual void Draw()
	{
		m_Texture.Draw();
	}
	virtual void Update()
	{
		//MOVE
		//SHOOT
		//TAKE DAMGE
		//DIE
		//WHATEVER
	}

	bool GetDead();
	
	Rectf GetDest();
	void SetDest(Rectf x);

protected:
	//WHATEVERS
	float m_MaxHealth;
	float m_Movementspeed;
	bool m_dead;//no
	//,,,,,,,,,,,,
	//ANIMS
	Texture m_Texture;
	//,,,,,,,,,,,,,,,,,,,,,,,
};

class player0 :public Player
{
public:
	player0()
	{
		m_MaxHealth = 100;
		m_Movementspeed = 100;
		//WHATEVER
	}
};
class player1 :public Player
{
public:
	player1()
	{
		m_MaxHealth = 200;
		m_Movementspeed = 200;
		//WHATEVER
	}
};
// ,,,,,,,

class PlayerManager
{
public:
	enum class PlayerType
	{
		clone0
		,clone1
		//,,,,,,
	};

	PlayerManager()
	{
		m_Players.emplace(PlayerType::clone0, new player0{});
		m_Players.emplace(PlayerType::clone1, new player1{});
		//,,,,,,,,,,,,,,,,,,

	}
	void Draw()
	{
		//DRAW CURRENT PLAYER
		m_Players[m_CurrentPlayerType]->Draw();
	}
	void Update()
	{
		//UPDATE CURRENT PLAYER
		m_Players[m_CurrentPlayerType]->Update();
		//REMOVE THE DEAD
		m_Players.erase(std::remove_if(m_Players.begin(), m_Players.end(), [&](std::pair<PlayerType, Player*>* element)
		{
			return element->second->GetDead();
		}), m_Players.end());
	}
	void SwapPlayer(PlayerType type)
	{
		m_Players[type]->SetDest(m_Players[m_CurrentPlayerType]->GetDest());
		m_CurrentPlayerType = type;
		//spawn explosion something effect to make swap cooooooooooooooooooooooooooooool
	}
private:
	std::map<PlayerType, Player*> m_Players;
	PlayerType m_CurrentPlayerType;
};
