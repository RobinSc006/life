#include <SFML/Graphics.hpp>

#include <iostream>
#include <limits>

#include "cellManager.cpp"

int main()
{
    const int WIDTH = 790;
    const int HEIGHT = 790;

    const int UPDATE_INTERVAL_INCREMENT = 1;

    int keypress_cooldown = 30;
    int keypress_counter = 0;

    int update_counter = 0;
    int update_interval = 5;

    // ? Game parameters
    sf::Color COLOR_WHITE = sf::Color(233, 233, 233, 255);
    sf::Color COLOR_RED = sf::Color(255, 54, 54, 255);
    sf::Color COLOR_GREEN_ONE = sf::Color(0, 245, 92, 255);
    sf::Color COLOR_GREEN_TWO = sf::Color(135, 168, 144, 255);
    sf::Color COLOR_BLUE = sf::Color(41, 38, 224, 233);

    sf::Color current_color = COLOR_GREEN_TWO;

    CellManager cell_manager;
    cell_manager.set_all_alive(false);

    // ? R-pentomino
    cell_manager.cells[25 + 60][23 + 60].set_alive(true);
    cell_manager.cells[25 + 60][24 + 60].set_alive(true);
    cell_manager.cells[25 + 60][25 + 60].set_alive(true);

    cell_manager.cells[24 + 60][24 + 60].set_alive(true);
    cell_manager.cells[26 + 60][23 + 60].set_alive(true);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

    while (window.isOpen())
    {
        if (keypress_counter - 10 >= INT32_MAX)
            keypress_counter = 0;
        keypress_counter++;
        update_counter++;

        if (update_counter >= update_interval)
        {
            cell_manager.update_cells();
            update_counter = 0;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && keypress_counter >= keypress_cooldown)
            {
                update_interval -= UPDATE_INTERVAL_INCREMENT;
                keypress_counter = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && keypress_counter >= keypress_cooldown)
            {
                update_interval += UPDATE_INTERVAL_INCREMENT;
                keypress_counter = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && keypress_counter >= keypress_cooldown)
            {
                current_color = COLOR_WHITE;
                keypress_counter = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && keypress_counter >= keypress_cooldown)
            {
                current_color = COLOR_RED;
                keypress_counter = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && keypress_counter >= keypress_cooldown)
            {
                current_color = COLOR_GREEN_ONE;
                keypress_counter = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && keypress_counter >= keypress_cooldown)
            {
                current_color = COLOR_GREEN_TWO;
                keypress_counter = 0;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && keypress_counter >= keypress_cooldown)
            {
                current_color = COLOR_BLUE;
                keypress_counter = 0;
            }
        }

        window.clear();

        cell_manager.render_cells(window, current_color);
        window.display();
    }

    return 0;
}