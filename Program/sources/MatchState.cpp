#include "../headers/MatchState.hpp"
#include "../headers/GameState.hpp"
#include "../headers/Action.hpp"
#include "../headers/CharacterPlayed.hpp"
#include "../headers/Config.hpp"
#include "../headers/Game.hpp"
#include "../headers/SpritesheetManager.hpp"
#include "../headers/TextureManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <string>

const std::string MatchState::m_matchID = "MATCH";

void MatchState::update(){
  if(Game::getInstance()->getClock()->getElapsedTime().asSeconds() >= 1){
    Game::getInstance()->addTime(sf::seconds(1) );
    Game::getInstance()->getClock()->restart();
  }
  sf::Event event;
  while( Game::getInstance()->getWindow()->pollEvent(event) ){
    if(event.type == sf::Event::Closed){
      Game::getInstance()->close();
    }else if(event.type ==sf::Event::KeyPressed ){
      action a = Config::getInstance()->getAction( (Key)event.key.code);
      if(a == (action)0 )
	break;
      if(Action::getType(a) == Action::PAUSE ){
	//Game::getInstance()->getStateHandler()->push(new PauseState() );
	break;
      }
      
      if(Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->getAction() == Action::NONE ){
	if(
	   !( ( (Action::getType(a) == Action::ATTACK_LEFT)
		||(Action::getType(a) == Action::ATTACK_MIDDLE)
		||(Action::getType(a) == Action::ATTACK_RIGHT) )
	      && !Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->doHit() )
	   )
	  Game::getInstance()->getMatch()->getCharacter(Action::getDoer(a) )->setAction( Action::getType(a) );
      }else{
	//player is already performing an action
      }
    }

  }
  Game::getInstance()->getMatch()->manage();
}


void MatchState::render(){
  //drawing order : 
  //background, opponent, opponent's spec, player's spec, player,
  // background
  m_render->clear();
  //m_view1->setViewport(sf::FloatRect(0, 0, 800, 600) );
  displayCharacters(0, 1, -200, 0);
  //displayCharacters(1, 0, Config::getInstance()->getWindowWidth(), 0 ); 
  displayCharacters(1, 0, 200, 0 );
  displayGauges();
  displayClock();
  m_window->draw();
}


void MatchState::displayGauges(){
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter1();
  CharacterPlayed * c2 = Game::getInstance()->getMatch()->getCharacter2();
  // health bars : red, green, border
  sf::Sprite s;
  sf::Texture * t;
  float width = Config::getInstance()->getWindowWidth();
  // opponent
  //opponent's spec
  //player's spec
  //player
  float scale = 2.0;
  s.scale(scale, scale);
  //p1 red
  t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  s.setTexture(*t);
  s.setTextureRect(sf::IntRect(0, 0, 156, 16) );
  s.setPosition (sf::Vector2f(0, 26) );
  m_render->draw(s);
  //p1 green
  float percent = 0.0+c1->getCurrentHealth();
  percent /= c1->getHealth();
  percent *= 150;
  s.setTextureRect(sf::IntRect(0, 16, 3+(percent), 16) );
  m_render->draw(s);
  //p2 red
  s.setTextureRect(sf::IntRect(0, 0, 156, 16) );
  s.setPosition (sf::Vector2f(width-156*scale, 26) );
  m_render->draw(s);
  //p2 green
  percent = 0.0+c2->getCurrentHealth();
  percent /= c2->getHealth();
  percent *= 150;
  s.setPosition (sf::Vector2f(width-(156-(150-percent) )*scale, 26) );
  s.setTextureRect(sf::IntRect(0, 16, 4+percent, 16) );
  m_render->draw(s);
 
  //stamina bars
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(0, 70) );
  m_render->draw(s);
  percent = 0.0+c1->getCurrentStamina();
  percent /= c1->getStamina();
  percent *= 100;
  s.setTextureRect(sf::IntRect(0, 40, 2+percent, 6) );
  m_render->draw(s);
  //p2
  s.setTextureRect(sf::IntRect(0, 32, 104, 8) );
  s.setPosition(sf::Vector2f(width-104*scale, 70) );
  m_render->draw(s);
  percent = 0.0+c2->getCurrentStamina();
  percent /= c2->getStamina();
  percent *= 100;
  s.setPosition(sf::Vector2f(width-(104-(100-percent) )*scale, 70 ) );
  s.setTextureRect(sf::IntRect(0, 40, 3+percent, 6) );
  m_render->draw(s);
  
}

