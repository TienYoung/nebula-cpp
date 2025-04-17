#include <AppKit/AppKit.hpp>
// #include <Metal/Metal.hpp>
// #include <MetalKit/MetalKit.hpp>

class ViewDelegate;

class ApplicationDelegate : public NS::ApplicationDelegate
{
    public:
        ApplicationDelegate(ViewDelegate* view_delegate);
        virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
        virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

    private:
        ViewDelegate* view_delegate = nullptr;
};