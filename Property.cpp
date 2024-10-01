#include "Property.h"
#include "Player.h"
#include <iostream>

Property::Property(const std::string& propertyName, int propertyPrice, int propertyRent, const std::string& color, bool train, bool utility)
    : name(propertyName), price(propertyPrice), baseRent(propertyRent), owner(nullptr), houses(0), colorGroup(color), isTrain(train), isUtility(utility), mortgaged(false), hasHotel(false) {
    
    if (!houseTexture.loadFromFile("home.png")) {
        std::cerr << "Error loading house texture!\n";
    }
    houseSprite.setTexture(houseTexture);
    houseSprite.setScale(0.04f, 0.04f);  // Adjust the size if needed

    if (!hotelTexture.loadFromFile("hotel.png")) {
        std::cerr << "Error loading hotel texture!\n";
    }
    hotelSprite.setTexture(hotelTexture);
    hotelSprite.setScale(0.04f, 0.04f);  // Adjust the size if needed
}

void Property::setOwner(Player* newOwner) {
    owner = newOwner;
}

bool Property::isOwned() const {
    return owner != nullptr;
}

bool Property::canBuildHome() const {
    return (owner != nullptr) && (houses < 4) && !hasHotel;
}

bool Property::canBuildHotel() const {
    return (owner != nullptr) && (houses == 4) && !hasHotel;
}

void Property::buildHome() {
    if (canBuildHome()) {
        if (owner->money >= homeCost) {
            owner->money -= homeCost;
            houses++;
            std::cout << owner->name << " built a homess on " << name << ". Total houses: " << houses << "\n";
            housePositions.push_back(owner->sprite.getPosition());
        } else {
            std::cout << owner->name << " doesn't have enough money to build a house.\n";
        }
    } else {
        std::cout << "Cannot build more houses on " << name << ".\n";
    }
}

void Property::buildHotel() {
    if (canBuildHotel()) {
        if (owner->money >= hotelCost) {
            owner->money -= hotelCost;
            houses = 0;  // Reset house count
            hasHotel = true;
            std::cout << owner->name << " built a hotel on " << name << ".\n";
            hotelPositions.push_back(owner->sprite.getPosition());
        } else {
            std::cout << owner->name << " doesn't have enough money to build a hotel.\n";
        }
    } else {
        std::cout << "Cannot build a hotel on " << name << " yet. You need 4 houses first.\n";
    }
}

void Property::chargeRent(Player* player, int diceRoll) {
    if (owner && owner != player) {
        if (mortgaged) {
            std::cout << name << " is mortgaged. No rent to be charged.\n";
            return;
        }
        int totalRent = baseRent + (houses * 50);

        if (isTrain) {
            int ownedTrains = 0;
            for (const auto& prop : owner->properties) {
                if (prop->isTrain) {
                    ownedTrains++;
                }
            }
            totalRent = 50 * ownedTrains;
        }
        if (isUtility) {
            totalRent = diceRoll * 10;
        }

        player->payRent(totalRent);
        owner->money += totalRent;
        std::cout << player->name << " paid " << totalRent << " rent to " << owner->name << "\n";
    }
}

void Property::updateBuildingPosition(const sf::Vector2f& boardPosition) {
    if (houses > 0 && !hasHotel) {
        houseSprite.setPosition(boardPosition);
    }
    if (hasHotel) {
        hotelSprite.setPosition(boardPosition);
    }
}
