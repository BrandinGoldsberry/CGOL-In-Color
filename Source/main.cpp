#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <GOLConfig.h>
#include <string>
#include <iostream>
#include <time.h>
#include <Life.hpp>

struct vector4 {
    int x;
    int y;
    int z;
    int w;
};

int FindSmallestNum(int a, int b, int c) {
    if (b < a)
    {
        if (c < b)
        {
            return c;
        }
        else {
            return b;
        }
    }
    else {
        if (c < a)
        {
            return c;
        } 
        else {
            return a;
        }
    }
}

void MakeFullBrightness(sf::Color *input_col) {
    //765
    int result = FindSmallestNum(input_col->r, input_col->g, input_col->b);
    float amt_off = 255 - result;
    input_col->r = input_col->r + amt_off;
    input_col->g = input_col->g + amt_off;
    input_col->b = input_col->b + amt_off;
}

void UpdateVectorLoc(std::vector<vector4> *BufferMap, int x, int y, sf::Color cur_color, int grid_res) {
    vector4 *current_vector = &(*BufferMap)[(x * grid_res) + y];
    current_vector->x = (current_vector->x + (int)cur_color.r) / 2;
    current_vector->y = (current_vector->y + (int)cur_color.g) / 2;
    current_vector->z = (current_vector->z + (int)cur_color.b) / 2;
    //if (current_vector->x + current_vector->y + current_vector->z < 100)
    //{
    //    switch (std::rand() % 3) {
    //    case 0:
    //        current_vector->x = 255;
    //        break;
    //    case 1:
    //        current_vector->y = 255;
    //        break;
    //    case 2:
    //        current_vector->z = 255;
    //        break;
    //    }
    //}
    current_vector->w++;
}

void UpdateMap(Life* life_map, std::vector<vector4> BufferMap, int grid_res) {
    for (size_t i = 0; i < grid_res; i++)
    {
        for (size_t j = 0; j < grid_res; j++)
        {
            int curIndex = (i * grid_res) + j;
            Life cur_life = life_map[curIndex];
            if (cur_life.isAlive()) {
                sf::Color cur_color = cur_life.GetColor();
                
                if (i > 0) {
                    UpdateVectorLoc(&BufferMap, i - 1, j, cur_color, grid_res);
                }
                if (i < grid_res - 1) {
                    UpdateVectorLoc(&BufferMap, i + 1, j, cur_color, grid_res);
                }
                if (j > 0) {
                    UpdateVectorLoc(&BufferMap, i, j - 1, cur_color, grid_res);
                }
                if (j < grid_res - 1) {
                    UpdateVectorLoc(&BufferMap, i, j + 1, cur_color, grid_res);
                }
                if (i > 0 && j > 0) {
                    UpdateVectorLoc(&BufferMap, i - 1, j - 1, cur_color, grid_res);
                }
                if (i < grid_res - 1 && j > 0) {
                    UpdateVectorLoc(&BufferMap, i + 1, j - 1, cur_color, grid_res);
                }
                if (i > 0 && j < grid_res - 1) {
                    UpdateVectorLoc(&BufferMap, i - 1, j + 1, cur_color, grid_res);
                }
                if (i < grid_res - 1 && j < grid_res - 1) {
                    UpdateVectorLoc(&BufferMap, i + 1, j + 1, cur_color, grid_res);
                }
            }
        }
    }

    for (size_t i = 0; i < grid_res; i++)
    {
        for (size_t j = 0; j < grid_res; j++)
        {
            vector4 cur_vector = BufferMap[(i * grid_res) + j];
            Life* cur_life = &life_map[(i * grid_res) + j];
            if (cur_vector.w > 2 && cur_vector.w < 6 && cur_vector.x + cur_vector.y + cur_vector.z > 100)
            {
                cur_life->setAlive(true);
                if (std::rand() % 100 > 95)
                {
                    //int r = std::rand() % 256;
                    //int g = std::rand() % 256;
                    //int b = std::rand() % 256;
                    sf::Color new_col = sf::Color(cur_vector.x, cur_vector.y, cur_vector.z, cur_vector.w);
                    MakeFullBrightness(&new_col);
                    cur_life->SetRGB(new_col);
                }
                else {
                    cur_life->SetRGB(cur_vector.x, cur_vector.y, cur_vector.z);
                }
            }
            else {
                cur_life->setAlive(false);
                cur_life->SetRGB(255, 255, 255);
            }
        }
    }
}

sf::Vector2<int> ScreenSpaceToWorldSpace(int GridRes, unsigned int MouseX, unsigned int MouseY, unsigned int ScreenX, unsigned int ScreenY) {
    float mouseXJump = ScreenX / (float)GridRes;
    float mouseYJump = ScreenY / (float)GridRes;

    int xLoc = MouseX / mouseXJump;
    int yLoc = MouseY / mouseYJump;

    return sf::Vector2<int>(xLoc, yLoc);
}

void DrawGrid(Life* life_map, sf::RenderWindow &window, int grid_res, sf::Vector2f rec_size) {
    for (size_t i = 0; i < grid_res; i++)
    {
        for (size_t j = 0; j < grid_res; j++)
        {
            Life cur_life = life_map[(i * grid_res) + j];
            if (cur_life.isAlive()) {
                sf::RectangleShape new_rec = sf::RectangleShape(rec_size);
                new_rec.setPosition(i * rec_size.x, j * rec_size.y);
                new_rec.setFillColor(cur_life.GetColor());
                window.draw(new_rec);
            }
        }
    }
}

