#include "Graphics.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "../GitHub/vali/Reader.hpp"


std::map<std::string, int> si;
std::map<std::string, bool> sb;
std::map<std::string, float> sfm;
std::map<std::string, std::string> ss;

sf::Vector2f FoodPosition(sch::backend*);
sf::Vector2f StartPosition(int,int);
void Add(sch::snake*, sch::backend*, int);
sf::Color GetColor(int);


void sch::Init(backend* b)
{


    vali::Reader settings("Settings.dat", si, sb, sfm, ss);
    settings.getData();
    if(si["iPlayer"] > 4)
        si["iPlayer"] = 4;
    else if(si["iPlayer"] < 1)
        si["iPlayer"] = 1;

    b->window = new sf::RenderWindow(sf::VideoMode(si["iWidth"], si["iHeight"]+50), "Grüne Schlange");
    b->bound = new sf::FloatRect(0,50,si["iWidth"],si["iHeight"]);

    b->font = new sf::Font();
    b->font->loadFromFile("Snake.ttf");


    //Textures
    b->backgroundt = new sf::Texture();
    b->backgroundt->loadFromFile("background.jpg");

    b->bodypartt = new sf::Texture();
    b->bodypartt->loadFromFile("body.png");

    b->headt = new sf::Texture();
    b->headt->loadFromFile("head.jpg");

    b->snackt = new sf::Texture();
    b->snackt->loadFromFile("snack.png");

    b->tailt = new sf::Texture();
    b->tailt->loadFromFile("tail.png");

    b->firstt = new sf::Texture();
    b->firstt->loadFromFile("gold.png");
    b->firstt->setRepeated(true);

    b->secondt = new sf::Texture();
    b->secondt->loadFromFile("silber.png");
    b->secondt->setRepeated(true);

    b->thirdt = new sf::Texture();
    b->thirdt->loadFromFile("bronze.png");
    b->thirdt->setRepeated(true);

    b->lastt = new sf::Texture();
    b->lastt->loadFromFile("black.png");
    b->lastt->setRepeated(true);

    //Sprite
    b->bg = new sf::Sprite();
    b->bg->setTexture(*b->backgroundt);
    b->bg->setPosition(-1, 50);

    b->first = new sf::Sprite();
    b->first->setTexture(*b->firstt);
    b->first->setPosition(0,0);
    b->first->setTextureRect(sf::IntRect(0,0,si["iWidth"] / 4,50));

    b->second = new sf::Sprite();
    b->second->setTexture(*b->secondt);
    b->second->setPosition(si["iWidth"] / 4,0);
    b->second->setTextureRect(sf::IntRect(0,0,si["iWidth"] / 4,50));

    b->third = new sf::Sprite();
    b->third->setTexture(*b->thirdt);
    b->third->setPosition(si["iWidth"] / 2,0);
    b->third->setTextureRect(sf::IntRect(0,0,si["iWidth"] / 4,50));

    b->last = new sf::Sprite();
    b->last->setTexture(*b->lastt);
    b->last->setPosition(3 * si["iWidth"] / 4,0);
    b->last->setTextureRect(sf::IntRect(0,0,si["iWidth"] / 4,50));

    //Sound
    b->soundb = new sf::SoundBuffer();
    b->soundb->loadFromFile("Rasseln.wav");

    b->sound = new sf::Sound();
    b->sound->setBuffer(*b->soundb);



    b->snakes = new std::vector<snake*>();
    b->snakes->reserve(si["iPlayer"]);
    for (int i = 0; i < si["iPlayer"]; i++)
    {
        snake* s = new snake();
        s->id = new std::pair<int, std::string*>();
        s->id->second = new std::string("S" + SSTR(i+1));
        s->active = new bool;
        *s->active = true;
        s->id->first = 0;
        s->h = new head();
        s->h->h = new sf::Sprite();
        s->h->h->setTexture(*b->headt);
        s->h->h->setPosition(StartPosition(i,3));
        s->h->h->setOrigin(25,25);
        s->h->d = new Direction();
        *s->h->d = (Direction)i;
        s->t = new tail();
        s->t->t = new sf::Sprite();
        s->t->t->setTexture(*b->tailt);
        s->t->t->setPosition(StartPosition(i,0));
        s->t->t->setOrigin(25,25);
        s->t->d = new Direction();
        *s->t->d = (Direction)i;
        s->bodyparts = new std::vector<bodypart*>();
        s->bodyparts->reserve(2);
        for (int j = 0; j < 2; j++)
        {
            bodypart* bp = new bodypart();
            bp->b = new sf::Sprite();
            bp->b->setTexture(*b->bodypartt);
            bp->b->setPosition(StartPosition(i,2-j));
            bp->b->setColor(GetColor(i));
            bp->b->setOrigin(25,25);
            bp->d = new Direction();
            *bp->d = (Direction)i;
            s->bodyparts->push_back(bp);
        }
        s->d = new Direction();
        *s->d = (Direction)i;
        b->snakes->push_back(s);
    }

    b->snacks = new std::vector<sf::Sprite*>();
    b->snacks->reserve(si["iPlayer"]);
    for(int i = 0; i < si["iPlayer"]; i++)
    {
        sf::Sprite* s = new sf::Sprite();
        s->setTexture(*b->snackt);
        s->setPosition(FoodPosition(b));
        b->snacks->push_back(s);
    }

    //Text
    b->text = new std::vector<sf::Text*>();
    b->text->reserve(si["iPlayer"]);
    for(int i = 0; i < si["iPlayer"]; i++)
    {
        sf::Text* t = new sf::Text();
        t->setFont(*b->font);
        t->setString(*(*b->snakes)[i]->id->second);
        t->setFillColor(sf::Color::Black);
        t->setCharacterSize(43);
        b->text->push_back(t);
    }

}

