#define NS_PRIVATE_IMPLEMENTATION
#include "Application.h"

Application::~Application()
{
    ns_window->release();
    // mtl_device->release();
    // mtk_view->release();
}

void Application::applicationWillFinishLaunching( NS::Notification* pNotification )
{
    using NS::StringEncoding::UTF8StringEncoding;

    NS::Menu* pMainMenu = NS::Menu::alloc()->init();
    NS::MenuItem* pAppMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* pAppMenu = NS::Menu::alloc()->init( NS::String::string( "Appname", UTF8StringEncoding ) );

    NS::String* appName = NS::RunningApplication::currentApplication()->localizedName();
    NS::String* quitItemName = NS::String::string( "Quit ", UTF8StringEncoding )->stringByAppendingString( appName );
    SEL quitCb = NS::MenuItem::registerActionCallback( "appQuit", [](void*,SEL,const NS::Object* pSender){
        auto pApp = NS::Application::sharedApplication();
        pApp->terminate( pSender );
    } );

    NS::MenuItem* pAppQuitItem = pAppMenu->addItem( quitItemName, quitCb, NS::String::string( "q", UTF8StringEncoding ) );
    pAppQuitItem->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );
    pAppMenuItem->setSubmenu( pAppMenu );

    NS::MenuItem* pWindowMenuItem = NS::MenuItem::alloc()->init();
    NS::Menu* pWindowMenu = NS::Menu::alloc()->init( NS::String::string( "Window", UTF8StringEncoding ) );

    SEL closeWindowCb = NS::MenuItem::registerActionCallback( "windowClose", [](void*, SEL, const NS::Object*){
        auto pApp = NS::Application::sharedApplication();
            pApp->windows()->object< NS::Window >(0)->close();
    } );
    NS::MenuItem* pCloseWindowItem = pWindowMenu->addItem( NS::String::string( "Close Window", UTF8StringEncoding ), closeWindowCb, NS::String::string( "w", UTF8StringEncoding ) );
    pCloseWindowItem->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );

    pWindowMenuItem->setSubmenu( pWindowMenu );

    pMainMenu->addItem( pAppMenuItem );
    pMainMenu->addItem( pWindowMenuItem );

    pAppMenuItem->release();
    pWindowMenuItem->release();
    pAppMenu->release();
    pWindowMenu->release();

    NS::Application* app = reinterpret_cast< NS::Application* >( pNotification->object() );
    app->setMainMenu( pMainMenu );
    app->setActivationPolicy( NS::ActivationPolicy::ActivationPolicyRegular );
}

void Application::applicationDidFinishLaunching( NS::Notification* pNotification )
{
    CGRect frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };

    ns_window = NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false );

    // mtl_device = MTL::CreateSystemDefaultDevice();

    // mtk_view = MTK::View::alloc()->init( frame, mtl_device );
    // mtk_view->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
    // mtk_view->setClearColor( MTL::ClearColor::Make( 1.0, 0.0, 0.0, 1.0 ) );

    // view_delegate = new MyMTKViewDelegate( _pDevice );
    // mtk_view->setDelegate( _pViewDelegate );

    // ns_window->setContentView( mtk_view );
    ns_window->setTitle( NS::String::string( "Nebula", NS::StringEncoding::UTF8StringEncoding ) );

    ns_window->makeKeyAndOrderFront( nullptr );

    NS::Application* app = reinterpret_cast< NS::Application* >( pNotification->object() );
    app->activateIgnoringOtherApps( true );
}

bool Application::applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender )
{
    return true;
}