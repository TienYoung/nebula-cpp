#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#include "view_delegate.h"

ViewDelegate::ViewDelegate( MTL::Device* pDevice )
: device( NS::RetainPtr<MTL::Device>(pDevice))
{
    command_queue = NS::TransferPtr(device->newCommandQueue());
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