#include <SFML/Graphics.hpp>
#include "dft.hpp"
#include <iostream>
#include <fstream>
#include <cmath>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        return 0;
    }

    std::ifstream input{argv[1]};

    std::vector<std::complex<double>> path;
    for (double re, im; input >> re >> im;)
    {
        path.push_back(re + im * 1i);
    }
    input.close();

    std::vector<std::complex<double>> transformed{fft::dft(path)};

    sf::VertexArray trail{sf::LineStrip};

    sf::RenderWindow window{sf::VideoMode{800, 600}, "Fourier Drawer"};

    const double PI = std::acos(-1);

    double time = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();

        std::complex<double> offset = window.getSize().x * 0.5 + static_cast<double>(window.getSize().y) * 0.5i;

        std::complex<double> pos = offset;
        for (size_t i = 0; i < path.size(); i++)
        {
            std::complex<double> prevPos = pos;

            double frequency = i;
            double radius = std::sqrt(std::pow(transformed[i].real(), 2) + std::pow(transformed[i].imag(), 2));
            double phase = std::atan2(transformed[i].imag(), transformed[i].real());

            pos += radius * std::exp(1i * (frequency * time + phase));

            sf::CircleShape circle{static_cast<float>(radius)};
            circle.setOrigin({static_cast<float>(radius), static_cast<float>(radius)});
            circle.setPosition(static_cast<float>(prevPos.real()), static_cast<float>(prevPos.imag()));
            circle.setOutlineColor(sf::Color{0x7f7f7f7f});
            circle.setOutlineThickness(1);
            circle.setFillColor(sf::Color{0x00000000});
            window.draw(circle);

            sf::Vertex line[2];
            line[0].position = {static_cast<float>(prevPos.real()), static_cast<float>(prevPos.imag())};
            line[0].color = sf::Color{0x7f7f00ff};
            line[1].position = {static_cast<float>(pos.real()), static_cast<float>(pos.imag())};
            line[1].color = sf::Color{0x7f7f00ff};
            window.draw(line, 2, sf::Lines);
        }

        trail.append(sf::Vertex{{static_cast<float>(pos.real()), static_cast<float>(pos.imag())}, sf::Color{0xffffffff}});
        window.draw(trail);
        if (trail.getVertexCount() >= path.size())
        {
            trail.clear();
        }

        window.display();

        time += 2 * PI / path.size();
        if (time > 2 * PI)
        {
            time -= 2 * PI;
        }
    }

    return 0;
}