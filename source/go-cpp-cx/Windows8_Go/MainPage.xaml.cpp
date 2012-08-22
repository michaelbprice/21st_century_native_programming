//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Point.hpp"
#include "Stone.hpp"

using namespace Windows8_Go;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Go;
using namespace std;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void MainPage::onInvalidMove (const PointCoords & invalidMove)
{
}

void MainPage::onWin ()
{
}

void MainPage::onLoss ()
{
}

void MainPage::onTie ()
{
}


PointCoords MainPage::promptForMove ()
{
    return PointCoords(0,0);
}

wstring MainPage::promptForName ()
{
    Windows::UI::Popups::MessageDialog ^ query = ref new Windows::UI::Popups::MessageDialog(L"What is your name?");
    auto result = query->ShowAsync();
    return result->ToString()->Data();
}

StoneColor MainPage::promptForStoneColor ()
{
    return StoneColor::NONE;
}

void MainPage::updateGameState ()
{
}

