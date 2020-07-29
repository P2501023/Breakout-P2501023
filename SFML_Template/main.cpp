#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main() {
	srand(time(0));

	RenderWindow app(VideoMode(520, 450), "Breakout");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");

	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 440);

	Sprite block[1000];

	int menu = 1;
	int lose = 0;
	int win = 0;
	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++) {
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}


	float dx = 6, dy = 5;
	float x = 300, y = 300;

	sf::Text text;
	text.setString("You Lose");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"));
	text.setCharacterSize(34);
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setPosition(190, 250);

	sf::Text text2;
	text2.setString("Press Space");
	text2.setCharacterSize(15);
	text2.setFont(font);
	text2.setFillColor(sf::Color::Red);
	text2.setPosition(205, 295);



	while (app.isOpen()) {
		Event e;
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

		if (lose || win || menu) {
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				dx = 6;
				dy = 5;
				x = 300;
				y = 300;

				lose = 0;

				int n = 0;
				for (int i = 1; i <= 10; i++)
					for (int j = 1; j <= 10; j++) {
						block[n].setPosition(i * 43, j * 20);
						n++;
					}
				win = 0;
				menu = 0;
			};
		}
		else {
			x += dx;
			for (int i = 0; i < n; i++)
				if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds())) {
					block[i].setPosition(-100, 0); dx = -dx;
				}

			y += dy;
			for (int i = 0; i < n; i++)
				if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds())) {
					block[i].setPosition(-100, 0); dy = -dy;
				}

			if (x < 0 || x>520)  dx = -dx;
			if (y < 0)  dy = -dy;

			if (y > 450) {
				text.setString("You lose");
				text.setPosition(180, 250);
				lose = 1;
			}
			else 
			{	text.setString("You Win");
			text.setPosition(195, 250);
			}

			if (Keyboard::isKeyPressed(Keyboard::Right)) {

				if (sPaddle.getPosition().x < 430)  sPaddle.move(8, 0);
			};
			if (Keyboard::isKeyPressed(Keyboard::Left)) {

				if (sPaddle.getPosition().x > 0)  sPaddle.move(-8, 0);
			};

			if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) dy = -(rand() % 5 + 2);

			sBall.setPosition(x, y);

			win = 1;
			for (int i = 0; i < n; i++) {
				if (block[i].getPosition().x != -100) {
					win = 0;

	
					break;
				}
			}
		}
		if (menu) {
			text.setString("Main Menu");
			text.setPosition(165, 250);
		}

		app.clear();

		app.draw(sBackground);
		app.draw(sBall);
		app.draw(sPaddle);


		for (int i = 0; i < n; i++)
			app.draw(block[i]);

		if (lose || win || menu) app.draw(text);
		if (lose || win || menu) app.draw(text2);

		app.display();
	}

	return 0;
}
