// Steven Rogers 2016

#ifndef _GAME_H
#define _GAME_H

#include "stdafx.h"

class Game
{
	public:
		Game(sf::RenderWindow& rw);

		void Draw();
		void OnRewardedPoints(const uint32 amount);
		void PlaySound(const std::string soundName);
		void SetDrawText(const std::string strText);

	private:
		void LoadSprite(const std::string spriteName, const float x = 0, const float y = 0);
		void LoadSound(const std::string soundName, const float x = 0, const float y = 0);
		void DrawSprite(const std::string spriteName, const float x = -1, const float y = -1);
		void DrawText(const std::string strText, const float x, const float y, const bool bOutline = true);

		std::string m_strCenterText;
		std::string m_strCurrentBackground;

		sf::Font m_font;
		sf::Music m_music;

		sf::RenderWindow& m_rwWindow;
		
		std::vector<std::shared_ptr<sf::Texture>> m_vTextureData;
		std::vector<std::shared_ptr<sf::SoundBuffer>> m_vSoundData;
		
		std::unordered_map<std::string, sf::Sound> m_uoSoundMap;
		std::unordered_map<std::string, sf::Sprite> m_uoSpriteMap;
};

#endif