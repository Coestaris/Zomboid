#include "main.h"

int main(int argc, char **argv)
{
    Updater::init();
    EventHandler::init(argc, argv, Vector2i(500, 500), Vector2i(100, 100), "Game title");

    EventHandler::runGame();
}
