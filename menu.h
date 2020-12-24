#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;




void menu(RenderWindow& window) {
	Texture startgamebutton, settingsbutton, exitbutton, menuBack, settingsmenu, menuBackground, startmenu, gamemode;
	startgamebutton.loadFromFile("menu/startgame.png");
	settingsbutton.loadFromFile("menu/settings.png");
	exitbutton.loadFromFile("menu/exit.png");
	menuBack.loadFromFile("menu/back.png");
	settingsmenu.loadFromFile("menu/settingsmenu2.png");
	menuBackground.loadFromFile("menu/backgroundMenu2.png");
	startmenu.loadFromFile("menu/startmenu.png");
	gamemode.loadFromFile("menu/gamemode.png");
	Sprite Sstartgamebutton(startgamebutton), Ssettingsbutton(settingsbutton), Sexitbutton(exitbutton), Sbackbutton(menuBack), Ssettingsmenu(settingsmenu), menuBg(menuBackground), Sstartmenu(startmenu), Sgamemode(gamemode);
	bool isMenuStart = 1;
	bool isMenu = 0;
	bool isMenuSettings = 0;
	bool spacepressed = 0;
	bool mousepressed = 0;
	bool gamemodeInGame = false;
	Sstartgamebutton.setPosition(555, 350);
	Ssettingsbutton.setPosition(555, 400);
	Sexitbutton.setPosition(555, 450);
	Sbackbutton.setPosition(555, 650);
	Ssettingsmenu.setPosition(0, 0);
	menuBg.setPosition(0, 0);
	Sstartmenu.setPosition(0, 0);
	Sgamemode.setPosition(555, 450);

	Music music;
	music.openFromFile("sounds/menu.ogg");
	music.setVolume(50.f);
	music.play();
	music.setLoop(true);

	SoundBuffer clickbuffer;
	clickbuffer.loadFromFile("sounds/click.ogg");
	Sound click(clickbuffer);
	click.setVolume(40.f);

	while (isMenuStart) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//if (!Keyboard::isKeyPressed(Keyboard::Escape)) { isMenuStart = 1 ;}

		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			spacepressed = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space)) {
			if (spacepressed) {
				click.play();
				isMenu = true;
				isMenuStart = false;
				spacepressed = false;
			}
			window.clear();
			window.draw(Sstartmenu);
			window.display();
		}
	}

		while (isMenu)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			Sstartgamebutton.setColor(Color::White);
			Ssettingsbutton.setColor(Color::White);
			Sexitbutton.setColor(Color::White);

			window.clear();
			//if (!Keyboard::isKeyPressed(Keyboard::Escape)) { isMenu = 1; }

			//кнопкa start
			if (IntRect(555, 350, 169, 39).contains(Mouse::getPosition(window))) 
				{
					Sstartgamebutton.setColor(Color::Red);  
						if (Mouse::isButtonPressed(Mouse::Left)) {
								isMenu = false;
							}
				}
			//кнопкa settings
			if (IntRect(555, 400, 169, 39).contains(Mouse::getPosition(window)))
			{
				Ssettingsbutton.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					mousepressed = true;
				}
				if (!Mouse::isButtonPressed(Mouse::Left)) {
					if (mousepressed) {
						click.play();
						isMenuSettings = true;
						isMenu = false;
					}
					mousepressed = false;
				}
			}
			//кнопкa exit
			if (IntRect(555, 450, 169, 39).contains(Mouse::getPosition(window)))
			{ 
				Sexitbutton.setColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left)) {
						window.close(); isMenu = false;
					}
			}
			// РАЗДЕЛ МЕНЮ НАСТРОЕК
			while (isMenuSettings) {
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
				}

				Sbackbutton.setColor(Color::White);
				Sgamemode.setColor(Color::White);

				if (IntRect(555, 650, 169, 39).contains(Mouse::getPosition(window)))
				{
					Sbackbutton.setColor(Color::Red);
					if (Mouse::isButtonPressed(Mouse::Left)) {
						mousepressed = true;
					}
					if (!Mouse::isButtonPressed(Mouse::Left)) {
						if (mousepressed) {
							isMenu = true;
							isMenuSettings = false;

							click.play();
						}
						mousepressed = false;
					}

				}
				// КНОПКА ПЕРЕКЛЮЧЕНИЯ ГЕЙММОДА 
				if (IntRect(555, 450, 169, 39).contains(Mouse::getPosition(window))) // ЕСЛИ КУРСОР В ГРАНИЦЕ КНОПКИ, ОНА -->
				{
					Sgamemode.setColor(Color::Red);  // --> СТАНОВИТСЯ КРАСНОЙ

					if (Mouse::isButtonPressed(Mouse::Left)) {   // ЕСЛИ ЛЕВАЯ КНОПКА НАЖАТА, ТО -->
						mousepressed = true; // ПЕРЕМЕННАЯ "КНОПКА НАЖАТА = 1 "
					}
					if (!Mouse::isButtonPressed(Mouse::Left) && mousepressed) {  // ЕСЛИ КНОПКА БЫЛА НАЖАТА ТО ->
						 click.play();  // --> ИГРАЕТ ЗВУК
						if (gamemodeInGame) { gamemodeInGame = false; mousepressed = false; } // ЕСЛИ GAMEMODE = 1, ТО СТАНОВИТСЯ = 0, КНОПКА ОТЖАТА
						else if (!gamemodeInGame) { gamemodeInGame = true; mousepressed = false; } // ЕСЛИ GAMEMODE = 0, ТО СТАНОВИТСЯ = 1, КНОПКА ОТЖАТА
					}
				}
				if (!gamemodeInGame) { Sgamemode.setTextureRect(IntRect(0, 0, 169, 39)); } // ЕСЛИ GAMEMODE = 0 ТО ПОКАЗЫВАЕТСЯ СПРАЙТ EASY
				if (gamemodeInGame) { Sgamemode.setTextureRect(IntRect(169, 0, 169, 39)); } // ЕСЛИ GAMEMODE = 1 ТО ПОКАЗЫВАЕТСЯ СПРАЙТ HARD

				window.clear();
				window.draw(Ssettingsmenu);
				window.draw(Sbackbutton);
				window.draw(Sgamemode);
				window.display();



			}
			// КОНЕЦ РАЗДЕЛА НАСТРОЕК


			window.draw(menuBg);

			window.draw(Sstartgamebutton);
			window.draw(Ssettingsbutton);
			window.draw(Sexitbutton);



			window.display();
		}
		

	
	window.clear();
}