void MouseDrawOnGrid(sf::Vector2i pos, Life *life_map, int grid_res) {
    if (pos.x < grid_res && pos.y < grid_res) {
        int life_index = (grid_res * pos.x) + pos.y;
        if (life_map[life_index].isAlive()) {
            life_map[life_index].setAlive(false);
        }
        else {
            life_map[life_index].setAlive(true);
            int r = std::rand() % 256;
            int g = std::rand() % 256;
            int b = std::rand() % 256;
            life_map[life_index].SetRGB(r, g, b);
        }
    }
}

std::string GetSquareInfo(sf::Vector2i pos, Life* life_map, int grid_res) {
    if (pos.x < grid_res && pos.y < grid_res) {
        int life_index = (grid_res * pos.x) + pos.y;
        if (life_map[life_index].isAlive()) {
            sf::Color curColor = life_map[life_index].GetColor();
            return "R: " + std::to_string((int)curColor.r) + " G: " + std::to_string((int)curColor.g) + " B: " + std::to_string((int)curColor.b);
        }
        else {
            return "Yo it's dead bro";
        }
    }
}

void FlushBuffer(std::vector<vector4> buffer, int grid_res) {
    for (size_t i = 0; i < grid_res * grid_res; i++)
    {
        buffer.push_back(vector4{ 0, 0, 0, 0 });
    }
}

int main()
{
    bool isPaused = false;
    unsigned int ScreenX = 640;
    unsigned int ScreenY = 480;
    unsigned int GridRes = 50;
    int UpdateTime = 10;
    int ElapsedTime = 0;
    sf::Vector2i mouse_position;

	sf::RenderWindow GOLWindow{ sf::VideoMode{ ScreenX, ScreenY }, "Game Of C", sf::Style::Default };
    GOLWindow.setKeyRepeatEnabled(false);

    float rec_size_X = ScreenX / (float)GridRes;
    float rec_size_Y = ScreenY / (float)GridRes;

    sf::Vector2f rec_size = sf::Vector2f(rec_size_X, rec_size_Y);

    Life *life_forms   = new Life[GridRes * GridRes];
    std::vector<vector4> LifeMapBuffer;
    for (size_t i = 0; i < GridRes * GridRes; i++)
    {
        LifeMapBuffer.push_back(vector4{ 0, 0, 0, 0 });
    }

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text mouse_text("", font, 20);
    sf::Text pause_text("Paused", font, 20);
    sf::Text update_rate(std::to_string(UpdateTime), font, 20);
    sf::Text rgb_text("", font, 20);
    pause_text.setPosition(0, 20);
    update_rate.setPosition(0, 40);
    rgb_text.setPosition(0, 60);
    pause_text.setColor(sf::Color::Blue);
    mouse_text.setColor(sf::Color::Blue);
    update_rate.setColor(sf::Color::Blue);
    rgb_text.setColor(sf::Color::Blue);

	while (GOLWindow.isOpen())
	{
        bool mouse_was_pressed = false;
		sf::Event winEvent;
		while (GOLWindow.pollEvent(winEvent))
		{
            switch (winEvent.type)
            {
            case sf::Event::Closed:
				GOLWindow.close();
                break;
            case sf::Event::MouseButtonPressed: 
                if(winEvent.mouseButton.button == 0) {
                    mouse_position = sf::Mouse::getPosition(GOLWindow);
                    sf::Vector2i grid_pos = ScreenSpaceToWorldSpace(GridRes, mouse_position.x, mouse_position.y, ScreenX, ScreenY);
                    mouse_text.setString("X: " + std::to_string(grid_pos.x) + " Y: " + std::to_string(grid_pos.y));
                    MouseDrawOnGrid(grid_pos, life_forms, GridRes);
                    mouse_was_pressed = true;
                }
                else {
                    mouse_position = sf::Mouse::getPosition(GOLWindow);
                    sf::Vector2i grid_pos = ScreenSpaceToWorldSpace(GridRes, mouse_position.x, mouse_position.y, ScreenX, ScreenY);
                    mouse_text.setString("X: " + std::to_string(grid_pos.x) + " Y: " + std::to_string(grid_pos.y));
                    rgb_text.setString(GetSquareInfo(grid_pos, life_forms, GridRes));
                }
                break;
            case sf::Event::KeyPressed:
                if (winEvent.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused;
                }
                if (winEvent.key.code == sf::Keyboard::Right) {
                    ElapsedTime = UpdateTime;
                }
                if (winEvent.key.code == sf::Keyboard::Up) {
                    UpdateTime += 10;
                    update_rate.setString(std::to_string(UpdateTime));
                }
                if (winEvent.key.code == sf::Keyboard::Down) {
                    UpdateTime -= 10;
                    update_rate.setString(std::to_string(UpdateTime));
                }
                break;
            }
		}

		GOLWindow.clear();

        if (ElapsedTime >= UpdateTime) {
            UpdateMap(life_forms, LifeMapBuffer, GridRes);
            FlushBuffer(LifeMapBuffer, GridRes);
            ElapsedTime = 0;
        }
        else if (!isPaused) {
            ElapsedTime++;
        }

        DrawGrid(life_forms, GOLWindow, GridRes, rec_size);

        GOLWindow.draw(update_rate);
        GOLWindow.draw(mouse_text);
        GOLWindow.draw(rgb_text);
        if(isPaused) {
            GOLWindow.draw(pause_text);
        }
		GOLWindow.display();
        sf::sleep(sf::milliseconds(16));
	}

    delete[] life_forms;
}