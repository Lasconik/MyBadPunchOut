#ifndef ACTION_HPP
#define ACTION_HPP

#include "../headers/Misc.hpp"

#include <string>

typedef byte action;
/** An action can be described in one byte:
 ABCDEFGH with
A = 0-1 for action's maker
B= 0-1 for action's target (optionnal)
CDEFGH = 000000-111111 for action term (up to 64 actions) 
*/

namespace Action{
  typedef enum{
    UNKNOWN = 0,
    ATTACK_LEFT = 1,
    ATTACK_MIDDLE,
    ATTACK_RIGHT,
    DODGE_LEFT,
    DODGE_MIDDLE,
    DODGE_RIGHT,
    KO,
    SUPER_STRIKE,
    PAUSE,
    ACTIONS_COUNT
  } Type;
  
  typedef enum{
    PLAYER1 = 0,
    PLAYER2
  } Subject;

  Type getType(const action&);

  Subject getTarget(const action&);

  Subject getDoer(const action&);

  byte actionToByte(const Action::Type&, const Action::Subject& doer = Action::PLAYER1, const Action::Subject& target = Action::PLAYER1);

  byte targetToByte(const Action::Subject&);

  byte doerToByte(const Action::Subject&);

  std::string actionToString(const action&);
}



#endif
