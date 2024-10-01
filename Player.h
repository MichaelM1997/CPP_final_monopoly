#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Property;  // Forward declaration

class Player {
public:
    std::string name;
    int money;
    int position;
    bool inJail;
    int jailTurns;
    bool hasGetOutOfJailCard;
    std::vector<Property*> properties;
    sf::Sprite sprite;
    int playerNumber;
    sf::Texture texture; // Unique texture for each player

    Player(const std::string& playerName, const std::string& textureFile, int number);
    
    void move(int steps);
    void updatePositionOnBoard();
    bool isBankrupt() const;
    void payRent(int amount);
    void buyProperty(Property* property);
    void goToJail();
};

#endif // PLAYER_H
