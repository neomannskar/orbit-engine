#pragma once
#include "Orbit/Export.hpp"
#include "Orbit/Core.hpp"

namespace Orbit {

class ORBIT_API Renderer : public MTK::ViewDelegate {
private:
    MTL::Device* m_pDevice = nullptr;
    MTL::CommandQueue* m_pCommandQueue = nullptr;

public:
    Renderer(MTL::Device* pDevice) : m_pDevice(pDevice) {
        m_pCommandQueue = m_pDevice->newCommandQueue();
    }

    ~Renderer() {
        if (m_pCommandQueue) m_pCommandQueue->release();
    }

    virtual void drawInMTKView(MTK::View *pView) override;
};

}
