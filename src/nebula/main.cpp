#include "application_delegate.h"
#include "view_delegate.h"

int main(int argc, char* argv[])
{
    ApplicationDelegate app_delegate(std::make_shared<ViewDelegate>(512, 512));

    NS::SharedPtr<NS::Application> pSharedApplication = NS::TransferPtr(NS::Application::sharedApplication());
    pSharedApplication->setDelegate( &app_delegate );
    pSharedApplication->run();

    return 0;
}