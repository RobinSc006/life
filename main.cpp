#include <SFML/Graphics.hpp>

#include <iostream>
#include <limits>

#include "cellManager.cpp"

int main()
{
    const int WIDTH = 780;
    const int HEIGHT = 780;

    const int UPDATE_INTERVAL_INCREMENT = 1;

    int keypress_cooldown = 10;
    int keypress_counter = 0;

    int update_counter = 0;
    int update_interval = 5;

    sf::Font font;
    if (!font.loadFromFile("assets/font/Recursive-Light.ttf"))
        std::cout << "unable to load font\n";

    sf::Text update_interval_display;
    sf::Text paused_display;
    sf::Text generations_display;

    update_interval_display.setFont(font);
    paused_display.setFont(font);
    generations_display.setFont(font);

    update_interval_display.setCharacterSize(11);
    paused_display.setCharacterSize(11);
    generations_display.setCharacterSize(11);

    update_interval_display.setPosition(10.0, 0.0);
    paused_display.setPosition(235.0, 0.0);
    generations_display.setPosition(125.0, 0.0);

    update_interval_display.setFillColor(sf::Color::White);
    paused_display.setFillColor(sf::Color::Red);
    generations_display.setFillColor(sf::Color::White);

    // ? Game parameters
    const sf::Color COLOR_WHITE = sf::Color(233, 233, 233, 255);
    const sf::Color COLOR_RED = sf::Color(255, 54, 54, 255);
    const sf::Color COLOR_GREEN_ONE = sf::Color(0, 245, 92, 255);
    const sf::Color COLOR_GREEN_TWO = sf::Color(135, 168, 144, 255);
    const sf::Color COLOR_BLUE = sf::Color(41, 38, 224, 233);
    const sf::Color CLEAR_COLOR = sf::Color(15, 15, 15, 233);

    const sf::Color SELECT_COLOR = sf::Color(242, 7, 152, 255);

    sf::Color current_color = COLOR_GREEN_TWO;

    bool update_paused = true;

    CellManager cell_manager;
    cell_manager.reset_cells(false);

    // ? R-pentomino
    cell_manager.cells[25 + 60][23 + 60].set_alive(true);
    cell_manager.cells[25 + 60][24 + 60].set_alive(true);
    cell_manager.cells[25 + 60][25 + 60].set_alive(true);

    cell_manager.cells[24 + 60][24 + 60].set_alive(true);
    cell_manager.cells[26 + 60][23 + 60].set_alive(true);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

    // ? Main loop
    while (window.isOpen())
    {
        update_interval_display.setString("Update interval: " + std::to_string(update_interval));
        generations_display.setString("Generations: " + std::to_string(cell_manager.get_generations()));
        if (update_paused)
            paused_display.setString("Paused");
        else
            paused_display.setString("");

        if (keypress_counter - 10 >= INT32_MAX)
            keypress_counter = 0;
        keypress_counter++;
        update_counter++;

        if (!update_paused && update_counter >= update_interval)
        {
            if(!cell_manager.update_cells()) update_paused = true;
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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                cell_manager.get_user_set_cells(window, true);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                cell_manager.get_user_set_cells(window, false);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && keypress_counter >= keypress_cooldown)
            {
                if (!update_paused)
                    update_paused = true;
                else
                    update_paused = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && keypress_counter >= keypress_cooldown)
            {
                cell_manager.reset_cells(false);
            }
        }

        window.clear(CLEAR_COLOR);

        cell_manager.render_cells(window, current_color);

        window.draw(update_interval_display);
        window.draw(paused_display);
        window.draw(generations_display);

        window.display();
    }

    return 0;
}