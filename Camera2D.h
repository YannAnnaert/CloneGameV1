#pragma once
#include "Delay.h"
#include "structs.h"


class Camera2D final
{
public:
	explicit Camera2D(const Point2f& startPos, const Window& window);
	~Camera2D() = default;

	Camera2D(const Camera2D& other) = delete;
	Camera2D(Camera2D&& other) = delete;
	Camera2D& operator=(const Camera2D& other) = delete;
	Camera2D& operator=(Camera2D&& other) = delete;
	//SHAKE
	void DoCameraShake() { m_DoCameraShake = true; };
	//ZOOM
	void Zoom(const float& zoom);
	void Zoom(const float& zoomX, const float& zoomY);
	//MOVEMENT
	void Track(const Point2f& target, const float& deltaTime);
	static void Translate(const float& x, const float& y);
	//VAR
	Point2f GetMousePos() const;
	Window GetScaledWindowSize()const;
	Point2f GetPosition()const;
	float GetScaleX()const { return m_ScaleX; }
	float GetScaleY()const { return m_ScaleY; }
private:
	//SHAKE
	void CameraShake();
	bool m_DoCameraShake = false;
	int m_ShakeCounter = 0;
	int m_NumberOfShakes = 2;
	//TRACK
	Delay m_TrackDelay{ 0.001f };
	float m_LerpValue = 60; //Higher value equals slower tracking
	//VAR
	Point2f m_Position = {};
	float m_Speed = 400;
	float m_ScaleX = 1;
	float m_ScaleY = 1;
	Window m_Window{};
	Window m_OriginalWindow{ "Original",846,500 };
};
