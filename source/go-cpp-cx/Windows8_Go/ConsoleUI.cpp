#include "pch.h"
#include "ConsoleUI.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include "Board.hpp"
#include "IPlayer.hpp"
#include "Stone.hpp"

using namespace std;

static const unsigned char kBorderTopLeftChar = '+';
static const unsigned char kBorderTopRightChar = '+';
static const unsigned char kBorderBottomLeftChar = '+';
static const unsigned char kBorderBottomRightChar = '+';
static const unsigned char kBorderTopChar = '=';
static const unsigned char kBorderRightChar = '=';
static const unsigned char kBorderBottomChar = '=';
static const unsigned char kBorderLeftChar = '=';
static const unsigned char kPointChar = '+';
static const unsigned char kPointSpacerChar = '-';

void printBoard (const Go::Board & board)
{
    using namespace Go;

    wcout << " ";
    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
        wcout << i;
    wcout << endl;

    wcout << kBorderTopLeftChar << wstring((9*2)+1, kBorderTopChar) << kBorderTopRightChar << endl;

    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
    {
        wcout << i << kBorderLeftChar;
        for (size_t j = 0; j < board.BOARD_SIZE; ++j)
        {
            wcout << kPointSpacerChar;
            switch (board.getStoneColorAt(PointCoords(i, j)))
            {
             case StoneColor::NONE:  wcout << kPointChar; break;
             case StoneColor::BLACK: wcout << 'B'; break; //'○'; break;
             case StoneColor::WHITE: wcout << 'W'; break; //'◙'; break;
            }
        }
        wcout << kPointSpacerChar << kBorderRightChar << i << endl;
    }

    wcout << kBorderBottomLeftChar << wstring((9*2)+1, kBorderBottomChar) << kBorderBottomRightChar << endl;

    wcout << " ";
    for (size_t i = 0; i < board.BOARD_SIZE; ++i)
        wcout << i;
    wcout << endl;
}

namespace Go
{

ConsoleUI::ConsoleUI (const IPlayer & player)
  : m_player(player)
  , m_updateCount(0)
{ }

void ConsoleUI::onInvalidMove (const PointCoords & invalidMove)
{
    wcout << L"Invalid move [" << invalidMove.row << L"," << invalidMove.column << L"]. Try again!" << endl;
}

void ConsoleUI::onTie ()
{
    wcout << m_player.getName() << L" tied... So close." << endl;
}

void ConsoleUI::onLoss ()
{
    wcout << m_player.getName() << L" loses. Sorry!" << endl;
}

void ConsoleUI::onWin ()
{
    wcout << m_player.getName() << L" WINS!" << endl;
}

PointCoords ConsoleUI::promptForMove ()
{
    wcout << m_player.getName() << L", enter move: ";

    size_t x_coord = 0;
    size_t y_coord = 0;

    cin >> x_coord >> y_coord;

    return PointCoords(x_coord, y_coord);
}

string ConsoleUI::promptForName ()
{
    wcout << L"Name for " << m_player.getName() << L": ";

    string playerName;
    cin >> playerName;

    return playerName;
}

StoneColor ConsoleUI::promptForStoneColor ()
{
    wcout << m_player.getName() << L", would you like to play as Black (0) or White (1): ";

    unsigned short choice = 0;
    cin >> choice;

    assert(choice == 0 || choice == 1);

    return (choice == 0) ? StoneColor::BLACK : StoneColor::WHITE;
}

void ConsoleUI::updateGameState ()
{
    if (m_updateCount == 0)
      wcout << m_player.getName() << L" is ready!" << endl;
    else
    {
      printBoard(m_player.getGameBoard());
    }

    ++m_updateCount;
}

};
