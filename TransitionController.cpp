#include "pch.h"
#include "TransitionController.h"
#include "Transition2D.h"
void TransitionController::Update(float deltaTime)
{
	for (auto transition : m_Transitions)
	{
		if (transition->m_IsStarted)
		{
			transition->Update(deltaTime);
			transition->UpdateDelay(deltaTime);
		}
	}
}
void TransitionController::Render() const
{
	for (auto transition : m_Transitions)
	{
		if (transition->m_IsStarted)
		{
			transition->Render();
		}
	}
}
void TransitionController::TriggerTransition(const std::string& name)
{
	for (auto transition : m_Transitions)
	{
		if (transition->GetName() == name)
		{
			if (!transition->m_IsStarted)
			{
				transition->m_Delay.Reset();
				transition->m_Delay.Start();
				transition->m_IsStarted = true;
				transition->Start();
			}
		}
	}
}
TransitionController::~TransitionController()
{
	for (auto transition:m_Transitions)
	{
		delete transition;
	}
}
