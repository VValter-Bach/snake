#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <ctime>
#include "main.hpp"
#include "Graphics.hpp"


int main()
{

    sch::backend* b = new sch::backend();
    sch::Init(b);
    sch::Inputhandler(b);

}
