#include "main.hpp"
#include "Graphics.hpp"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

void sch::Inputhandler(backend* b)
{
    int i = 0;
    while(b->window->isOpen())
    {
        i++;
        Render(b);
        if(i == 1000)
        {
            Move(b);
            i = 0;
        }
        sf::Event event;
        while (b->window->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Left && *(*b->snakes)[0]->h->d != right)
                    *(*b->snakes)[0]->d = left;
                else if(event.key.code == sf::Keyboard::Up && *(*b->snakes)[0]->h->d != down)
                    *(*b->snakes)[0]->d = up;
                else if(event.key.code == sf::Keyboard::Right && *(*b->snakes)[0]->h->d != left)
                    *(*b->snakes)[0]->d = right;
                else if(event.key.code == sf::Keyboard::Down && *(*b->snakes)[0]->h->d != up)
                    *(*b->snakes)[0]->d = down;

                if(b->snakes->size() < 2)
                    continue;

                if(event.key.code == sf::Keyboard::A && *(*b->snakes)[1]->h->d != right)
                    *(*b->snakes)[1]->d = left;
                else if(event.key.code == sf::Keyboard::W && *(*b->snakes)[1]->h->d != down)
                    *(*b->snakes)[1]->d = up;
                else if(event.key.code == sf::Keyboard::D && *(*b->snakes)[1]->h->d != left)
                    *(*b->snakes)[1]->d = right;
                else if(event.key.code == sf::Keyboard::S && *(*b->snakes)[1]->h->d != up)
                    *(*b->snakes)[1]->d = down;

                if(b->snakes->size() < 3)
                    continue;

                if(event.key.code == sf::Keyboard::J && *(*b->snakes)[2]->h->d != right)
                    *(*b->snakes)[2]->d = left;
                else if(event.key.code == sf::Keyboard::I && *(*b->snakes)[2]->h->d != down)
                    *(*b->snakes)[2]->d = up;
                else if(event.key.code == sf::Keyboard::L && *(*b->snakes)[2]->h->d != left)
                    *(*b->snakes)[2]->d = right;
                else if(event.key.code == sf::Keyboard::K && *(*b->snakes)[2]->h->d != up)
                    *(*b->snakes)[2]->d = down;

                if(b->snakes->size() < 4)
                    continue;

                if(event.key.code == sf::Keyboard::Num1 && *(*b->snakes)[3]->h->d != right)
                    *(*b->snakes)[3]->d = left;
                else if(event.key.code == sf::Keyboard::Num5 && *(*b->snakes)[3]->h->d != down)
                    *(*b->snakes)[3]->d = up;
                else if(event.key.code == sf::Keyboard::Num3 && *(*b->snakes)[3]->h->d != left)
                    *(*b->snakes)[3]->d = right;
                else if(event.key.code == sf::Keyboard::Num2 && *(*b->snakes)[3]->h->d != up)
                    *(*b->snakes)[3]->d = down;
            }
            if (event.type == sf::Event::Closed)
                b->window->close();
        }
    }
}
