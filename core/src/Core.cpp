#include "Orbit/Core.hpp"
#include <iostream>

namespace Orbit {

Core::Core() {
    m_device = MTL::CreateSystemDefaultDevice();
    
    if (m_device) {
        std::cout << "Device: " << m_device->name()->utf8String() << std::endl;
    } else {
        std::cout << "Failed to create Metal device." << std::endl;
    }
}

Core::~Core() {
    if (m_device) {
        m_device->release();
        m_device = nullptr;
    }
}

void test() {
    Core core;
}

}
