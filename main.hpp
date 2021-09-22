#ifndef SCHLANGE_HPP
#define SCHLANGE_HPP
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <bits/stdc++.h>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace sch
{

enum Direction
{
    right, up, left, down
};

struct tail
{
    sf::Sprite* t;
    Direction* d;
};


struct bodypart
{
    sf::Sprite* b;
    Direction* d;
};

struct head
{
    sf::Sprite* h;
    Direction* d;
};

struct snake
{
    std::pair<int, std::string*>* id;
    bool* active;
    Direction* d;
    tail* t;
    std::vector<bodypart*>* bodyparts;
    head* h;
};

struct backend
{
    sf::SoundBuffer* soundb;
    sf::Sound* sound;

    sf::Font* font;

    sf::FloatRect* bound;

    sf::RenderWindow* window;

    sf::Texture* firstt;
    sf::Texture* secondt;
    sf::Texture* thirdt;
    sf::Texture* lastt;
    sf::Texture* tailt;
    sf::Texture* backgroundt;
    sf::Texture* bodypartt;
    sf::Texture* headt;
    sf::Texture* snackt;

    sf::Sprite* first;
    sf::Sprite* second;
    sf::Sprite* third;
    sf::Sprite* last;
    sf::Sprite* bg;

    std::vector<sf::Sprite*>* snacks;
    std::vector<snake*>* snakes;
    std::vector<sf::Text*>* text;
};

void Inputhandler(backend*);

}

#endif // SCHLANGE_HPP
