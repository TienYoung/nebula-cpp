#define NS_PRIVATE_IMPLEMENTATION
#include "Application.h"

void ApplicationDelegate::applicationWillFinishLaunching( NS::Notification* pNotification )
{
    using NS::StringEncoding::UTF8StringEncoding;

    NS::SharedPtr<NS::Menu> app_menu = NS::TransferPtr(NS::Menu::alloc()->init( NS::String::string( "Nebula", UTF8StringEncoding ) ));
    SEL quitCb = NS::MenuItem::registerActionCallback( "appQuit", [](void*,SEL,const NS::Object* pSender){
        NS::Application::sharedApplication()->terminate( pSender );
    } );
    NS::SharedPtr<NS::MenuItem> app_quit_item = NS::TransferPtr(app_menu->addItem( NS::String::string( "Quit Nebula", UTF8StringEncoding ), quitCb, NS::String::string( "q", UTF8StringEncoding ) ));
    app_quit_item->setKeyEquivalentModifierMask( NS::EventModifierFlagCommand );

    NS::SharedPtr<NS::Menu> main_menu = NS::TransferPtr(NS::Menu::alloc()->init());
    NS::SharedPtr<NS::MenuItem> app_menu_item = NS::TransferPtr(NS::MenuItem::alloc()->init());
    main_menu->addItem( app_menu_item.get() );
    app_menu_item->setSubmenu( app_menu.get() );

    NS::Application* app = reinterpret_cast< NS::Application* >( pNotification->object() );
    app->setMainMenu( main_menu.get() );
    app->setActivationPolicy( NS::ActivationPolicy::ActivationPolicyRegular );
}

void ApplicationDelegate::applicationDidFinishLaunching( NS::Notification* pNotification )
{
    CGRect frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };

    NS::SharedPtr<NS::Window> window = NS::TransferPtr(NS::Window::alloc()->init(
        frame,
        NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false ));

    // mtl_device = MTL::CreateSystemDefaultDevice();

    // mtk_view = MTK::View::alloc()->init( frame, mtl_device );
    // mtk_view->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
    // mtk_view->setClearColor( MTL::ClearColor::Make( 1.0, 0.0, 0.0, 1.0 ) );

    // view_delegate = new MyMTKViewDelegate( _pDevice );
    // mtk_view->setDelegate( _pViewDelegate );

    // window->setContentView( mtk_view );
    window->setTitle( NS::String::string( "Nebula", NS::StringEncoding::UTF8StringEncoding ) );

    window->makeKeyAndOrderFront( nullptr );

    NS::Application* app = reinterpret_cast< NS::Application* >( pNotification->object() );
    app->activateIgnoringOtherApps( true );
}

bool ApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender )
{
    return true;
}