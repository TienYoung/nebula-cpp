#define NS_PRIVATE_IMPLEMENTATION
#include "application_delegate.h"
#include "view_delegate.h"

ApplicationDelegate::ApplicationDelegate(std::shared_ptr<ViewDelegate> view_delegate)
: view_delegate(view_delegate)
{
}

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
    NS::Window* window = NS::Window::alloc()->init(
        view_delegate->GetFrame(),
        NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
        NS::BackingStoreBuffered,
        false );

    window->setContentView( view_delegate->TransferView() );

    window->setTitle( NS::String::string( "Nebula", NS::StringEncoding::UTF8StringEncoding ) );

    window->makeKeyAndOrderFront( nullptr );

    NS::Application* app = reinterpret_cast< NS::Application* >( pNotification->object() );
    app->activateIgnoringOtherApps( true );
}

bool ApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender )
{
    return true;
}