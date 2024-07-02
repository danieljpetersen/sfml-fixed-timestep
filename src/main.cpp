#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

////////////////////////////////////////////////////////////

int main()
{
	sf::Clock clock;
	const double tickDeltaTime = 1.0 / 20.0; // 20 ticks per second
	double elapsedTime = clock.getElapsedTime().asSeconds();
	double accumulator = 0.0;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
	window.setVerticalSyncEnabled(true);

	sf::CircleShape shape(20.f);
	sf::Vector2f shapePosition = shape.getPosition();
	sf::Vector2f shapePreviousPosition = shape.getPosition();

	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::A))
				{
					moveLeft = true;
				}
				if ((event.key.code == sf::Keyboard::Right) || (event.key.code == sf::Keyboard::D))
				{
					moveRight = true;
				}
				if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W))
				{
					moveUp = true;
				}
				if ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S))
				{
					moveDown = true;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::A))
				{
					moveLeft = false;
				}
				if ((event.key.code == sf::Keyboard::Right) || (event.key.code == sf::Keyboard::D))
				{
					moveRight = false;
				}
				if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W))
				{
					moveUp = false;
				}
				if ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S))
				{
					moveDown = false;
				}
			}
		}

		double newTime = clock.getElapsedTime().asSeconds();
		double frameTime = newTime - elapsedTime;
    	if (frameTime > 0.25)
    	{
    		frameTime = 0.25;
    	}
		elapsedTime = newTime;
		accumulator += frameTime;

		int stepCount = 0;
		while (accumulator >= tickDeltaTime)
		{
			stepCount++;
			accumulator -= tickDeltaTime;
		}

		for (int i = 0; i < stepCount; i++)
		{
            shapePreviousPosition = shapePosition;

			const int movementAmount = 5;
			if (moveLeft)
			{
				shapePosition.x -= movementAmount;
			}

			if (moveRight)
			{
				shapePosition.x += movementAmount;
			}

			if (moveUp)
			{
				shapePosition.y -= movementAmount;
			}

			if (moveDown)
			{
				shapePosition.y += movementAmount;
			}
		}

		const double alpha = accumulator / tickDeltaTime;
		sf::Vector2f interpolated = sf::Vector2f(0,0);
		interpolated.x = shapePosition.x * alpha + shapePreviousPosition.x * (1.0 - alpha );
		interpolated.y = shapePosition.y * alpha + shapePreviousPosition.y * (1.0 - alpha );
		shape.setPosition(interpolated);

		window.clear();
		window.draw(shape);
		window.display();

		std::stringstream ss;
		ss << 1.0f / frameTime;
		window.setTitle(ss.str());
	}

	return 0;
}
