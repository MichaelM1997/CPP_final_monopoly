#include "Player.h"
#include "Property.h"
#include <iostream>
#include <vector>

Player::Player(const std::string& playerName, const std::string& textureFile, int number)
    : name(playerName), money(1500), position(0), inJail(false), jailTurns(0), hasGetOutOfJailCard(false), playerNumber(number) {
    
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture for player " << playerName << "\n";
    }

    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.05f); // Adjust sprite size if necessary
    updatePositionOnBoard(); // Place player at the starting position
}

void Player::move(int steps) {
    position = (position + steps) % 40; // Wrap around the board
    updatePositionOnBoard();
}

void Player::updatePositionOnBoard() {
    std::vector<sf::Vector2f> boardPositions = {
        {720.f, 720.f}, {640.f, 720.f}, {560.f, 720.f}, {480.f, 720.f}, {400.f, 720.f},
        {320.f, 720.f}, {240.f, 720.f}, {160.f, 720.f}, {80.f, 720.f}, {0.f, 720.f},
        {0.f, 640.f}, {0.f, 560.f}, {0.f, 480.f}, {0.f, 400.f}, {0.f, 320.f},
        {0.f, 240.f}, {0.f, 160.f}, {0.f, 80.f}, {0.f, 0.f},
        {80.f, 0.f}, {160.f, 0.f}, {240.f, 0.f}, {320.f, 0.f}, {400.f, 0.f},
        {480.f, 0.f}, {560.f, 0.f}, {640.f, 0.f}, {720.f, 0.f},
        {720.f, 80.f}, {720.f, 160.f}, {720.f, 240.f}, {720.f, 320.f}, {720.f, 400.f},
        {720.f, 480.f}, {720.f, 560.f}, {720.f, 640.f}
    };

    if (position < boardPositions.size()) {
        sprite.setPosition(boardPositions[position]);
    } else {
        std::cerr << "Invalid board position!\n";
    }
}

bool Player::isBankrupt() const {
    return money < 0;
}

void Player::payRent(int amount) {
    money -= amount;
    std::cout << name << " paid $" << amount << " in rent. Remaining money: $" << money << "\n";
    if (isBankrupt()) {
        std::cout << name << " is bankrupt!\n";
    }
}

void Player::buyProperty(Property* property) {
    if (money >= property->price && !property->isOwned()) {
        money -= property->price;
        property->setOwner(this);
        properties.push_back(property);
        std::cout << name << " bought " << property->name << " for $" << property->price << "\n";
    } else {
        std::cout << name << " cannot buy " << property->name << ". Insufficient funds or already owned.\n";
    }
}

void Player::goToJail() {
    inJail = true;
    position = 10; // Assuming position 10 is "Jail"
    std::cout << name << " went to jail!\n";
}
