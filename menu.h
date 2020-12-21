#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;




void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuTexture3, menuBack, aboutTexture, menuBackground, startTexture, hardTexture, easyTexture, gmTexture;

	menuTexture1.loadFromFile("menu/startgame.png");
	menuTexture2.loadFromFile("menu/settings.png");
	menuTexture3.loadFromFile("menu/exit.png");
	menuBack.loadFromFile("menu/back.png");
	aboutTexture.loadFromFile("menu/settingsmenu2.png");
	menuBackground.loadFromFile("menu/backgroundMenu2.png");
	startTexture.loadFromFile("menu/startmenu.png");
	hardTexture.loadFromFile("menu/hard.png");
	easyTexture.loadFromFile("menu/easy.png");
	gmTexture.loadFromFile("menu/gamemode.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), back(menuBack), about(aboutTexture), menuBg(menuBackground), startmenu(startTexture), hard(hardTexture), easy(easyTexture), gm(gmTexture);
	bool isMenu = 1, start = 1, Set = 0;
	bool gamemode = false, MousePressed = false;
	int menuNum = 0;
	menu1.setPosition(555, 350);
	menu2.setPosition(555, 400);
	menu3.setPosition(555, 450);
	back.setPosition(555, 650);
	hard.setPosition(555, 450);
	easy.setPosition(555, 550);
	gm.setPosition(555, 450);
	menuBg.setPosition(0, 0);
	startmenu.setPosition(0, 0);



	Music music;
	music.openFromFile("sounds/menu.ogg");
	music.setVolume(5.f);
	music.play();
	music.setLoop(true);

	SoundBuffer clickbuffer;
	clickbuffer.loadFromFile("sounds/click.ogg");
	Sound click(clickbuffer);
	click.setVolume(50.f);
	while (start) {


		if (Keyboard::isKeyPressed(Keyboard::Space)) { isMenu = 1; start = 0; click.play(); }
		window.clear();
		window.draw(startmenu);
		window.display();
	}

	while (isMenu)
	{

		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);

		menuNum = 0;

		window.clear(Color(129, 181, 221));



		if (!Keyboard::isKeyPressed(Keyboard::Escape)) { isMenu = 1; }



		if (IntRect(555, 350, 169, 39).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Red); menuNum = 1; }
		if (IntRect(555, 400, 169, 39).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Red); menuNum = 2; }
		if (IntRect(555, 450, 169, 39).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Red); menuNum = 3; }


		if (Mouse::isButtonPressed(Mouse::Left))
		{

			if (menuNum == 1) {
				click.play();

				isMenu = false;
			}
			if (menuNum == 2) {
				click.play();
				Set = 1;
				isMenu = false;



			}
			if (menuNum == 3) { click.play(); window.close(); isMenu = false; }

		}
		while (Set) {
			back.setColor(Color::White);
			if (IntRect(555, 650, 169, 39).contains(Mouse::getPosition(window))) {
				back.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					click.play();
					Set = 0;
					isMenu = 1;
				}
			}
			gm.setColor(Color::White);
			if (IntRect(555, 450, 169, 39).contains(Mouse::getPosition(window)))
			{
				gm.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					MousePressed = true;
				}
				if (!Mouse::isButtonPressed(Mouse::Left) && MousePressed) {
					if (MousePressed) { click.play(); }
					if (gamemode) { gamemode = false; MousePressed = false; }
					else if (!gamemode) { gamemode = true; MousePressed = false; }
				}
			}



			if (!gamemode) { gm.setTextureRect(IntRect(0, 0, 169, 39)); }
			if (gamemode) { gm.setTextureRect(IntRect(169, 0, 169, 39)); }
			
			window.clear();

			window.draw(about);
			window.draw(back);
			window.draw(gm);

			window.display();
		}

		window.clear();

		window.draw(menuBg);

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
