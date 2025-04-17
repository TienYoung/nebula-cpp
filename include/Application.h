#include <AppKit/AppKit.hpp>
// #include <Metal/Metal.hpp>
// #include <MetalKit/MetalKit.hpp>

class Application : public NS::ApplicationDelegate
{
    public:
        ~Application();

        NS::Menu* createMenuBar();

        virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
        virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
        virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

    private:
        NS::Window* ns_window;
        // MTK::View* mtk_view;
        // MTL::Device* mtl_device;
};