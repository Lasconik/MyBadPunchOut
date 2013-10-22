#ifndef CHARACTERSTATE_HPP
#define CHARACTERSTATE_HPP

#include "../headers/GameState.hpp"
#include "../headers/Character.hpp"
#include "../headers/GUI_Button.hpp"
#include "../headers/GUI_Window.hpp"
#include "../headers/GUI_Container.hpp"

#include <SFML/Graphics/Text.hpp>

#include <string>
#include <vector>

class CharacterState : public GameState {
public:
  virtual void update();
  virtual void render();
  virtual bool enter();
  virtual bool exit();
  virtual void deleteAll();
  virtual StateID::ID getID() const { return m_charMenuID; }

private:
  static const StateID::ID m_charMenuID = StateID::CHARACTER_MENU;
  sf::RenderTexture * m_render;
  GUIWindow * m_window;
  Container * m_container;
  unsigned int m_index1;
  unsigned int m_index2;
  static std::vector<Character *> m_chars;
  std::vector<sf::Text *> m_texts;
  std::vector<Button *> m_buttons;
  void confirmCharacters();

};

#endif
