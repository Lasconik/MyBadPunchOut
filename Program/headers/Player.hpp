/**
   Here we define a player, for the current game session : as in many fight games, we keep the number of victories
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../headers/CharacterPlayed.hpp"

#include <string>

class Player{

private:
  std::string m_name; //name of the player, displayed during the match
  unsigned short m_victories; //number of victories (for global score)
  unsigned short m_points; //number of points in the current match
  CharacterPlayed * m_character; //character chosen by the player

public:
  //constructors
  Player(const std::string& = "Player", CharacterPlayed * = NULL);
  ~Player();
  //getters
  std::string getName() const{
    return m_name; 
  };
  unsigned short getVictories() const{
    return m_victories; 
  };
  unsigned short getPoints() const {
    return m_points; 
  };
  CharacterPlayed * getCharacter() const{
    return m_character; 
  };
  //setters
  void setName(const std::string& value){
    m_name = value;
  };
  void setVictories(const unsigned short& value){
    m_victories = value;
  };
  void setPoints(const unsigned short& value){
    m_points = value;
  };
  void setCharacter(const CharacterPlayed& c){
    m_character->setName( c.getName() );
    m_character->setHealth( c.getHealth() );
    m_character->setCurrentHealth( c.getCurrentHealth() );
    m_character->setAction( c.getAction() );
    m_character->setFrame( c.getFrame() );
    m_character->setResistance( c.getResistance() );
    m_character->setAttack( c.getAttack() );
    m_character->setStamina( c.getStamina() );
  };
  //others
  void resetPoints(){
    m_points = 0;
  };
  void addPoints(const unsigned short& value){
    m_points = ( (m_points+value) <= -1) ? m_points+value : -1;
  };
  void addVictory(){
    m_victories = (m_victories == -1) ? -1 : m_victories+1;
  }
  void manage();
  std::string toString();
};


#endif
