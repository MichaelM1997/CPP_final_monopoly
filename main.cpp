#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Board.h"

int main() {
    srand(static_cast<unsigned>(time(0)));

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Could not load font!\n";
        return -1;
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Monopoly");

    // Load the background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("b.jpg")) {
        std::cerr << "Error loading background image!\n";
        return -1;
    }

    // Create the background sprite
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Handle player setup
    std::vector<Player> players;
    int playerCount = 0;
    while (playerCount < 2 || playerCount > 8) {
        std::cout << "Enter number of players (2-8): ";
        std::cin >> playerCount;
    }

    for (int i = 0; i < playerCount; ++i) {
        std::string playerName;
        std::cout << "Enter name for Player " << (i + 1) << ": ";
        std::cin >> playerName;
        players.emplace_back(playerName, "player" + std::to_string(i + 1) + ".png", i + 1);
    }

    // Create the game board
    Board board;
    int currentPlayer = 0;

    // Text to display when a property is bought
    sf::Text purchaseSign;
    purchaseSign.setFont(font);
    purchaseSign.setCharacterSize(24);
    purchaseSign.setFillColor(sf::Color::Red);
    purchaseSign.setPosition(300.f, 350.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // Draw the background
        window.draw(backgroundSprite);

        // Draw players on the board
        for (const auto& player : players) {
            window.draw(player.sprite);
        }

        // Handle the current player's turn
        Player& current = players[currentPlayer];
        if (!current.isBankrupt()) {
            int diceRoll = (rand() % 6 + 1) + (rand() % 6 + 1);
            std::cout << current.name << " rolled a " << diceRoll << "\n";
            current.move(diceRoll);

            Property* landedProperty = board.getSlot(current.position);
            if (landedProperty) {
                if (landedProperty->name == "Go to Jail") {
                    std::cout << current.name << " goes to jail.\n";
                    current.goToJail();
                } else if (landedProperty->isOwned()) {
                    landedProperty->chargeRent(&current, diceRoll);
                } else if (landedProperty->name == "Community Chest" || landedProperty->name == "Chance") {
                    int randomAmount = (rand() % 200) - 100;
                    current.money += randomAmount;
                    std::cout << current.name << (randomAmount >= 0 ? " gained " : " lost ")
                              << abs(randomAmount) << ". New balance: $" << current.money << "\n";
                } else if (landedProperty->name != "Income Tax") {
                    char choice;
                    std::cout << "Buy " << landedProperty->name << " for $" << landedProperty->price << "? (y/n): ";
                    std::cin >> choice;
                    if (choice == 'y' && current.money >= landedProperty->price) {
                        current.money -= landedProperty->price;
                        landedProperty->setOwner(&current);
                        purchaseSign.setString(current.name + " bought " + landedProperty->name);
                    }
                }

                // Handle building on properties
                if (landedProperty->isOwned() && landedProperty->owner == &current && (landedProperty->canBuildHome() || landedProperty->canBuildHotel())) {
                    char buildChoice;
                    std::cout << "Build on " << landedProperty->name << "? (h for home, o for hotel, n for no): ";
                    std::cin >> buildChoice;

                    if (buildChoice == 'h') {
                        landedProperty->buildHome();
                        // std::cout << current.name << " built a home on " << landedProperty->name << ".\n";
                    } else if (buildChoice == 'o') {
                        landedProperty->buildHotel();
                        // std::cout << current.name << " built a hotel on " << landedProperty->name << ".\n";
                    }
                }
            }

            // Check for win condition
            if (current.money > 2000) {
                std::cout << current.name << " has won the game!\n";
                break;
            }

            // Move to the next player
            currentPlayer = (currentPlayer + 1) % players.size();
        } else {
            // Check if all players are bankrupt
            bool allBankrupt = true;
            for (const auto& player : players) {
                if (!player.isBankrupt()) {
                    allBankrupt = false;
                    break;
                }
            }
            if (allBankrupt) {
                std::cout << current.name << " has won by being the last player standing!\n";
                break;
            }
        }

        // Draw purchase information
        window.draw(purchaseSign);

        // Draw houses and hotels on the properties where the current player is standing
        for (const auto& slot : board.slots) {
            if (slot->houses > 0 && slot->owner == &current) {
                slot->updateBuildingPosition(current.sprite.getPosition());
                window.draw(slot->houseSprite);
            }
            if (slot->hasHotel && slot->owner == &current) {
                slot->updateBuildingPosition(current.sprite.getPosition());
                window.draw(slot->hotelSprite);
            }
        }

        window.display();
    }
    return 0;
}
