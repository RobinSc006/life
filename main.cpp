#include <SFML/Graphics.hpp>

#include <iostream>

#include "cellManager.cpp"

int main()
{
    const int WIDTH = 500;
    const int HEIGHT = 500;

    const int UPDATE_INTERVAL_INCREMENT = 100;
    int update_interval = 1000;
    int counter = 0;

    CellManager cell_manager;
    cell_manager.set_all_alive(false);

    // ? Cube
    /*
    cell_manager.cells[5][5].set_alive(true);
    cell_manager.cells[6][6].set_alive(true);
    cell_manager.cells[5][6].set_alive(true);
    cell_manager.cells[6][5].set_alive(true);
    */

    cell_manager.cells[5][5].set_alive(true);
    cell_manager.cells[6][5].set_alive(true);
    cell_manager.cells[7][5].set_alive(true);

    cell_manager.cells[4][6].set_alive(true);
    cell_manager.cells[5][6].set_alive(true);
    cell_manager.cells[6][6].set_alive(true);

    sf::RenderWindow window(sf::VideoMode(500, 500), "Game of Life");

    while (window.isOpen())
    {
        if (counter >= update_interval)
        {
            cell_manager.update_cells();
            counter = 0;
        }
        counter++;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                update_interval -= UPDATE_INTERVAL_INCREMENT;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                update_interval += UPDATE_INTERVAL_INCREMENT;
            }
        }

        window.clear();

        cell_manager.render_cells(window);
        window.display();
    }

    return 0;
}