sf::Vector2f StartPosition(int i, int j)
{
    switch(i)
    {
    case 0:
        return sf::Vector2f(25, 50*j + 25);
        break;
    case 1:
        return sf::Vector2f(50*j + 25, si["iHeight"] - 25);
        break;
    case 2:
        return sf::Vector2f(si["iWidth"] - 25, si["iHeight"]  + 25 - (50*(j+1)));
        break;
    case 3:
        return sf::Vector2f(si["iWidth"]  + 25 - (50 *(j+1)), 25);
        break;
    }
    return sf::Vector2f();
}

sf::Color GetColor(int i)
{
    switch(i)
    {
    case 0:
        return sf::Color(255,255,255,255);
        break;
    case 1:
        return sf::Color(100,255,100,200);
        break;
    case 2:
        return sf::Color(255,255,100,200);
        break;
    case 3:
        return sf::Color(255,100,100,200);
        break;
    }
    return sf::Color();
}

sf::Vector2f FoodPosition(sch::backend* b)
{
    std::srand(std::time(NULL) + std::rand());
    sf::Vector2f pos((std::rand() % (si["iWidth"] / 50)) * 50, 50 + (std::rand() % (si["iHeight"] / 50)) * 50);
    for(size_t i = 0; i < b->snacks->size(); i++)
    {
        if((*b->snacks)[i]->getGlobalBounds().contains(pos))
            return FoodPosition(b);
    }
    for(size_t i = 0; i < b->snakes->size(); i++)
    {
        if((*b->snakes)[i]->h->h->getGlobalBounds().contains(pos))
            return FoodPosition(b);
        if((*b->snakes)[i]->t->t->getGlobalBounds().contains(pos))
            return FoodPosition(b);
        for (size_t j = 0; j < (*b->snakes)[i]->bodyparts->size(); j++)
            if((*(*b->snakes)[i]->bodyparts)[j]->b->getGlobalBounds().contains(pos))
                return FoodPosition(b);
    }
    return pos;
}

void Add(sch::snake* s, sch::backend* b, int i)
{
    sch::bodypart* bp = new sch::bodypart();
    bp->b = new sf::Sprite();
    s->id->first += 10;
    bp->b->setTexture(*b->bodypartt);
    bp->b->setPosition(s->bodyparts->back()->b->getPosition());
    bp->b->setOrigin(25,25);
    bp->b->setColor(GetColor(i));
    bp->d = new sch::Direction();
    *bp->d = *s->bodyparts->back()->d;
    s->bodyparts->push_back(bp);
    b->sound->play();
}

