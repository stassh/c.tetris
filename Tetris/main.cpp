#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] = {
	1, 3, 5, 7,
	2, 4, 5, 7,
	3, 5, 5, 6,
	3, 5, 4, 7,
	2, 3, 5, 7,
	3, 5, 7, 6,
	2, 3, 4, 5,
};

int main() {
	RenderWindow window(VideoMode(320, 400), "The Game!");

	Texture t;
	t.loadFromFile("images/tiles.png");
	Sprite s(t);
	s.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Up) rotate = true;
				else if (e.key.code == Keyboard::Left) dx = -1;
				else if (e.key.code == Keyboard::Right) dx = 1;
			}
		}

		// move
		for (int i = 0; i < 4; i++)
		{
			a[i].x += dx;
		}


		// rotate
		if (rotate) {
			Point p = a[1];

			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;

				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
		}

		// tick
		if (timer > delay) {
			for (int i = 0; i < 4; i++)
			{	
				a[i].y += 1;
			}
			timer = 0;
		}


		int n = 3;
		if (a[0].x==0)
		for (int i = 0; i < 4; i++) {
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}

		dx = 0; rotate = 0;

		window.clear(Color::White);

		for (int i = 0; i < 4; i++) {
			s.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(s);
		}

		window.display();
	}
	return 0;
}

