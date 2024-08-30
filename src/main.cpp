#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "physics.h"

#define WIN_WIDTH 1920 // you should make these command line arguemnts if you can't figure out a way to find the resolution automagically
#define WIN_HEIGHT 1080

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Physics Simulation by Tae Kim");
    window.setFramerateLimit(120);

    std::vector<GravitySource> gravitySources;

    gravitySources.push_back(GravitySource(600, 500, 7000));
    gravitySources.push_back(GravitySource(1200, 500, 7000));

    int amountOfParticles = 10000; // this should also be a command line argument

    Particle particles[amountOfParticles];

    for (int i = 0; i < amountOfParticles; i++)
    {
        // adds particles to the vector
        particles[i] = Particle(600, 700, 4, 0.2 + (0.1 / amountOfParticles) * i);
        // should make these ^^ fractions of the total window height and width insead of set points

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
