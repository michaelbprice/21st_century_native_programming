#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include <type_traits>
#include <string>
#include <utility>
#include "IPlayer.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"

namespace Go {

template <typename TyPlayerUI>	
class Player final : public IPlayer
{
 private:
    TyPlayerUI m_ui;

    Board * m_pBoard; // Non-owning pointer... do NOT delete!

    StoneColor m_stoneColor;
    std::wstring m_name;
    Stones m_stones;
    size_t m_capturedCount;
 	
    Player (const Player &);

 public:
    Player (const std::wstring & name, TyPlayerUI ui);

    ~Player () { };

    //Player (const Player &) = delete;
    //Player & operator= (const Player &) = delete;

    //Player (Player &&) = default;
    //Player & operator= (Player &&) = default;

    virtual void addToCaptured (size_t numCaptured) override;
    virtual size_t calculateScore () override;
    virtual void chooseName () override;
    virtual StoneColor chooseStoneColor () override;
    virtual const Board & getGameBoard () const override;
    virtual const std::wstring & getName () const override;
    virtual StoneColor getStoneColor () override;
    virtual bool hasStones () const override;
    virtual void notifyGameReady () override;
    virtual void notifyLost () override;
    virtual void notifyTied () override;
    virtual void notifyTurn () override;
    virtual void notifyWon () override;
    virtual void setGameBoard (Board & board) override;
    virtual void setStoneColor (StoneColor color) override;
    virtual PointCoords playStone () override;
};

} // namespace Go

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
