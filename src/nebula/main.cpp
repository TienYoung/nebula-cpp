#include "Application.h"

int main(int argc, char* argv[])
{
    ApplicationDelegate app_delegate;

    NS::SharedPtr<NS::Application> pSharedApplication = NS::TransferPtr(NS::Application::sharedApplication());
    pSharedApplication->setDelegate( &app_delegate );
    pSharedApplication->run();

    return 0;
}