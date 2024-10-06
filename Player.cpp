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
    sprite.setScale(0.01f, 0.03f); // Adjust sprite size if necessary
    updatePositionOnBoard(); // Place player at the starting position
}

void Player::move(int steps) {
    position = (position + steps) % 40; // Wrap around the board
    updatePositionOnBoard();
}

void Player::updatePositionOnBoard() {
    const float boardSize = 800.f;     // Size of the board (assuming 800x800)
    const int totalPositions = 40;     // Total number of positions on the board
    const int tilesPerSide = 10;       // Number of tiles on each side
    const float tileSize = boardSize / tilesPerSide; // Size of each tile

    sf::Vector2f newPosition;

    int pos = position % totalPositions;

    if (pos >= 0 && pos < 10) {
        // Bottom edge (from Go to Jail)
        newPosition.x = boardSize - tileSize * (pos + 1);
        newPosition.y = boardSize - tileSize;
    } else if (pos >= 10 && pos < 20) {
        // Left edge (from Jail to Free Parking)
        newPosition.x = 0;
        newPosition.y = boardSize - tileSize * (20 - pos);
    } else if (pos >= 20 && pos < 30) {
        // Top edge (from Free Parking to Go to Jail)
        newPosition.x = tileSize * (pos - 20);
        newPosition.y = 0;
    } else if (pos >= 30 && pos < 40) {
        // Right edge (from Go to Jail to Go)
        newPosition.x = boardSize - tileSize;
        newPosition.y = tileSize * (pos - 30);
    } else {
        std::cerr << "Invalid board position!\n";
        return;
    }

    sprite.setPosition(newPosition);
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
