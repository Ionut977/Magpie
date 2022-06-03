#include "pch.h"
#include "SettingItem.h"
#if __has_include("SettingItem.g.cpp")
#include "SettingItem.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::Foundation;


namespace winrt::Magpie::implementation {

DependencyProperty SettingItem::TitleProperty = DependencyProperty::Register(
	L"Title",
	xaml_typename<hstring>(),
	xaml_typename<Magpie::SettingItem>(),
	PropertyMetadata(box_value(L""), _OnTitleChanged)
);

DependencyProperty SettingItem::DescriptionProperty = DependencyProperty::Register(
	L"Description",
	xaml_typename<IInspectable>(),
	xaml_typename<Magpie::SettingItem>(),
	PropertyMetadata(nullptr, &SettingItem::_OnDescriptionChanged)
);

DependencyProperty SettingItem::IconProperty = DependencyProperty::Register(
	L"Icon",
	xaml_typename<IInspectable>(),
	xaml_typename<Magpie::SettingItem>(),
	PropertyMetadata(nullptr, &SettingItem::_OnIconChanged)
);

DependencyProperty SettingItem::ActionContentProperty = DependencyProperty::Register(
	L"ActionContent",
	xaml_typename<IInspectable>(),
	xaml_typename<Magpie::SettingItem>(),
	PropertyMetadata(nullptr, &SettingItem::_OnActionContentChanged)
);

SettingItem::SettingItem() {
	InitializeComponent();
}

void SettingItem::Title(const hstring& value) {
	SetValue(TitleProperty, box_value(value));
}

hstring SettingItem::Title() const {
	return GetValue(TitleProperty).as<hstring>();
}

void SettingItem::Description(IInspectable value) {
	SetValue(DescriptionProperty, value);
}

IInspectable SettingItem::Description() const {
	return GetValue(DescriptionProperty);
}

void SettingItem::Icon(IInspectable value) {
	SetValue(IconProperty, value);
}

IInspectable SettingItem::Icon() const {
	return GetValue(IconProperty);
}

void SettingItem::ActionContent(IInspectable value) {
	SetValue(ActionContentProperty, value);
}

IInspectable SettingItem::ActionContent() const {
	return GetValue(ActionContentProperty);
}

void SettingItem::_OnTitleChanged(DependencyObject const& sender, DependencyPropertyChangedEventArgs const&) {
	SettingItem* that = get_self<SettingItem>(sender.as<default_interface<SettingItem>>());
	that->_Update();
	that->_propertyChangedEvent(*that, PropertyChangedEventArgs{ L"Title" });
}

void SettingItem::_OnDescriptionChanged(DependencyObject const& sender, DependencyPropertyChangedEventArgs const&) {
	SettingItem* that = get_self<SettingItem>(sender.as<default_interface<SettingItem>>());
	that->_Update();
	that->_propertyChangedEvent(*that, PropertyChangedEventArgs{ L"Description" });
}

void SettingItem::_OnIconChanged(DependencyObject const& sender, DependencyPropertyChangedEventArgs const&) {
	SettingItem* that = get_self<SettingItem>(sender.as<default_interface<SettingItem>>());
	that->_Update();
	that->_propertyChangedEvent(*that, PropertyChangedEventArgs{ L"Icon" });
}

void SettingItem::_OnActionContentChanged(DependencyObject const& sender, DependencyPropertyChangedEventArgs const&) {
	SettingItem* that = get_self<SettingItem>(sender.as<default_interface<SettingItem>>());
	that->_Update();
	that->_propertyChangedEvent(*that, PropertyChangedEventArgs{ L"ActionContent" });
}

void SettingItem::_Update() {
	DescriptionPresenter().Visibility(Description() == nullptr ? Visibility::Collapsed : Visibility::Visible);
	IconPresenter().Visibility(Icon() == nullptr ? Visibility::Collapsed : Visibility::Visible);
}

void SettingItem::_SetEnabledState() {
	VisualStateManager::GoToState(*this, IsEnabled() ? L"Normal" : L"Disabled", true);
}

void SettingItem::IsEnabledChanged(IInspectable const&, DependencyPropertyChangedEventArgs const&) {
	_SetEnabledState();
}

void SettingItem::Loading(FrameworkElement const&, IInspectable const&) {
	_SetEnabledState();
	_Update();
}

event_token SettingItem::PropertyChanged(PropertyChangedEventHandler const& value) {
	return _propertyChangedEvent.add(value);
}

void SettingItem::PropertyChanged(event_token const& token) {
	_propertyChangedEvent.remove(token);
}

}