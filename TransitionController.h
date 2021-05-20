#pragma once
#include <vector>
class Transition2D;
class TransitionController
{
public:
	TransitionController() = default;
	~TransitionController();
	void Update(float deltaTime);
	void Render()const;
	void TriggerTransition(const std::string& name);
	void AddTransition(Transition2D* transition) { m_Transitions.push_back(transition); }
private:
	std::vector<Transition2D*>m_Transitions;
};