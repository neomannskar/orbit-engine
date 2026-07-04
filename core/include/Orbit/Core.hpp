#pragma once
#include "Orbit/Export.hpp"

namespace Orbit {

ORBIT_API void test();

class Core {
public:
    Core();
    ~Core();
private:
    /* NS::SharedPtr<MTL::Device> device */ MTL::Device* m_device = nullptr;
};

}
