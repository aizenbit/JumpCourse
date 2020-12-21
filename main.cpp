#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include "menu.h"
#include "menugame.h"
#include <iostream>


using namespace sf;
using namespace std;

float offsetX = 0, offsetY = 0;



class PLAYER {

public:

	float dx, dy;
	FloatRect rect;
	bool onGround, FlipRight = false, FlipLeft = false, Slip = false, SoundRL = false, SloopR = false, Rpos = true;
	Sprite sprite;
	float currentFrame;

	PLAYER(Texture& image)
	{
		sprite.setTexture(image);
		rect = FloatRect(6 * 64, 190 * 64, 64, 64);  // 8 130 // 6 190  // 10 100
		dx = dy = 0;
		currentFrame = 0;
	}

	void update(float time)
	{
		rect.left += dx * time;
		Collision(0);
		if (!onGround) dy = dy + 0.0005f * time;
		if (!onGround) Slip = false;
		rect.top += dy * time;
		onGround = false;
		Collision(1);
		if (onGround)
		{
			FlipRight = false;
		}
		if (onGround)
		{
			FlipLeft = false;
		}

		currentFrame += 0.007f * time;
		if (currentFrame > 3) currentFrame -= 3;

		if (dx < 0 && dy == 0) sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 0, -64, 64));
		if (dx > 0 && dy == 0) sprite.setTextureRect(IntRect(64 * int(currentFrame), 0, 64, 64));
		if (dx == 0 && dy == 0 && Rpos) sprite.setTextureRect(IntRect(64 * int(currentFrame), 64, 64, 64));
		if (dx == 0 && dy == 0 && !Rpos) sprite.setTextureRect(IntRect(64 * int(currentFrame) +64, 64, -64, 64));
		if (dx > 0 && dy < 0) sprite.setTextureRect(IntRect(64 * int(currentFrame), 192, 64, 64));
		if (dx < 0 && dy < 0) sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 192, -64, 64));
		if (dx > 0 && dy > 0.01) sprite.setTextureRect(IntRect(64 * int(currentFrame), 256, 64, 64));
		if (dx < 0 && dy > 0.01) sprite.setTextureRect(IntRect(64 * int(currentFrame) + 64, 256, -64, 64));
		if (Keyboard::isKeyPressed(Keyboard::Space) && dy == 0) sprite.setTextureRect(IntRect(64 * int(currentFrame), 128, 64, 64));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}

	void Collision(int dir)
	{
		for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
			{
  				if (TileMap[i][j] == 'C' || TileMap[i][j] == 'A' || TileMap[i][j] == 'S' || TileMap[i][j] == 'D' || TileMap[i][j] == 'F' || TileMap[i][j] == 'G')
				{
					if ((dx > 0) && (dir == 0)) { rect.left = j * 64 - rect.width; FlipRight = true; SoundRL = true; }
					if (FlipRight) { FlipLeft = false; }
					if ((dx < 0) && (dir == 0)) { rect.left = j * 64 + 64; FlipLeft = true; SoundRL = true; }
					if (FlipLeft) { FlipRight = false; }
					if ((dy > 0) && (dir == 1)) { rect.top = i * 64 - rect.height;  dy = 0;  onGround = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 64 + 64;   dy = 0; }
					SloopR = false;
					Slip = true;
				}
			}
		for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
			for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
			{
				if (TileMap[i][j] == 'R')
				{

					if (dy > 0) { SloopR = true; }

				}
				if (TileMap[i][j] == 'O')
				{

					if ((dx > 0) && (dir == 0)) { rect.left = j * 64 - rect.width; FlipRight = true; SoundRL = true; }
					if (FlipRight) { FlipLeft = false; }
					if ((dx < 0) && (dir == 0)) { rect.left = j * 64 + 64; FlipLeft = true; SoundRL = true; }
					if (FlipLeft) { FlipRight = false; }
					if ((dy > 0) && (dir == 1)) { rect.top = i * 64 - rect.height;  dy = 0; SloopR = true; }
					if ((dy < 0) && (dir == 1)) { rect.top = i * 64 + 64;   dy = 0; }
					Slip = true;
				}
				if (TileMap[i][j] == ' ')
				{
					SloopR = false;
				}
			}
	}
};

class Object {
public:

	float dx, dy, h, w;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;

	Object(Texture& image)
	{
		sprite.setTexture(image);
		rect = FloatRect();
		dx = dy = 0;
		currentFrame = 0;
	}

