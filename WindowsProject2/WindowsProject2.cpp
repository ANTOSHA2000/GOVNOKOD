#include <SFML/Graphics.hpp>
using namespace sf;

//класс астероида
class Asteroid
{
public:
	//характеристики астероида
	float x, y;
	float ax = 0, ay = 0;
	int size;
	int points;
	float speed = 0.1;
	CircleShape asteroid;

	//констуктор класса
	Asteroid(float X, float Y, int SIZE, int POINTS)
	{
		x = X;
		y = Y;
		size = SIZE;
		points = POINTS;

		//создаем спрайт астероида
		asteroid.setRadius(size);
		asteroid.setPointCount(points);
		asteroid.setFillColor(Color::Black);
		asteroid.setOutlineColor(Color::White);
		asteroid.setOutlineThickness(3);

		asteroid.setPosition(x, y);

	}
	//функция, отвечающая за создание астероидов
	public:void drawAsteroids()
	{
		ax += 0.1;
		ay += 0.1;

		x += ax;
		y += ay;

		if (x >= 600 || x <= 0) ax = -ax;
		if (y >= 400 || y <= 0) ay = -ay;
		
		asteroid.setPosition(x, y);
	}
};

int main()
{
	//рисуем окно
	RenderWindow app(VideoMode(600, 400), "Game");
	app.setFramerateLimit(60);

	//у корабля:угол поворота, наличие тяги, позиция и скорость соответственно
	float angle = 0;
	bool thrust = false;
	float x = 300, y = 200;
	float dx = 0, dy = 0;
	float speed = 0;
	bool shoot = false;

	//максимальная скорость
	float maxSpeed = 10;

	float radians = 0.017453;
	
	CircleShape ship;
	// Установка радиуса
	ship.setRadius(10);
	// Установка количества точек
	ship.setPointCount(3);
	// Цвет рамки
	ship.setOutlineColor(Color::White);
	// Толщина рамки
	ship.setOutlineThickness(2);
	// Установка позиции
	ship.setPosition(300, 200);
	// Цвет заливки
	ship.setFillColor(Color::Black);
	//ставим центр корабля
	ship.setOrigin(10, 10);
	ship.setScale(0.7, 1);

	//создаем обьект класса астероида
	Asteroid asteroid(100.0, 100.0, 15, 5);

	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				app.close();
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			angle -= 3;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			angle += 3;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			thrust = true;
		}
		else thrust = false;

		//проверка наличия тяги
		if (thrust)
		{
			dx += cos(angle*radians)*0.2;
			dy += sin(angle*radians)*0.2;
		}
		else
		{
			dx *= 0.99;
			dy *= 0.99;
		}

		speed = sqrt(dx * dx + dy * dy);

		if (speed > maxSpeed)
		{
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
		}

		//вычисляем икс и игрек
		x += dx;
		y += dy;

		//проверяем: корабль вышел за пределы игрового пространства?
		if (x > 600) x = 0;
		if (x < 0) x = 600;

		if (y > 400) y = 0;
		if (y < 0) y = 400;

		//перемещаем корабль
		ship.setPosition(x, y);

        //непосредственно сам поворот
        ship.setRotation(angle+90);

		asteroid.drawAsteroids();

		app.clear(Color::Black);
		app.draw(ship);
		app.draw(asteroid.asteroid);
		app.display();
	}
}