#include <SFML/Graphics.hpp>

#include <iostream>

#include "cellManager.cpp"

int main()
{
    const int WIDTH = 500;
    const int HEIGHT = 500;

    int keypress_cooldown = 30;
    long long keypress_counter = 0;
    
    int update_counter = 0;
    int update_interval = 1000;

    CellManager cell_manager;
    cell_manager.set_all_alive(false);

    // ? Cube
    /*
    cell_manager.cells[5][5].set_alive(true);
    cell_manager.cells[6][6].set_alive(true);
    cell_manager.cells[5][6].set_alive(true);
    cell_manager.cells[6][5].set_alive(true);
    */

    // ? Oscillator
    /*
    cell_manager.cells[5][5].set_alive(true);
    cell_manager.cells[6][5].set_alive(true);
    cell_manager.cells[7][5].set_alive(true);

    cell_manager.cells[4][6].set_alive(true);
    cell_manager.cells[5][6].set_alive(true);
    cell_manager.cells[6][6].set_alive(true);
    */

    // ? Glider
    cell_manager.cells[5][5].set_alive(true);
    cell_manager.cells[6][5].set_alive(true);
    cell_manager.cells[7][5].set_alive(true);

    cell_manager.cells[7][4].set_alive(true);
    cell_manager.cells[6][3].set_alive(true);
    

    sf::RenderWindow window(sf::VideoMode(500, 500), "Game of Life");

    while (window.isOpen())
    {
        keypress_counter++;
        update_counter++;

        if (update_counter >= update_interval) {
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
                cell_manager.update_cells();
                keypress_counter = 0;
            }
        }

        window.clear();

        cell_manager.render_cells(window);
        window.display();
    }

    return 0;
}