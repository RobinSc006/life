#include <SFML/Graphics.hpp>
#include "cell.cpp"

class CellManager
{
private:
    const int MIN_CONNECTED = 2;
    const int MAX_CONNECTED = 3;

public:
    static const int GRID_WIDTH = 152;
    static const int GRID_HEIGHT = 152;
    Cell cells[GRID_WIDTH][GRID_HEIGHT];

    const int GRID_SEPERATOR_SIZE = 1;
    const int GRID_X_OFFSET = 15;
    const int GRID_Y_OFFSET = 15;

    void set_all_alive(bool status)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                cells[x][y].set_alive(status);
                // ? It didn't work before, because I wrote cells[x, y]...
            }
        }
    }

    void render_cells(sf::RenderWindow &window, sf::Color color)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                window.draw(cells[x][y].render(x * (cells[x][y].get_size() + GRID_SEPERATOR_SIZE) + GRID_X_OFFSET,
                                               y * (cells[x][y].get_size() + GRID_SEPERATOR_SIZE) + GRID_Y_OFFSET, color));
            }
        }
    }

    void update_cells()
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {
                if (cells[x][y].get_die_next_turn()) {
                    cells[x][y].set_alive(false);
                    cells[x][y].set_die_next_turn(false);
                }
                if (cells[x][y].get_live_next_turn()) {
                    cells[x][y].set_alive(true);
                    cells[x][y].set_live_next_turn(false);
                }
            }
        }

        for (int x = 0; x < GRID_WIDTH; x++)
        {
            for (int y = 0; y < GRID_HEIGHT; y++)
            {

                bool left_connected = false;
                bool right_connected = false;
                bool up_connected = false;
                bool down_connected = false;

                bool diagonal_down_left_connected = false;
                bool diagonal_down_right_connected = false;
                bool diagonal_up_left_connected = false;
                bool diagonal_up_right_connected = false;

                /* Horizontal/Vertical */
                if (x > 0 && cells[x - 1][y].is_alive())
                {
                    left_connected = true;
                }
                if (x < GRID_WIDTH - 1 && cells[x + 1][y].is_alive())
                {
                    right_connected = true;
                }
                if (y > 0 && cells[x][y - 1].is_alive())
                {
                    up_connected = true;
                }
                if (y < GRID_HEIGHT - 1 && cells[x][y + 1].is_alive())
                {
                    down_connected = true;
                }

                /* Diagonals */
                if (x > 0 && y < GRID_HEIGHT - 1 && cells[x - 1][y + 1].is_alive())
                {
                    diagonal_down_left_connected = true;
                }
                if (x < GRID_WIDTH - 1 && y < GRID_HEIGHT - 1 && cells[x + 1][y + 1].is_alive())
                {
                    diagonal_down_right_connected = true;
                }
                if (x > 0 && y > 0 && cells[x - 1][y - 1].is_alive())
                {
                    diagonal_up_left_connected = true;
                }
                if (x < GRID_WIDTH - 1 && y > 0 && cells[x + 1][y - 1].is_alive())
                {
                    diagonal_up_right_connected = true;
                }

                /* Reproduce/Live/Die */
                int num_connected = left_connected + right_connected + up_connected + down_connected +
                                    diagonal_down_left_connected + diagonal_down_right_connected +
                                    diagonal_up_left_connected + diagonal_up_right_connected;

                if (cells[x][y].is_alive())
                {
                    if (num_connected > MAX_CONNECTED)
                        cells[x][y].set_die_next_turn(true);
                    if (num_connected < MIN_CONNECTED)
                        cells[x][y].set_die_next_turn(true);
                }
                else
                {
                    if (num_connected == MAX_CONNECTED)
                        cells[x][y].set_live_next_turn(true);
                }
            }
        }
    }
};