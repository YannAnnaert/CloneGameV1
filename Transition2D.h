#pragma once
#include "Delay.h"
#include "TransitionController.h"
class Transition2D
{
public:
	explicit Transition2D(const std::string& name):m_Name(name),m_Delay(1){}
	virtual ~Transition2D()=default;

	Transition2D(const Transition2D& other) = delete;
	Transition2D(Transition2D&& other) = delete;
	Transition2D& operator=(const Transition2D& other) = delete;
	Transition2D& operator=(Transition2D&& other) = delete;

	virtual void Start()=0;
	virtual void Update(float deltaTime){}
	virtual void Render()const{}

	void SetDelayTime(const float& time) { m_Delay.SetDelayTime(time); }
	std::string GetName()const { return m_Name; }
	
	friend TransitionController;
protected:
	Delay m_Delay;
private:
	bool m_IsStarted=false;
	std::string m_Name;
	void UpdateDelay(float deltaTime);
	virtual void OnExit(){}
};

class FadeExample final:public Transition2D
{
public:
	explicit FadeExample(const Window& window, const std::string& name)
	:Transition2D(name),m_Window(window)
	{
		m_Delay.SetDelayTime(2);
	} 
	void Start()override;
	void Update(float deltaTime)override;
	void Render()const override;
private:
	void OnExit() override;
	float m_MaxOpacity = 1;
	float m_CurrentOpacity = 1;
	float m_Fade = 0.5f;
	Window m_Window{};
	
};