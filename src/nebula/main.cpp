#include "Application.h"

int main(int argc, char* argv[])
{
    Application app;

    NS::Application* pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate( &app );
    pSharedApplication->run();

    return 0;
}