	void update(float time)
	{
		currentFrame += 0.007f * time;
		if (currentFrame > 4) currentFrame -= 4;
		if (dx == 0 && dy == 0) sprite.setTextureRect(IntRect(w * int(currentFrame), h, rect.width, rect.height));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
		dy = 0;
	}

};



int main()
{
	RenderWindow window(VideoMode(1280, 768), "Jump Dick"); // 1280x768 = 20x12*5= 20x60
	

	Clock clock;

	








	RectangleShape soundbottom(Vector2f(40, 40));
	soundbottom.setPosition(1230, 10);
	

	// ТЕКСТУРЫ

	Texture t;
	t.loadFromFile("texture/player.png");
	//t.setSmooth(true);

	Texture f;
	f.loadFromFile("map/fire2.png");

	Texture tor;
	tor.loadFromFile("map/torch.png");

	Texture mon;
	mon.loadFromFile("map/monster.png");

	Texture sou;
	sou.loadFromFile("texture/sound.png");
	soundbottom.setTexture(&sou);
	soundbottom.setTextureRect(IntRect(0, 0, 40, 40));


	Texture map;
	map.loadFromFile("map/map.png");
	Sprite map1;
	map1.setTexture(map);

	// ---------------------------------------------------------	
	sf::Texture texwater;
	texwater.loadFromFile("texture/water.png");
	texwater.setRepeated(true);
	sf::RectangleShape water(sf::Vector2f(1280 * 3, 64));
	water.setTexture(&texwater);
	water.setPosition(0, 704);
	float waterSpeed = 0.01f;

	float currentFrame = 0;
	PLAYER p(t);

	Object fire(f);
	fire.rect.top = 190 * 64;
	fire.rect.left = 9 * 64;
	fire.rect.width = 64;
	fire.rect.height = 64;
	fire.w = 64;
	fire.h = 0;

	Object torch(tor);
	torch.rect.top = 152 * 64;
	torch.rect.left = 8 * 64;
	torch.rect.width = 64;
	torch.rect.height = 64;
	torch.w = 64;
	torch.h = 0;

	Object torch2(tor);
	torch2.rect.top = 152 * 64;
	torch2.rect.left = 13 * 64;
	torch2.rect.width = 64;
	torch2.rect.height = 64;
	torch2.w = 64;
	torch2.h = 0;

	Object torch3(tor);
	torch3.rect.top = 152 * 64;
	torch3.rect.left = 17 * 64;
	torch3.rect.width = 64;
	torch3.rect.height = 64;
	torch3.w = 64;
	torch3.h = 0;

	Object monster(mon);
	monster.rect.top = 190 * 64;
	monster.rect.left = 14 * 64;
	monster.rect.width = 64;
	monster.rect.height = 64;
	monster.w = 64;
	monster.h = 0;

	// ---------------------------------------------------------
	// ЗВУКИ

	SoundBuffer jumpbuffer2;
	jumpbuffer2.loadFromFile("sounds/jump2.ogg");
	Sound jump(jumpbuffer2);
	jump.setVolume(40.f);

	SoundBuffer jumpbuffer;
	jumpbuffer.loadFromFile("sounds/jump.ogg"); // ПРЫЖОК
	Sound jump2(jumpbuffer2);
	jump2.setVolume(40.f);

	SoundBuffer bitbuffer;
	bitbuffer.loadFromFile("sounds/bit2.ogg"); // УДАР ОБ СТЕНУ
	Sound bit(bitbuffer);
	bit.setVolume(20.f);

	SoundBuffer groundbuffer;
	groundbuffer.loadFromFile("sounds/ground2.ogg"); // УДАР ОБ ЗЕМЛЮ
	Sound ground(groundbuffer);
	ground.setVolume(25.f);

	sf::SoundBuffer camp;
	camp.loadFromFile("sounds/campfire.ogg");
	Sound campfire(camp);
	campfire.setVolume(50.f);
	campfire.setLoop(true);

	Music music;
	music.openFromFile("sounds/gamemusic2.ogg"); // ФОНОВАЯ МУЗЫКА
	music.setLoop(true);
	


	

	// ---------------------------------------------------------

	float MoveRL, SpaceDelay, PressingTime, MaxJump;
	bool Right, Jump, SpaceJ, RightDown, LeftDown, SoundG, Test, Motion, SoundGame;
	MoveRL = 1;
	Right = true;
	Jump = false;
	Test = false;
	SpaceJ = false;
	MaxJump = false;
	RightDown = false;
	LeftDown = false;
	SoundG = false;
	SoundGame = true;
	
	PressingTime = 0.03f;
	Motion = true;

	

	/*
	bool Test2 = Motion;
	if (Motion) { cout << "1" << endl; };
	if (!Motion) { cout << "2" << endl; };
	if (Test2) { cout << "3" << endl; };
	if (!Test2) { cout << "4" << endl; };
	*/
	menu(window);

	music.play();


	
	while (window.isOpen())
	{
		// Параметры времени
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;



		//if (Keyboard::isKeyPressed(Keyboard::Tab)) {  sleep;}

		// ---------------------------------------------------------
		Vector2i mousePosition = Mouse::getPosition(window);
		// Открытие закрытие окна игры


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					if (soundbottom.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						if (SoundGame) {  soundbottom.setTextureRect(IntRect(120, 0, 40, 40)); }
						else if (!SoundGame) {soundbottom.setTextureRect(IntRect(40, 0, 40, 40));}
					}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					if (soundbottom.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
						if (SoundGame) { SoundGame = false;	}
						else if (!SoundGame) { SoundGame = true; }
					}
		}
		if (!Mouse::isButtonPressed(Mouse::Left)) {
			if (SoundGame) { soundbottom.setTextureRect(IntRect(0, 0, 40, 40)); }
			if (!SoundGame) { soundbottom.setTextureRect(IntRect(80, 0, 40, 40)); }
			if (SoundGame && soundbottom.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				soundbottom.setTextureRect(IntRect(160, 0, 40, 40));
			}
			if (!SoundGame && soundbottom.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
				soundbottom.setTextureRect(IntRect(200, 0, 40, 40));
			}
		}
		if (SoundGame) { music.setVolume(50.f); }
		if (!SoundGame) { music.setVolume(0.f); }



		// ---------------------------------------------------------
		// Код движение влево вправо

		if (Keyboard::isKeyPressed(Keyboard::A) & !Keyboard::isKeyPressed(Keyboard::D))
		{
			if (!p.onGround) { MoveRL = 0; };
			if (p.onGround & !SpaceJ) { MoveRL = 1; };
			if (Motion) { p.dx = -0.27f * MoveRL; }
			if (p.onGround) { Right = false; }
		}
		if (Keyboard::isKeyPressed(Keyboard::D) & !Keyboard::isKeyPressed(Keyboard::A))
		{
			if (!p.onGround) { MoveRL = 0.f; };
			if (p.onGround & !SpaceJ) { MoveRL = 1.f; };
			if (Motion) { p.dx = 0.27f * MoveRL; }
			if (p.onGround) { Right = true; }
		}

		// ---------------------------------------------------------
		// Код пробела

		if (!MaxJump) {
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (p.onGround) { SpaceJ = true; }
				SpaceDelay = 0;
				PressingTime = PressingTime + 1.9f * time/1000;
				if (PressingTime > 1.5f) { PressingTime = 1.5f; MaxJump = true; }
			}
		}

		if (SpaceJ & !Keyboard::isKeyPressed(Keyboard::Space) || MaxJump)
		{
			if (p.onGround) {
				p.dy = -0.4f * PressingTime; p.onGround = false; jump.play();}
			if (!p.onGround) { Jump = true; }
			SpaceDelay = SpaceDelay + 1.f*time;
			if (SpaceDelay > 10.f) { SpaceJ = false; }
			if (!SpaceJ) { PressingTime = 0.03f; }
			if (!SpaceJ || p.dy < 0.f) { MaxJump = false; }
		}
		// ---------------------------------------------------------
		// Если персонаж приземляется, то переменная "прыжок" принимает значение "выключен"
		if (p.onGround) { Jump = false; }
		// ---------------------------------------------------------
		// Если персонаж повернут вправо/влево и был совершен прыжок, то он будет в полете двигаться в том направлении по оси dx
		if (Jump & Right) { p.dx = 0.25f; }
		if (Jump & !Right) { p.dx = -0.25f; }
		// ---------------------------------------------------------
		// Если персонаж ударяется об вертикальную стену и приземляется в обратном направлении, то значение его поворота относительно dx отражается.
		if (p.FlipRight & Jump) { Right = false; }
		if (p.FlipLeft & Jump) { Right = true; }


		// ---------------------------------------------------------
		//  Если персонаж пересекает границу блока при нажатой клавише D он подает вниз с ускорением по dx +

		// ---------------------------------------------------------
		//  Если персонаж пересекает границу блока при нажатой клавише D он подает вниз с ускорением по dx -
		if (p.Slip & Motion) {
			if (Keyboard::isKeyPressed(Keyboard::A) && !SpaceJ && !Keyboard::isKeyPressed(Keyboard::D)) {
				LeftDown = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::D) && !SpaceJ && !Keyboard::isKeyPressed(Keyboard::A)) {
				RightDown = true;
			}
		}
		if (LeftDown && !p.onGround) { p.dx = p.dx -0.12f; }
		if (RightDown && !p.onGround) { p.dx = p.dx + 0.12f; }
		if (p.onGround) { RightDown = false; LeftDown = false; }

		// ---------------------------------------------------------
		// ЗВУКИ УДАРОВ ОБ ПОЛ И СТЕНУ

		if (p.SoundRL & Jump) { bit.play(); p.SoundRL = false; }
		if (Jump) { SoundG = true; }
		if (SoundG & !Jump) { SoundG = false; ground.play(); }

		// ---------------------------------------------------------
		if (p.SloopR) { p.dx = -0.25f; p.dy = 0.25f; LeftDown = true; }

		// ПЕРЕМЕЩЕНИЕ КАМЕРЫ ( 768 1536 2304 3072 3840 4608 )

		offsetY = 11520;
		if (p.rect.top < 11456) { offsetY = 10752; }
		if (p.rect.top < 10624) { offsetY = 9984; }
		if (p.rect.top < 9984) { offsetY = 9216; }
		if (p.rect.top < 9216) { offsetY = 8448; }
		if (p.rect.top < 8448) { offsetY = 7680; }
		if (p.rect.top < 7680) { offsetY = 6912; }
		if (p.rect.top < 6912) { offsetY = 6144; }
		if (p.rect.top < 6144) { offsetY = 5376; }
		if (p.rect.top < 5376) { offsetY = 4608; }
		if (p.rect.top < 4608) { offsetY = 3840; }
		//if (p.rect.left > 1216) { offsetX = 320;  }
		//if (p.rect.left < 1280) { }
		// ---------------------------------------------------------
		if (Right) { p.Rpos = true; }
		if (!Right) { p.Rpos = false;  }

		if ((LeftDown || RightDown) && p.dy > 0.005f) { Test = true; }
		if (Test && p.onGround) { ground.play(); Test = false; }

		if (water.getPosition().x < -1280) {
			water.setPosition(0, water.getPosition().y);
		}
		water.move(-waterSpeed, 0);


		fire.update(time);
		torch.update(time);
		torch2.update(time);
		torch3.update(time);
		monster.update(time / 16);
		p.update(time);

		window.clear(Color::Black);

		// Отрисовка карты, координаты тайтлов
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{

				if (TileMap[i][j] == 'A') map1.setTextureRect(IntRect(0, 11520, 1280, 768));

				if (TileMap[i][j] == 'S') map1.setTextureRect(IntRect(0, 10752, 1280, 768));

				if (TileMap[i][j] == 'D') map1.setTextureRect(IntRect(0, 9984, 1280, 768));

				if (TileMap[i][j] == 'F') map1.setTextureRect(IntRect(0, 9216, 1280, 768));

				if (TileMap[i][j] == 'G') map1.setTextureRect(IntRect(0, 8448, 1280, 768));

				if (TileMap[i][j] == 'H') map1.setTextureRect(IntRect(0, 7680, 1280, 768));

				if (TileMap[i][j] == 'J') map1.setTextureRect(IntRect(0, 6912, 1280, 768));

				if (TileMap[i][j] == 'K') map1.setTextureRect(IntRect(0, 6144, 1280, 768));

				if (TileMap[i][j] == 'L') map1.setTextureRect(IntRect(0, 5376, 1280, 768));

				if (TileMap[i][j] == 'Z') map1.setTextureRect(IntRect(0, 4608, 1280, 768));

				if (TileMap[i][j] == 'X') map1.setTextureRect(IntRect(0, 3840, 1280, 768));

				if (TileMap[i][j] == 'R') continue;

				if (TileMap[i][j] == 'O') continue;

				if (TileMap[i][j] == 'C') continue;

				if (TileMap[i][j] == ' ') continue;

				map1.setPosition(j * 64 - offsetX, i * 64 - offsetY);

				window.draw(map1);

			}
		// ---------------------------------------------------------

		if (p.rect.top > 11456) { window.draw(water); }
		window.draw(fire.sprite);
		window.draw(torch.sprite);
		window.draw(torch2.sprite);
		window.draw(torch3.sprite);
		window.draw(monster.sprite);

		window.draw(p.sprite);

		window.draw(soundbottom);

		window.display();



	}

	return 0;
}
