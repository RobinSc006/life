#include <SFML/Graphics.hpp>
#include <iostream>

class Cell
{
private:
    const sf::Color COLOR_ALIVE = sf::Color(0, 245, 92, 255); 
    const sf::Color COLOR_DEAD = sf::Color(33, 33, 33, 255);

    int size = 4;
    bool alive = false;
    bool die_next_turn = false;
    bool live_next_turn = false;
    sf::RectangleShape shape;

public:
    void set_die_next_turn(bool val)
    {
        die_next_turn = val;
    }
    bool get_die_next_turn()
    {
        return die_next_turn;
    }
    void set_live_next_turn(bool val)
    {
        live_next_turn = val;
    }
    bool get_live_next_turn()
    {
        return live_next_turn;
    }
    bool is_alive()
    {
        return alive;
    }
    void set_alive(bool val)
    {
        alive = val;
    }
    int get_size()
    {
        return size;
    }

    sf::RectangleShape render(int grid_x, int grid_y, sf::Color color)
    {
        shape.setSize(sf::Vector2f(size, size));
        if (alive)
            shape.setFillColor(color);
        else
            shape.setFillColor(COLOR_DEAD);

        shape.setPosition(grid_x, grid_y);

        return shape;
    }
};