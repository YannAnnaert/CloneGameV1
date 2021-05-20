#include "pch.h"
#include "Transition2D.h"


void Transition2D::UpdateDelay(float deltaTime)
{
	if(m_Delay.Update(deltaTime))
	{
		m_IsStarted = false;
		OnExit();
	}
}

//EXAMPLE
void FadeExample::Start()
{
	m_CurrentOpacity = m_MaxOpacity;
}
void FadeExample::Update(float deltaTime)
{
	m_CurrentOpacity -= m_Fade * deltaTime;
}
void FadeExample::Render() const
{
	utils::SetColor(Color4f{1,1,1,m_CurrentOpacity});
	utils::FillRect(0, 0, m_Window.width, m_Window.height);
}
void FadeExample::OnExit()
{
	std::cout << "NielsGay" << std::endl;
}
