// ConsoleApplication1.cpp : Defines the entry point for the console application.
// Steven Rogers 2016

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	srand((uint32)time(NULL));

	std::vector<std::string> config = Util::readLinesFromFile("login.txt");

	if (config.size() < 5)
	{
		printf("There was an issue reading login.txt.\n");
		system("pause");
		return 0;
	}
	
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Twitch Trivia");

	Game game(window);
	TwitchIRC irc(&game, config[0], config[0], config[1], (uint32)atoi(config[2].c_str()), config[3], config[4]);
	
	// run the program as long as the window is open
    while (window.isOpen() && irc.activeSocket())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

		// do stuff
		game.Draw();
		irc.Update();

        // end the current frame
        window.display();
    }

	return 0;
}