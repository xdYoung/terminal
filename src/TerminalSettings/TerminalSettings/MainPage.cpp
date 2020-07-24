﻿#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "Globals.h"
#include "Profiles.h"
#include "ColorSchemes.h"
#include "Keybindings.h"

namespace winrt
{
    namespace MUX = Microsoft::UI::Xaml;
}

using namespace winrt::Windows::UI::Xaml;

namespace winrt::TerminalSettings::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

        // TODO: When we actually connect this to Windows Terminal,
        //       this section will clone the active AppSettings
        _settingsSource = AppSettings();
        _settingsClone = _settingsSource.Clone();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
    }

    void MainPage::SettingsNav_SelectionChanged(const MUX::Controls::NavigationView, const MUX::Controls::NavigationViewSelectionChangedEventArgs)
    {
    }

    void MainPage::SettingsNav_Loaded(IInspectable const& sender, RoutedEventArgs const& e)
    {
        //// set the initial selectedItem
        for (uint32_t i = 0; i < SettingsNav().MenuItems().Size(); i++)
        {
            const auto item = SettingsNav().MenuItems().GetAt(i).as<Controls::ContentControl>();
            const hstring globalsNav = L"Globals_Nav";
            const hstring itemTag = unbox_value<hstring>(item.Tag());

            if (itemTag == globalsNav)
            {
                // item.IsSelected(true); // have to investigate how to replace this
                SettingsNav().Header() = item.Tag();
                break;
            }
        }

        contentFrame().Navigate(xaml_typename<TerminalSettings::Globals>());
    }

    void MainPage::SettingsNav_ItemInvoked(MUX::Controls::NavigationView const& sender, MUX::Controls::NavigationViewItemInvokedEventArgs const& args)
    {
        auto clickedItemContainer = args.InvokedItemContainer();

        if (clickedItemContainer != NULL)
        {
            const hstring globalsPage = L"General_Nav";
            const hstring profilesPage = L"Profiles_Nav";
            const hstring colorSchemesPage = L"Appearance_Nav";
            const hstring keybindingsPage = L"Keyboard_Nav";

            hstring clickedItemTag = unbox_value<hstring>(clickedItemContainer.Tag());

            if (clickedItemTag == globalsPage)
            {
                contentFrame().Navigate(xaml_typename<TerminalSettings::Globals>());
            }
            else if (clickedItemTag == profilesPage)
            {
                contentFrame().Navigate(xaml_typename<TerminalSettings::Profiles>());
            }
            else if (clickedItemTag == colorSchemesPage)
            {
                contentFrame().Navigate(xaml_typename<TerminalSettings::ColorSchemes>());
            }
            else if (clickedItemTag == keybindingsPage)
            {
                contentFrame().Navigate(xaml_typename<TerminalSettings::Keybindings>());
            }
        }
    }
}