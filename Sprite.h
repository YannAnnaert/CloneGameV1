#pragma once

class Sprite
{
public:
	Sprite(const std::string& stringTexture, const int cols, const int rows);
	Sprite(const Texture* texture, const int cols, const int rows);
	~Sprite();
	void Draw(const Rectf& destRect) const;
	void Update(float elapsedSec);
	

	void SetFrameRate(int frames);
	void AddFramesPerSec(int frames);
	float GetTextureWidth();
	float GetTextureHeight();

private:
	const Texture* m_Texture;
	const float m_SpriteSheetLeft;
	const float m_SpriteSheetTop;
	float m_SpriteSheetWidth;
	float m_SpriteSheetHeight;
	const int m_Cols;
	const int m_Rows;
	int m_FramesPerSec;
	float m_FrameTime;
	int m_FrameCounter;

	float m_AccuSec;
	int m_CurrFrame;
	Rectf m_SrcRect;
	

	void UpdateSprite(float elapsedSec);
	void DrawSprite(const Rectf& destRect) const;
	
	void InitSrcRect();
	void UpdateSrcRect();
	int GetCurrentFrame() const { return m_FrameCounter; }
	
};