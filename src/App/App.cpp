#include "pch.h"
#include "App.h"
#if __has_include("App.g.cpp")
#include "App.g.cpp"
#endif
#include "Win32Utils.h"
#include "Logger.h"
#include "HotkeyService.h"
#include "AppSettings.h"
#include "CommonSharedConstants.h"
#include "MagService.h"


using namespace winrt;
using namespace Windows::UI::Xaml::Media;


namespace winrt::Magpie::App::implementation {

App::App() {
	__super::Initialize();
	
	AddRef();
	m_inner.as<::IUnknown>()->Release();

	// 根据操作系统版本设置样式
	ResourceDictionary resource = Resources();

	// 根据操作系统选择图标字体
	bool isWin11 = Win32Utils::GetOSBuild() >= 22000;
	resource.Insert(
		box_value(L"SymbolThemeFontFamily"),
		FontFamily(isWin11 ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets")
	);

	if (isWin11) {
		// Win11 中更改圆角大小
		resource.Insert(
			box_value(L"ControlCornerRadius"),
			box_value(CornerRadius{ 8,8,8,8 })
		);
		resource.Insert(
			box_value(L"NavigationViewContentGridCornerRadius"),
			box_value(CornerRadius{ 8,0,0,0 })
		);
	}

	_displayInformation = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
}

App::~App() {
	Close();
}

void App::SaveSettings() {
	AppSettings::Get().Save();
}

StartUpOptions App::Initialize(int) {
	StartUpOptions result{};
	
	AppSettings& settings = AppSettings::Get();
	if (!settings.Initialize()) {
		result.IsError = true;
		return result;
	}

	result.IsError = false;
	result.MainWndRect = settings.WindowRect();
	result.IsWndMaximized= settings.IsWindowMaximized();
	result.IsNeedElevated = settings.IsAlwaysRunAsElevated();

	HotkeyService::Get().Initialize();
	MagService::Get().Initialize();

	return result;
}

bool App::IsShowTrayIcon() const noexcept {
	return AppSettings::Get().IsShowTrayIcon();
}

event_token App::IsShowTrayIconChanged(EventHandler<bool> const& handler) {
	return AppSettings::Get().IsShowTrayIconChanged([handler(handler)](bool value) {
		handler(nullptr, value);
	});
}

void App::IsShowTrayIconChanged(event_token const& token) {
	AppSettings::Get().IsShowTrayIconChanged(token);
}

void App::HwndMain(uint64_t value) noexcept {
	if (_hwndMain == (HWND)value) {
		return;
	}

	_hwndMain = (HWND)value;
	_hwndMainChangedEvent(*this, value);
}

void App::MainPage(Magpie::App::MainPage const& mainPage) noexcept {
	if (!mainPage) {
		_mainPage.RootNavigationView().SelectedItem(nullptr);
	}
	_mainPage = mainPage;
}

void App::OnHostWndFocusChanged(bool isFocused) {
	if (isFocused == _isHostWndFocused) {
		return;
	}

	_isHostWndFocused = isFocused;
	_hostWndFocusChangedEvent(*this, isFocused);
}

void App::RestartAsElevated() const noexcept {
	PostMessage(_hwndMain, CommonSharedConstants::WM_RESTART_AS_ELEVATED, 0, 0);
}

}