void sch::Move(backend* b)
{
    size_t in = 0;
    for(size_t i = 0; i < b->snakes->size(); i++)
    {
        if(*(*b->snakes)[i]->active == false)
        {
            in++;
            continue;
        }
        snake* s = (*b->snakes)[i];
        *s->t->d = *(*s->bodyparts)[s->bodyparts->size()-2]->d;
        s->t->t->setPosition(s->bodyparts->back()->b->getPosition());
        for(size_t j = s->bodyparts->size()-1; j > 0; j--)
        {
            (*s->bodyparts)[j]->b->setPosition((*s->bodyparts)[j-1]->b->getPosition());
            *(*s->bodyparts)[j]->d = *(*s->bodyparts)[j-1]->d;
        }
        s->bodyparts->front()->b->setPosition(s->h->h->getPosition());
        *s->bodyparts->front()->d = *s->h->d;

        *s->h->d = *s->d;
        if(*s->h->d == down)
            s->h->h->move(0,50);
        else if(*s->h->d == up)
            s->h->h->move(0,-50);
        else if(*s->h->d == left)
            s->h->h->move(-50,0);
        else if(*s->h->d == right)
            s->h->h->move(50,0);

        if (!b->bound->contains(s->h->h->getPosition()))
            *s->active = false;
        for (size_t j = 0; j < b->snacks->size(); j++)
            if (s->h->h->getGlobalBounds().contains((*b->snacks)[j]->getPosition()))
            {
                (*b->snacks)[j]->setPosition(FoodPosition(b));
                Add(s,b,i);
            }
        for (size_t j = 0; j < b->snakes->size(); j++)
        {
            snake* sc = (*b->snakes)[j];
            for (size_t k = 0; k < sc->bodyparts->size(); k++)
                if(s->h->h->getGlobalBounds().contains((*sc->bodyparts)[k]->b->getPosition()))
                {
                    *s->active = false;
                    sc->id->first += s->id->first;
                }
            if(s->h->h->getGlobalBounds().contains(sc->t->t->getPosition()))
            {
                *s->active = false;
                sc->id->first += s->id->first;
            }
            if(j == i)
                continue;
            if(s->h->h->getGlobalBounds().contains(sc->h->h->getPosition()))
            {
                *s->active = false;
                sc->id->first += s->id->first;
            }
        }
    }
    if(in == b->snakes->size())
    {
        sf::sleep(sf::seconds(10));
        b->window->close();
    }

    for (size_t i = 0; i < b->text->size(); i++)
    {
        sf::Text* t = (*b->text)[i];
        std::vector<std::pair<int,std::string*>> ss;
        for(size_t j = 0; j < b->snakes->size(); j++)
            ss.push_back(*(*b->snakes)[j]->id);

        std::sort(ss.begin(), ss.end());
        t->setString(*ss[b->text->size()-1-i].second + ": " + SSTR(ss[b->text->size()-1-i].first));
        t->setPosition((i * (si["iWidth"] / 4)) + ((si["iWidth"] / 8) - t->getGlobalBounds().width  / 2),0);
    }
}

void sch::Render(backend* b)
{
    b->window->clear();
    b->window->draw(*b->bg);
    for(size_t i = 0; i < b->snacks->size(); i++)
        b->window->draw(*(*b->snacks)[i]);
    for(size_t i = 0; i < b->snakes->size(); i++)
    {
        (*b->snakes)[i]->h->h->setRotation(0 - ((*(*b->snakes)[i]->d) * 90));
        if(b->sound->getStatus() == sf::Sound::Playing)
            (*b->snakes)[i]->t->t->setRotation(0 - ((*(*b->snakes)[i]->t->d) * 90) + (std::rand() %50) - 25);
        else
            (*b->snakes)[i]->t->t->setRotation(0 - ((*(*b->snakes)[i]->t->d) * 90));
        b->window->draw(*(*b->snakes)[i]->h->h);
        for(size_t j = 0; j < (*b->snakes)[i]->bodyparts->size(); j++)
            b->window->draw(*(*(*b->snakes)[i]->bodyparts)[j]->b);
        b->window->draw(*(*b->snakes)[i]->t->t);
    }
    b->window->draw(*b->first);
    b->window->draw(*b->second);
    b->window->draw(*b->third);
    b->window->draw(*b->last);
    for(size_t i = 0; i < b->text->size(); i++)
    {
        b->window->draw(*(*b->text)[i]);
    }
    b->window->display();
}
