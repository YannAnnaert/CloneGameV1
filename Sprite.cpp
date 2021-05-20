#pragma once
#include "pch.h"
#include "Texture.h"
#include "Sprite.h"



Sprite::Sprite(const std::string& stringTexture, const int cols, const int rows)
	:m_SpriteSheetLeft{0.f}
	,m_SpriteSheetTop{0.f}
	,m_Cols{cols}
	,m_Rows{rows}
	,m_FramesPerSec{15}

	,m_AccuSec{}
	,m_CurrFrame{}
	,m_SrcRect{}
	,m_FrameCounter()

	
{
	m_Texture = new Texture{ stringTexture };
	m_SpriteSheetWidth = m_Texture->GetWidth() ;
	m_SpriteSheetHeight = m_Texture->GetHeight() ;
	m_FrameTime = 1.0f / m_FramesPerSec;
	InitSrcRect();
	
}

Sprite::Sprite(const Texture* texture, const int cols, const int rows)
	: m_Texture{ texture }
	, m_SpriteSheetLeft{ 0.f }
	, m_SpriteSheetTop{ 0.f }
	, m_SpriteSheetWidth{ m_Texture->GetWidth() }
	, m_SpriteSheetHeight{ m_Texture->GetHeight() }
	, m_Cols{ cols }
	, m_Rows{ rows }
	, m_FramesPerSec{ 15 }

	, m_AccuSec{}
	, m_CurrFrame{}
	, m_SrcRect{}
	,m_FrameCounter()


{
	m_FrameTime = 1.0f / m_FramesPerSec;
	InitSrcRect();
}

Sprite::~Sprite()
{
	delete m_Texture;
}

void Sprite::Draw(const Rectf& destRect) const
{
	

	DrawSprite(destRect);
}

void Sprite::Update(float elapsedSec)
{
	UpdateSprite(elapsedSec);
}

void Sprite::InitSrcRect()
{
	m_SrcRect.width = m_SpriteSheetWidth / m_Cols;
	m_SrcRect.height = m_SpriteSheetHeight / m_Rows;
	UpdateSrcRect();
}

void Sprite::UpdateSrcRect()
{
	m_SrcRect.left = m_SpriteSheetLeft + m_CurrFrame % m_Cols * m_SrcRect.width;
	m_SrcRect.bottom = m_SpriteSheetTop + (m_CurrFrame / m_Cols + 1) * m_SrcRect.height;
}


void Sprite::UpdateSprite(float elapsedSec)
{

	//if met counter -> check als laatse frame -> zet bool -> get bool + nils gay
	
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameTime)
	{
		++m_FrameCounter;
		if(m_FrameCounter == m_Cols)
		{
			
		}
		++m_CurrFrame %= (m_Cols * m_Rows);
		m_AccuSec -= m_FrameTime;
		UpdateSrcRect();
	}
}

void Sprite::DrawSprite(const Rectf& destRect) const
{
	m_Texture->Draw(destRect, m_SrcRect);
}

void Sprite::SetFrameRate(int frames)
{
	m_FramesPerSec = frames;
}

void Sprite::AddFramesPerSec(int frames)
{
	m_FramesPerSec += frames;
}

float Sprite::GetTextureWidth()
{
	return m_Texture->GetWidth();
}

float Sprite::GetTextureHeight()
{
	return m_Texture->GetHeight();
}

