#pragma once
#include "Orbit/Export.hpp"
#include "Orbit/Core.hpp"

// #if defined(__APPLE__)
    #include <cstdint>
    #include <cstddef>
// #endif

namespace Orbit {

class ORBIT_API Renderer : public MTK::ViewDelegate {
public:
    Renderer(MTL::Device* pDevice);
    /* : m_pDevice(pDevice) {
        m_pCommandQueue = m_pDevice->newCommandQueue();
    } */
    ~Renderer();
    /* {
        if (m_pCommandQueue) m_pCommandQueue->release();
    } */
    virtual void drawInMTKView(MTK::View *pView) override;

private:
    static constexpr uint8_t kMaxFramesInFlight = 3;

    MTL::Device* m_pDevice = nullptr;

    MTL4::CommandQueue *m_pCmdQueue = nullptr;
    MTL4::CommandBuffer *m_pCmdBuffer = nullptr;
    MTL4::CommandAllocator *m_pCmdAllocators[kMaxFramesInFlight] = {};

    MTL::SharedEvent *m_pSharedEvent = nullptr;
    size_t m_frameNum = 0;
};

}
