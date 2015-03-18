#include <iostream>
#include <SFML/Graphics.hpp>

int main(void)
{
	std::cout << "Fractals. Here." << std::endl;

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	sf::RenderWindow window(modes[0], "Fractalou", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            switch( event.type )
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
            {
                window.clear();
                sf::CircleShape shape(10);
                shape.setPosition( event.mouseMove.x, event.mouseMove.y );
                shape.setFillColor(sf::Color::Green);
                window.draw(shape);
                break;
            }
            default:
                break;
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.draw(shape);
        window.display();
    }

	return 0;
}