void MatchState::displayClock(){
  // chrono : back, second 100, second 10, second 1
  sf::Sprite s;
  sf::Texture * t = TextureManager::getInstance()->get("sprites.png")->getTexture();
  float width = Config::getInstance()->getWindowWidth();
  s.setTextureRect(sf::IntRect(0, 46, 128, 64) );
  s.setPosition(width/2-64, 10);
  s.setTexture(*t);
  m_render->draw(s);  
  unsigned short time;
  time = Game::getInstance()->getMatch()->getTimePerRound()-(Game::getInstance()->getTimer()->asSeconds() );
  if(time > 0){ // if time is infinity, we are not displaying time
    //displaying 100'
    s.setTextureRect(sf::IntRect( (28*(time/100) ), 111, 28, 36) );
    s.setPosition(width/2-64+16, 10+ 14);
    m_render->draw(s);
    //displaying 10'
    s.setTextureRect(sf::IntRect((28*(time%100/10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+34, 10+ 14);
    m_render->draw(s);
    //displaying 1'
    s.setTextureRect(sf::IntRect((28*(time%10) ), 111, 28, 36) );
    s.setPosition(width/2-64+16+68, 10+ 14);
    m_render->draw(s);
  }
  
}

void MatchState::displayCharacters(const unsigned short& p_front, const unsigned short& p_back, const float& decX, const float& decY){
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter(p_front);
  CharacterPlayed * c2 = Game::getInstance()->getMatch()->getCharacter(p_back);
  sf::Sprite s;
  Spritesheet * ss;
  //displaying background
  sf::Texture * t = TextureManager::getInstance()->get("background.png")->getTexture();
  s.setTexture(*t);
  s.setPosition(sf::Vector2f(200+decX, 50+decY) );
  m_render->draw(s);
  //displaying players' sprites : we need the image, the spritesheet, and the current frame of the action
  std::string file = "characters/";
  // character 2
  file += c2->getBasename();
  file += "_front.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = c2->getBasename();
  file += "_front.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400+decX, 400+decY  );
  unsigned short idSprite = ss->getAnimation(c2->getAction() ).get(c2->getFrame() ); 
  Sprite * sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    //s.scale(2.0, 2.0);
    m_render->draw(s);
  }
  // character 1
  file = "characters/";
  file += c1->getBasename();
  file += "_back.png";
  t = TextureManager::getInstance()->get(file)->getTexture();
  file = c1->getBasename();
  file += "_back.sprt";
  ss = SpritesheetManager::getInstance()->get(file);
  s.setTexture(*t);
  s.setPosition( 400+decX, 600+decY );
  idSprite = ss->getAnimation(c1->getAction() ).get(c1->getFrame() );
  sprt = ss->getSprite(idSprite);
  if(sprt){
    s.setTextureRect(sf::IntRect(sprt->getPositionX(), sprt->getPositionY(), sprt->getWidth(), sprt->getHeight() ) );
    s.setOrigin( sprt->getHotpointX(), sprt->getHotpointY()  );
    //s.scale(1.25, 1.25);
    m_render->draw(s);
  }
}


bool MatchState::enter(){
  Game::getInstance()->getMusic()->stop();
  sf::Texture * t = TextureManager::getInstance()->get("loading")->getTexture();
  sf::Sprite s;
  CharacterPlayed * c1 = Game::getInstance()->getMatch()->getCharacter1();
  CharacterPlayed * c2 =Game::getInstance()-> getMatch()->getCharacter2();
  s.setTexture(*t);
  s.setPosition(0,0);
  Game::getInstance()->getWindow()->draw(s);
  Game::getInstance()->getWindow()->display();
  TextureManager::getInstance()->get("background.png")->getTexture();
  TextureManager::getInstance()->get("sprites.png")->getTexture();
  std::string file = "characters/";
  // character 2
  file += c2->getBasename();
  file += "_front.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c2->getBasename();
  file += "_front.sprt";
  SpritesheetManager::getInstance()->get(file);
  file = "characters/";
  file += c1->getBasename();
  file += "_back.png";
  TextureManager::getInstance()->get(file)->getTexture();
  file = c1->getBasename();
  file += "_back.sprt";
  SpritesheetManager::getInstance()->get(file);
  *Game::getInstance()->getTimer() = sf::microseconds(0);
  Game::getInstance()->getClock()->restart();
  if(Game::getInstance()->getMusic()->openFromFile("../../resources/audio/battle1.ogg") )
    Game::getInstance()->getMusic()->play();
  c1->gainStamina(600);
  c2->gainStamina(600);
  m_render = Game::getInstance()->getRender();
  m_container = new Container(m_render );
  m_window = new GUIWindow (Game::getInstance()->getWindow(), m_container);
  return true;
}


bool MatchState::exit(){
  //delete m_container;
  //delete m_window;
  //delete m_render;
  return true;
}

void MatchState::deleteAll(){
  delete m_container;
  delete m_window;
  // delete m_render;

}
