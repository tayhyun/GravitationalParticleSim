#include <SFML/Graphics.hpp>
#include <vector>

class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape circle;

public:
    GravitySource(float pos_x, float pos_y, float strength)
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;

        circle.setPosition(pos);
        circle.setFillColor(sf::Color::White);
        circle.setRadius(15);
    }

    void render(sf::RenderWindow &wind)
    {
        wind.draw(circle);
    }
    sf::Vector2f get_pos()
    {
        return pos;
    }

    float get_strength()
    {
        return strength;
    }
};

class Particle
{
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::CircleShape circle;

public:
    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y)
    {

        velocity.x = velocity_x;
        velocity.y = velocity_y;

        pos.x = pos_x;
        pos.y = pos_y;

        circle.setPosition(pos);
        circle.setFillColor(sf::Color::White);
        circle.setRadius(4);
    }

    void render(sf::RenderWindow &wind)
    {
        circle.setPosition(pos);
        wind.draw(circle);
    }

    void set_color(sf::Color &color)
    {
        circle.setFillColor(color);
    }
    void updatePhysics(GravitySource &circle)
    {
        // vector decomposition for x and y
        float distance_x = circle.get_pos().x - pos.x;
        float distance_y = circle.get_pos().y - pos.y;
        // recompose the vector
        float distance = sqrt((distance_x * distance_x) + (distance_y * distance_y));
        // find the inverse of the distance to then create a normalized vector
        float inverse = 1 / distance;
        // normalized the x and y component of the vector
        float distance_x_ratio = distance_x * inverse;
        float distance_y_ratio = distance_y * inverse;
        // inverse square law to create gravitational dropoff
        float inverse_square_dropoff = inverse * inverse;

        float acceleration_x = distance_x_ratio * circle.get_strength() * inverse_square_dropoff;
        float acceleration_y = distance_y_ratio * circle.get_strength() * inverse_square_dropoff;

        velocity.x += acceleration_x;
        velocity.y += acceleration_y;

        pos.x += velocity.x;
        pos.y += velocity.y;
    }
};
sf::Color map_val_to_color(float value)
{
    if (value < 0.0f)
        value = 0;
    if (value > 1.0f)
        value = 1;

    int r = 0;
    int g = 0;
    int b = 0;

    if (value < 0.5f)
    {
        b = 255 * (1.0f - 2 * value);
        g = 255 * 2 * value;
    }
    else
    {
        g = 255 * (2.0f - 2 * value);
        r = 255 * (2 * value - 1);
    }
    return sf::Color(r, g, b);
}
