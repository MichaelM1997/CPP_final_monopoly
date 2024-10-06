#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Player;  // Forward declaration

class Property {
public:
    std::string name;
    int price;
    int baseRent;
    Player* owner;
    int houses;
    std::string colorGroup;
    bool isTrain;
    bool isUtility;
    bool mortgaged;
    int homeCost = 100;  // Cost to build a home
    int hotelCost = 200; // Cost to build a hotel
    bool hasHotel;
    sf::Sprite houseSprite; // Sprite for houses
    sf::Sprite hotelSprite; // Sprite for hotel
    sf::Texture houseTexture; // Texture for house
    sf::Texture hotelTexture; // Texture for hotel
    std::vector<sf::Vector2f> housePositions; // Store positions of houses
    std::vector<sf::Vector2f> hotelPositions; 

    Property(const std::string& name, int price, int rent, const std::string& colorGroup = "", bool isRailroad = false, bool isUtility = false);
    
    void setOwner(Player* newOwner);
    bool isOwned() const;
    bool canBuildHome() const;
    bool canBuildHotel() const;
    void buildHome();
    void buildHotel();
    void chargeRent(Player* player, int diceRoll = 0);
    void updateBuildingPosition(const sf::Vector2f& boardPosition);
};

#endif // PROPERTY_H
