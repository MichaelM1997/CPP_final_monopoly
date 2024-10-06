# Monopoly Game

This project is a simplified implementation of the classic Monopoly board game using C++ and SFML library.

## Features

- Multiple players (2-8)
- Graphical board representation
- Dice rolling and player movement
- Property buying and rent collection
- Building houses and hotels
- Bankruptcy and win conditions

## How to Play

1. Start the game and enter the number of players (2-8).
2. Enter names for each player.
3. Players take turns rolling the dice and moving around the board.
4. Land on properties to buy them or pay rent to other players.
5. Build houses and hotels to increase the rent on your properties.
6. The game ends when all but one player go bankrupt, or when a player reaches $2000.

## Project Structure

- `main.cpp`: Main game loop and SFML window management
- `Board.cpp` / `Board.h`: Manages the game board and properties
- `Player.cpp` / `Player.h`: Player logic and movement
- `Property.cpp` / `Property.h`: Property management and rent calculation
