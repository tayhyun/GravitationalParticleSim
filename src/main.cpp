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
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Physics Simulation by Tae Kim");
    window.setFramerateLimit(60);

    std::vector<GravitySource> gravitySources;

    gravitySources.push_back(GravitySource(500, 500, 7000));
    gravitySources.push_back(GravitySource(1200, 500, 7000));

    int amountOfParticles = 2000;

    std::vector<Particle> particles;

    for (int i = 0; i < amountOfParticles; i++)
    {
        // adds particles to the vector
        particles.push_back(Particle(600, 700, 4, 0.2 + (0.1 / amountOfParticles) * i));

        // changing colors
        float val = (float)i / (float)amountOfParticles;

        sf::Color color = map_val_to_color(val);

        particles[i].set_color(color);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        window.clear();

        for (int i = 0; i < gravitySources.size(); i++)
        {
            for (int j = 0; j < particles.size(); j++)
            {
                particles[j].updatePhysics(gravitySources[i]);
            }
        }

        for (int i = 0; i < gravitySources.size(); i++)
        {
            gravitySources[i].render(window);
        }

        for (int j = 0; j < particles.size(); j++)
        {
            particles[j].render(window);
        }
        window.display();
    }

    return 0;
}
