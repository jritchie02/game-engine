#include "application.hpp"

int main()
{
    // Create an Application
    engine::Application engine = engine::Application();
    engine.loop();

    return 0;
}