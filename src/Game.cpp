// Steven Rogers 2016

#include "stdafx.h"

Game::Game(sf::RenderWindow& rw) :
	m_rwWindow(rw),
	m_strCurrentBackground("gfx\\bg.jpg")
{
	LoadSprite("gfx\\bg.jpg", 0, 0);
	LoadSprite("gfx\\bg_red.jpg", 0, 0);
	LoadSprite("gfx\\bg_green.jpg", 0, 0);

	if (!m_font.loadFromFile("gfx\\KeepCalm-Medium.ttf"))
		printf("Failed to load font.\n");

	SetDrawText("Please standby.");
	
	LoadSound("sfx\\time_up.ogg");
	LoadSound("sfx\\time_almost_up.ogg");
	LoadSound("sfx\\score_5.ogg");
	LoadSound("sfx\\score_4.ogg");
	LoadSound("sfx\\score_3.ogg");
	LoadSound("sfx\\score_2.ogg");
	LoadSound("sfx\\score_1.ogg");
	LoadSound("sfx\\new_question.ogg");

	if (!m_music.openFromFile("sfx\\music.ogg"))
		printf("Failed to load music.\n");

	m_music.setLoop(true);
	m_music.setVolume(15.0f);
	m_music.play();
}

void Game::Draw()
{
	DrawSprite(m_strCurrentBackground);

	if (!m_strCenterText.empty())
		DrawText(m_strCenterText, SCREEN_W / 2.0f, SCREEN_H / 2.5f);
}

void Game::OnRewardedPoints(const uint32 points)
{
	std::string soundName = "sfx\\score_" + std::to_string(points) + ".ogg";
	PlaySound(soundName);
}

void Game::LoadSprite(const std::string spriteName, const float x, const float y)
{
	m_vTextureData.push_back(std::shared_ptr<sf::Texture>(new sf::Texture()));

	if (!m_vTextureData[m_vTextureData.size() - 1]->loadFromFile(spriteName))
	{
		printf("Failed to load sprite %s.\n", spriteName.c_str());
		return;
	}
	
	m_uoSpriteMap[spriteName].setPosition(x, y);
	m_uoSpriteMap[spriteName].setTexture(*m_vTextureData[m_vTextureData.size() - 1]);
}

void Game::LoadSound(const std::string soundName, const float x, const float Y)
{
	m_vSoundData.push_back(std::shared_ptr<sf::SoundBuffer>(new sf::SoundBuffer()));

	if (!m_vSoundData[m_vSoundData.size() - 1]->loadFromFile(soundName))
	{
		printf("Failed to load sound %s.\n", soundName.c_str());
		return;
	}

	m_uoSoundMap[soundName].setBuffer(*m_vSoundData[m_vSoundData.size() - 1]);
}

void Game::DrawSprite(const std::string spriteName, const float x, const float y)
{
	auto itr = m_uoSpriteMap.find(spriteName);
	ASSERT(itr != m_uoSpriteMap.end());

	if (x >= 0 && y >= 0)
		itr->second.setPosition(x, y);

	m_rwWindow.draw(itr->second);
}

void Game::DrawText(const std::string strText, const float x, const float y, const bool bOutline)
{
	sf::Text text;

	if (bOutline)
		DrawText(strText, x + 5, y + 5, false);

	text.setFont(m_font);
	text.setString(strText);
	text.setCharacterSize(48);
	text.setColor(bOutline ? sf::Color::Yellow : sf::Color::Black);
	text.setPosition(floor(x), floor(y));

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(floor(textRect.left + textRect.width / 2.0f), floor(textRect.top + textRect.height / 2.0f));

	m_rwWindow.draw(text);
}

void Game::PlaySound(const std::string soundName)
{
	auto itr = m_uoSoundMap.find(soundName);
	ASSERT(itr != m_uoSoundMap.end());
	itr->second.play();
}

void Game::SetDrawText(const std::string strText)
{
	m_strCenterText = strText;

	int32 count = 0;

	for (size_t i = 0; i < m_strCenterText.size(); ++i)
	{
		if (count >= 25)
		{
			if (m_strCenterText[i] == ' ')
			{
				count = 0;
				m_strCenterText[i] = '\n';
			}
		}
		else
		{
			++count;
		}
	}
}