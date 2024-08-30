#include <SFML/Graphics.hpp>
#include <vector>
#include "physics.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Physics Simulation by Tae Kim");
    window.setFramerateLimit(120);

    std::vector<GravitySource> gravitySources;

    gravitySources.push_back(GravitySource(500, 500, 7000));
    gravitySources.push_back(GravitySource(1200, 500, 7000));

    int amountOfParticles = 10000;

    Particle particles[amountOfParticles]; // this will work after you make a default consrutor

    for (int i = 0; i < amountOfParticles; i++)
    {
        // adds particles to the vector
        particles[i] = Particle(600, 700, 4, 0.2 + (0.1 / amountOfParticles) * i);

        // particles.push_back(Particle(600, 700, 4, 0.2 + (0.1 / amountOfParticles) * i));

        // update the particle's position, velocity and other stuff via setters since they will be nothing be default

        // changing colors
        float val = (float)i / (float)amountOfParticles;
        // sf::Color color = sf::Color::Red;
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
            for (int j = 0; j < amountOfParticles; j++) // particle.size() is now just amountOfParticles
            {
                particles[j].updatePhysics(gravitySources[i]);
            }
        }

        for (int i = 0; i < gravitySources.size(); i++)
        {
            gravitySources[i].render(window);
        }

        for (int j = 0; j < amountOfParticles; j++) // particle.size() is now just amountOfParticles
        {
            particles[j].render(window);
        }
        window.display();
    }

    return 0;
}
