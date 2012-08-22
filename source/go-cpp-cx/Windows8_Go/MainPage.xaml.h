//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Go {
template <typename TyPlayerUI>
class Player;

struct PointCoords;
}
#include "Stone.hpp"

namespace Windows8_Go
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
    friend class Go::Player<MainPage^>;
	public:
		MainPage();

    private:
        void onInvalidMove (const Go::PointCoords & invalidMove);
        void onWin ();
        void onLoss ();
        void onTie ();

        Go::PointCoords promptForMove ();
        std::wstring promptForName ();
        Go::StoneColor promptForStoneColor ();
        void updateGameState ();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	};
}
