#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include <memory>
#include "Property.h"

// Define PropertyData struct here
struct PropertyData {
    std::string name;
    int price;
    int rent;
    std::string colorGroup;
    bool isRailroad;
    bool isUtility;
};

class Board {
public:
    std::vector<std::unique_ptr<Property>> slots;
    std::map<std::string, std::vector<Property*>> colorGroups;
    sf::Sprite boardSprite;
    sf::Texture boardTexture;


    Board();
    void addProperty(const PropertyData& data);    
    Property* getSlot(int position);
    void draw(sf::RenderWindow& window);

};

#endif
