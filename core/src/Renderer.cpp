#include "Orbit/Renderer.hpp"

namespace Orbit {

void Renderer::drawInMTKView(MTK::View *pView) {
    // 1. Autorelease pool to manage memory for Objective-C objects every frame
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

    // 2. Create a command buffer
    MTL::CommandBuffer *pCmd = m_pCommandQueue->commandBuffer();

    // 3. Get the render pass descriptor from the view
    MTL::RenderPassDescriptor *pRpd = pView->currentRenderPassDescriptor();

    if (pRpd) {
        // 4. Create a render command encoder
        MTL::RenderCommandEncoder *pEnc = pCmd->renderCommandEncoder(pRpd);

        // (If we were drawing the draw calls go here)
        
        pEnc->endEncoding();

        // 5. Present the drawable to the screen
        pCmd->presentDrawable(pView->currentDrawable());
    }

    // 6. Commit the command buffer to the GPU
    pCmd->commit();

    // 7. Release the autorelease pool to free up memory
    pPool->release();
}

}