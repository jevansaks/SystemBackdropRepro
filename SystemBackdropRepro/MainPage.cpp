#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include "winrt\windows.ui.h"
#include "winrt\windows.ui.composition.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::SystemBackdropRepro::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

    }

    winrt::Windows::Foundation::Size MainPage::MeasureOverride(winrt::Windows::Foundation::Size const& availableSize)
    {
        ::Sleep(250);
        return __super::MeasureOverride(availableSize);
    }


    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        auto backdrop = Window::Current().try_as<winrt::Windows::UI::Composition::ICompositionSupportsSystemBackdrop>();
        if (backdrop.SystemBackdrop())
        {
            backdrop.SystemBackdrop(nullptr);
            myButton().Content(box_value(L"Currently: XAML backdrop"));
        }
        else
        {
            myButton().Content(box_value(L"Currently: System backdrop"));
            auto compositor = Window::Current().Compositor();
            auto brush = compositor.CreateColorBrush(Windows::UI::Color{ 255,0,0,0 });
            backdrop.SystemBackdrop(brush);
        }

    }
}
