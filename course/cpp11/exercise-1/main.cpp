#include <memory>
#include <stdexcept>

#include "ConsoleUI.hpp"
#include "GameController.hpp"
#include "Logger.hpp"
#include "Player.hpp"

using namespace Go;

int main (int argc, char * argv[])
{
    using namespace std;

    IPlayer * one = nullptr;
    IPlayer * two = nullptr;

    try
    {
        one = new Player<ConsoleUI>("Player 1");
        two = new Player<ConsoleUI>("Player 2");

        GameController controller(*one, *two);

        controller.start();
    }
    catch (const exception & ex)
    {
        gLogger.log(LogLevel::kNone, ex.what());
    }
    catch (...)
    {
        gLogger.log(LogLevel::kNone, "Oops! Some uncaught exception");
    }

    delete one;
    delete two;

    return 0;
}

