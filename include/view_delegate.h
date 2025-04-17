#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

class ViewDelegate : public MTK::ViewDelegate
{
    public:
        ViewDelegate(int width, int height);
        virtual void drawInMTKView( MTK::View* pView ) override;

        CGRect GetFrame() const { return frame; }

        MTK::View* TransferView();

    private:
        CGRect frame;
        NS::SharedPtr<MTK::View> view;

        NS::SharedPtr<MTL::Device> device;
        NS::SharedPtr<MTL::CommandQueue> command_queue;
};