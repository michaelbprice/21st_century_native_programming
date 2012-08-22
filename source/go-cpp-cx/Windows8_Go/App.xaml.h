//
// App.xaml.h
// Declaration of the App class.
//

#pragma once

#include "App.g.h"
#include "GameController.hpp"
#include "IPlayer.hpp"
#include <future>

namespace Windows8_Go
{
	/// <summary>
	/// Provides application-specific behavior to supplement the default Application class.
	/// </summary>
	ref class App sealed
	{
    private:
        std::unique_ptr<Go::IPlayer> m_playerOne;
        std::unique_ptr<Go::IPlayer> m_playerTwo;
        std::unique_ptr<Go::GameController> m_controller;

        std::future<int> wait_for_it;

    public:
		App();
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ pArgs) override;

	private:
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
	};
}
