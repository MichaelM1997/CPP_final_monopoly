#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include <memory>
#include "Property.h"

class Board {
public:
    std::vector<std::unique_ptr<Property>> slots;
    std::map<std::string, std::vector<Property*>> colorGroups;
    sf::Sprite boardSprite;
    sf::Texture boardTexture;


    Board();
    void addStreet(const std::string& name, int price, int rent, const std::string& colorGroup);
    Property* getSlot(int position);
    void draw(sf::RenderWindow& window);

};

#endif
