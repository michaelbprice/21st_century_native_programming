#ifndef INCL_PLAYER_HPP__
#define INCL_PLAYER_HPP__

#include <string>
#include <utility>
#include "IPlayer.hpp"
#include "Board.fwd.hpp"
#include "Point.fwd.hpp"
#include "Stone.fwd.hpp"

namespace Go {

template <typename TyPlayerUI>	
class Player : public IPlayer
{
 private:
    TyPlayerUI m_ui;

    Board * m_pBoard; // Non-owning pointer... do NOT delete!

    StoneColor m_stoneColor;
    std::string m_name;
    Stones m_stones;
    size_t m_capturedCount;
 	
 public:
    Player (const std::string & name);

    virtual void addToCaptured (size_t numCaptured);
    virtual size_t calculateScore () const;
    virtual void chooseName ();
    virtual StoneColor chooseStoneColor ();
    virtual const Board & getGameBoard () const;
    virtual const std::string & getName () const;
    virtual StoneColor getStoneColor ();
    virtual bool hasStones () const;
    virtual void notifyGameReady ();
    virtual void notifyLost ();
    virtual void notifyTied ();
    virtual void notifyTurn ();
    virtual void notifyWon ();
    virtual void setGameBoard (Board & board);
    virtual void setStoneColor (StoneColor color);
    virtual PointCoords playStone ();
};

} // namespace Go

#include "Player.tpp"

#endif /* end of include guard: INCL_PLAYER_HPP__ */
