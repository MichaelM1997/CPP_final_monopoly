#include "Board.h"

Board::Board() {
    // Starting positions
    slots.push_back(std::make_unique<Property>("Go", 0, 0));
    addStreet("Mediterranean Avenue", 60, 2, "Brown");
    addStreet("Baltic Avenue", 60, 4, "Brown");
    slots.push_back(std::make_unique<Property>("Reading Railroad", 200, 25, "", true));
    slots.push_back(std::make_unique<Property>("Electric Company", 150, 0, "", false, true));
    slots.push_back(std::make_unique<Property>("Income Tax", 0, 200));
    addStreet("Oriental Avenue", 100, 6, "Light Blue");
    addStreet("Vermont Avenue", 100, 6, "Light Blue");
    addStreet("Connecticut Avenue", 120, 8, "Light Blue");
    slots.push_back(std::make_unique<Property>("Jail (Just Visiting)", 0, 0));
    
    // Continue adding properties from the traditional board
    slots.push_back(std::make_unique<Property>("St. Charles Place", 140, 10, "Pink"));
    slots.push_back(std::make_unique<Property>("Electric Company", 150, 0, "", false, true));
    addStreet("States Avenue", 140, 10, "Pink");
    addStreet("Virginia Avenue", 160, 12, "Pink");
    slots.push_back(std::make_unique<Property>("Community Chest", 0, 0));
    slots.push_back(std::make_unique<Property>("St. James Place", 180, 14, "Orange"));
    addStreet("Tennessee Avenue", 180, 14, "Orange");
    addStreet("New York Avenue", 200, 16, "Orange");
    slots.push_back(std::make_unique<Property>("Kentucky Avenue", 220, 18, "Red"));
    addStreet("Indiana Avenue", 220, 18, "Red");
    addStreet("Illinois Avenue", 240, 20, "Red");
    slots.push_back(std::make_unique<Property>("B&O Railroad", 200, 25, "", true));
    slots.push_back(std::make_unique<Property>("Atlantic Avenue", 260, 22, "Yellow"));
    slots.push_back(std::make_unique<Property>("Ventnor Avenue", 260, 22, "Yellow"));
    slots.push_back(std::make_unique<Property>("Water Works", 150, 0, "", false, true));
    addStreet("Marvin Gardens", 280, 24, "Yellow");
    slots.push_back(std::make_unique<Property>("Go to Jail", 0, 0));
    addStreet("Pacific Avenue", 300, 26, "Green");
    addStreet("North Carolina Avenue", 300, 26, "Green");
    slots.push_back(std::make_unique<Property>("Community Chest", 0, 0));
    slots.push_back(std::make_unique<Property>("Pennsylvania Avenue", 320, 28, "Green"));
    slots.push_back(std::make_unique<Property>("Short Line", 200, 25, "", true));
    slots.push_back(std::make_unique<Property>("Chance", 0, 0));
    addStreet("Park Place", 350, 35, "Dark Blue");
    slots.push_back(std::make_unique<Property>("Boardwalk", 400, 50, "Dark Blue"));
}


void Board::addStreet(const std::string& name, int price, int rent, const std::string& colorGroup) {
    auto street = std::make_unique<Property>(name, price, rent, colorGroup);
    auto ptr = street.get();
    slots.push_back(std::move(street));
    colorGroups[colorGroup].push_back(ptr);
}

Property* Board::getSlot(int position) {
    return position < slots.size() ? slots[position].get() : nullptr;
}

