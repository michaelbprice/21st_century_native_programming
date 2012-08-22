#ifndef INCL_PLAYER_FWD_HPP__
#define INCL_PLAYER_FWD_HPP__

#include <functional>

namespace Go {

class IPlayer;
typedef std::pair<std::reference_wrapper<IPlayer>, std::reference_wrapper<IPlayer>> PlayerPair;

} // namespace Go

#endif /* end of include guard: INCL_PLAYER_FWD_HPP__ */
