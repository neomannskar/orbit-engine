#include "Orbit/Core.hpp"
#include "Orbit/Renderer.hpp"

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION

class Application : public NS::ApplicationDelegate {
private:
    /* NS::SharedPtr<MTL::Device> device*/
    NS::Window *m_pWindow;
    MTK::View *m_pView;
    MTL::Device *m_pDevice;
    Orbit::Renderer *m_pRenderer;

public:
    ~Application();

    virtual void applicationDidFinishLaunching(NS::Notification *pNotification) override;
};

Application::~Application() {
    delete m_pRenderer;
    m_pRenderer = nullptr;
    m_pView->release();
    m_pWindow->release();
    m_pDevice->release();
}

void Application::applicationDidFinishLaunching(NS::Notification *pNotification) {
    m_pDevice = MTL::CreateSystemDefaultDevice();

    CGRect frame = CGRectMake(0, 0, 800, 600);

    m_pWindow = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskTitled | NS::WindowStyleMaskClosable | NS::WindowStyleMaskResizable,
        NS::BackingStoreBuffered,
        false
    );

    m_pWindow->setTitle(NS::String::string("Orbit Engine", NS::UTF8StringEncoding));

    // Setup the metal kit view
    m_pView = MTK::View::alloc()->init(frame, m_pDevice);
    m_pView->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

    m_pView->setClearColor(MTL::ClearColor(0.1, 0.1, 0.1, 1.0));

    m_pRenderer = new Orbit::Renderer(m_pDevice);
    m_pView->setDelegate(m_pRenderer);

    m_pWindow->setContentView(m_pView);
    m_pWindow->makeKeyAndOrderFront(nullptr);

    NS::Application *pApp = reinterpret_cast<NS::Application *>(pNotification->object());
    // pApp->setActivationPolicy(NS::ApplicationActivationPolicyRegular);
    pApp->activateIgnoringOtherApps(true);
}

#include <iostream>

int main() {
    std::cout << "Starting..." << std::endl;
    NS::AutoreleasePool *pPool = NS::AutoreleasePool::alloc()->init();
    Application delegate;
    NS::Application *pSharedApp = NS::Application::sharedApplication();
    pSharedApp->setDelegate(&delegate);

    std::cout << "Running..." << std::endl;
    pSharedApp->run();

    pPool->release();
    return 0;
}
