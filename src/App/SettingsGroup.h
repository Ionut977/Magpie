#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "SettingsGroup.g.h"


namespace winrt::Magpie::implementation {

struct SettingsGroup : SettingsGroupT<SettingsGroup> {
	SettingsGroup();

	void Title(const hstring& value);

	hstring Title() const;

	void Description(Windows::Foundation::IInspectable value);

	Windows::Foundation::IInspectable Description() const;

	Windows::UI::Xaml::Controls::UIElementCollection Children() const;
	void Children(Windows::UI::Xaml::Controls::UIElementCollection const& value);

	void IsEnabledChanged(Windows::Foundation::IInspectable const&, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);
	void Loading(Windows::UI::Xaml::FrameworkElement const&, Windows::Foundation::IInspectable const&);

	event_token PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& value);
	void PropertyChanged(event_token const& token);

	static const Windows::UI::Xaml::DependencyProperty ChildrenProperty;
	static const Windows::UI::Xaml::DependencyProperty TitleProperty;
	static const Windows::UI::Xaml::DependencyProperty DescriptionProperty;

private:
	static void _OnTitleChanged(Windows::UI::Xaml::DependencyObject const& sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);
	static void _OnDescriptionChanged(Windows::UI::Xaml::DependencyObject const& sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);

	void _Update();

	void _SetEnabledState();

	event<Windows::UI::Xaml::Data::PropertyChangedEventHandler> _propertyChangedEvent;
};

}

namespace winrt::Magpie::factory_implementation {

struct SettingsGroup : SettingsGroupT<SettingsGroup, implementation::SettingsGroup> {
};

}