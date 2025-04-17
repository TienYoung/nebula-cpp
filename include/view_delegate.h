#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

class ViewDelegate : public MTK::ViewDelegate
{
    public:
        ViewDelegate( MTL::Device* pDevice );
        virtual void drawInMTKView( MTK::View* pView ) override;

        NS::SharedPtr<MTL::Device> device;
        NS::SharedPtr<MTL::CommandQueue> command_queue;
};