#include "../headers/GameState.hpp"
#include "../headers/GUI_Container.hpp"
#include "../headers/GUI_Window.hpp"

#include <SFML/Graphics/RenderTexture.hpp>

#include <string>

class MatchState : public GameState{

public:
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual void deleteAll();
  virtual void checkClose();
  virtual StateID::ID getID() const { return m_matchID; }

private:
  static const StateID::ID m_matchID = StateID::MATCH;
  sf::RenderTexture * m_render;
  Container * m_container;
  GUIWindow * m_window;
  void displayGauges();
  void displayClock();
  void displayCharacters(const unsigned short&, const unsigned short&, const float&, const float&);

};
