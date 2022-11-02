#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
int N=30,M=20;
int size=18;
int w = size*N;
int h = size*M;
int score = 0;

int dir,num=4;

struct Snake
{ int x,y;}  s[100];

struct Fruit
{ int x,y;} f;


int main()
{
    sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game!");

    //sound
        sf::SoundBuffer losing;
		losing.loadFromFile("losing.wav");
		sf::Sound losingsound;
		losingsound.setBuffer(losing);
		losingsound.setPlayingOffset(sf::seconds(1));
		sf::SoundBuffer eating;
		eating.loadFromFile("eating.wav");
		sf::Sound eatingsound;
		eatingsound.setBuffer(eating);
		eatingsound.setPlayingOffset(sf::seconds(2));

        //textures
    sf::Texture t2,t3;

    t2.loadFromFile("images/Red.png");
    t3.loadFromFile("background2.jpg");

    sf::Sprite sprite2(t2);
    sf::Sprite sprite3(t3);
    //fonts and texts
    sf::Font font;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::Black);
	font.loadFromFile("arial.ttf");
    sf::Text gameoverText;
	gameoverText.setFont(font);
	gameoverText.setString("Game Over!");
	gameoverText.setCharacterSize(60);
	gameoverText.setPosition(80,80);
	gameoverText.setFillColor(sf::Color::Blue);
	sf::RectangleShape gameoverBackground(sf::Vector2f(700, 700));
	gameoverBackground.setFillColor(sf::Color::Black);

    sf::Clock clock;

    float timer=0, delay=0.1;

    f.x=10;
    f.y=10;
    start:
    while (window.isOpen())
    {   scoreText.setPosition(1,1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir != 2) dir=1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir != 1) dir=2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir != 0) dir=3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&& dir != 3) dir=0;

        if (timer>delay) {timer=0;

        for (int i=num;i>0;--i)
     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}

    if (dir==0) s[0].y+=1;
    if (dir==1) s[0].x-=1;
    if (dir==2) s[0].x+=1;
    if (dir==3) s[0].y-=1;

    if ((s[0].x==f.x) && (s[0].y==f.y))
     {num++; f.x=rand()%N; f.y=rand()%M;
     score += 1;
     eatingsound.play();
    scoreText.setString("Score: " + std::to_string(score));
     }

    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;

    for (int i=1;i<num;i++){

     if (s[0].x==s[i].x && s[0].y==s[i].y)
     {  losingsound.play();
         goto gameover;
     }

        }}


   ////// draw  ///////
    window.clear();
    window.draw(sprite3);

        window.draw(scoreText);

    for (int i=0;i<num;i++)
        { sprite2.setPosition(s[i].x*size, s[i].y*size);  window.draw(sprite2); }

    sprite2.setPosition(f.x*size, f.y*size);  window.draw(sprite2);

    window.display();
    }
    gameover:
while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
        window.draw(gameoverBackground);
		window.draw(gameoverText);
		window.draw(scoreText);
		scoreText.setPosition(120,140);
		scoreText.setFillColor(sf::Color::Blue);
		window.display();
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                scoreText.setFillColor(sf::Color::Black);
                score=0;
                scoreText.setString("Score: " + std::to_string(0));
                   int number=4;
                for (int z=number;z>0;--z)
                    {s[z].x= s[z-1].x;
                     s[z].y= s[z-1].y;}
                     window.close();

                    main();
                goto start;}*/
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

	}


    return 0;
}
