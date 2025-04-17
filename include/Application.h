#include <AppKit/AppKit.hpp>
// #include <Metal/Metal.hpp>
// #include <MetalKit/MetalKit.hpp>

class ApplicationDelegate : public NS::ApplicationDelegate
{
    public:
        virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
        virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;
};