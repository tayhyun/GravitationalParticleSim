#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GravitySource
{
    sf::Vector2f pos;
    float strength;
    sf::CircleShape circle;

public:
    GravitySource(float pos_x, float pos_y, float strength) // this shouldn't be "strength" b/c that is the same as the member var
    {
        pos.x = pos_x;
        pos.y = pos_y;
        this->strength = strength;
        int radius = 15;
        circle.setPosition(pos);
        circle.setFillColor(sf::Color::White);
        circle.setRadius(radius); // make this a variable
    }

    void render(sf::RenderWindow &wind)
    {
        wind.draw(circle);
    }
    const sf::Vector2f get_pos() // make this a const function
    {
        return pos;
    }

    float const get_strength() // make this a const function
    {
        return strength;
    }
};

class Particle
{
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Color color;

    // this is constant between all particles so make it static
    constexpr static float radius = 4.0f;

    // You don't need a whole circle for each particle
    // just the pos and color
    // sf::CircleShape circle;

public:
    // make a default constructor so that you can use an array
    Particle()
        : pos(0.0f, 0.0f), velocity(0.0f, 0.0f)
    {
        color = sf::Color::White;
    }

    Particle(float pos_x, float pos_y, float velocity_x, float velocity_y)
    {

        velocity.x = velocity_x;
        velocity.y = velocity_y;

        pos.x = pos_x;
        pos.y = pos_y;

        color = sf::Color::White;
    }

    void render(sf::RenderWindow &wind)
    {
        sf::CircleShape circle(radius);

        circle.setPosition(pos);
        circle.setFillColor(color);

        wind.draw(circle);
    }

    void set_color(sf::Color &in_color)
    {
        color = in_color;
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
