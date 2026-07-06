#include "Orbit/Renderer.hpp"

namespace Orbit {

Renderer::Renderer(MTL::Device *pDevice) : m_pDevice(pDevice) {
    m_pCmdQueue = m_pDevice->newMTL4CommandQueue();
    m_pCmdBuffer = m_pDevice->newCommandBuffer();

    for (auto& pAlloc : m_pCmdAllocators) {
        pAlloc = m_pDevice->newCommandAllocator();
    }

    m_pSharedEvent = m_pDevice->newSharedEvent();
    m_pSharedEvent->setSignaledValue(0);
}

Renderer::~Renderer() {
    if (m_pSharedEvent)
        m_pSharedEvent->release();

    for (auto *pAlloc : m_pCmdAllocators) {
        if (pAlloc)
            pAlloc->release();
    }

    if (m_pCmdBuffer)
        m_pCmdBuffer->release();
    if (m_pCmdQueue)
        m_pCmdQueue->release();
}

void Renderer::drawInMTKView(MTK::View *pView) {
    // 1. Autorelease pool to manage memory for Objective-C objects every frame
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();

    // 2. Throttle the CPU so it never gets more than kMaxFramesInFlight frames
    // ahead of the GPU, then claim this frame's allocator
    if (m_frameNum >= kMaxFramesInFlight) {
        m_pSharedEvent->waitUntilSignaledValue(m_frameNum - kMaxFramesInFlight, UINT64_MAX);
    }
    const uint8_t frameIndex = m_frameNum % kMaxFramesInFlight;
    MTL4::CommandAllocator *pAlloc = m_pCmdAllocators[frameIndex];
    pAlloc->reset();

    // 3. Create a command buffer
    m_pCmdBuffer->beginCommandBuffer(pAlloc);
    CA::MetalDrawable *pDrawable = pView->currentDrawable();

    if (pDrawable) {
        MTL4::RenderPassDescriptor *pRpd = MTL4::RenderPassDescriptor::alloc()->init();
        MTL::RenderPassColorAttachmentDescriptor *pColorAttachment = pRpd->colorAttachments()->object(0);
        pColorAttachment->setTexture(pDrawable->texture());
        pColorAttachment->setLoadAction(MTL::LoadActionClear);
        pColorAttachment->setStoreAction(MTL::StoreActionStore);
        pColorAttachment->setClearColor(pView->clearColor());

        // 5. Create a render command encoder
        MTL4::RenderCommandEncoder *pEnc = m_pCmdBuffer->renderCommandEncoder(pRpd);

        // DRAW CALLS

        pEnc->endEncoding();
        pRpd->release();
    }

    m_pCmdBuffer->endCommandBuffer();

    if (pDrawable) {
        // 6. Metal 4 detaches presentation from the command buffer
        // The queue must wait on and signals the drawable.
        m_pCmdQueue->wait(pDrawable);
        m_pCmdQueue->commit(&m_pCmdBuffer, 1);
        m_pCmdQueue->signalDrawable(pDrawable);
        pDrawable->present();
    } else {
        m_pCmdQueue->commit(&m_pCmdBuffer, 1);
    }

    // 7. Signal that this frame is complete and advance the frame counter

    m_pCmdQueue->signalEvent(m_pSharedEvent, m_frameNum);
    m_frameNum++;

    // 8. Release the autorelease pool to free up memory
    pPool->release();
}

}
