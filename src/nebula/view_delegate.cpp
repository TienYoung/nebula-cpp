#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#include "view_delegate.h"

ViewDelegate::ViewDelegate(int width, int height)
: frame(CGRectMake(100, 100, width, height))
{
    device = NS::TransferPtr(MTL::CreateSystemDefaultDevice());
    command_queue = NS::TransferPtr(device->newCommandQueue());

    view = NS::TransferPtr(MTK::View::alloc()->init( frame, device.get() ));
    view->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
    view->setClearColor( MTL::ClearColor::Make( 1.0, 0.0, 0.0, 1.0 ) );
    
}

void ViewDelegate::drawInMTKView( MTK::View* pView )
{
    NS::SharedPtr<MTL::CommandBuffer> cmd = NS::RetainPtr(command_queue->commandBuffer());
    MTL::RenderPassDescriptor* desc = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* encoder = cmd->renderCommandEncoder( desc );
    encoder->endEncoding();
    cmd->presentDrawable( pView->currentDrawable() );
    cmd->commit();
}

MTK::View* ViewDelegate::TransferView() 
{ 
    view->setDelegate( this );
    MTK::View* raw_view = view.get()->retain();
    view.detach();
    return raw_view; 
}