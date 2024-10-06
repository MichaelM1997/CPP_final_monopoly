#include "Board.h"
#include <vector>


// create the list of properties
// name, price, rent, colorGroup, isRailroad, isUtility
std::vector<PropertyData> createPropertyList() {
    return {
        {"Go", 0, 0, "", false, false},
        {"Mediterranean Avenue", 60, 2, "Brown", false, false},
        {"Baltic Avenue", 60, 4, "Brown", false, false},
        {"Reading Railroad", 200, 25, "", true, false},
        {"Electric Company", 150, 0, "", false, true},
        {"Income Tax", 0, 200, "", false, false},
        {"Oriental Avenue", 100, 6, "Light Blue", false, false},
        {"Vermont Avenue", 100, 6, "Light Blue", false, false},
        {"Connecticut Avenue", 120, 8, "Light Blue", false, false},
        {"Jail (Just Visiting)", 0, 0, "", false, false},
        {"St. Charles Place", 140, 10, "Pink", false, false},
        {"Electric Company", 150, 0, "", false, true},
        {"States Avenue", 140, 10, "Pink", false, false},
        {"Virginia Avenue", 160, 12, "Pink", false, false},
        {"Community Chest", 0, 0, "", false, false},
        {"St. James Place", 180, 14, "Orange", false, false},
        {"Tennessee Avenue", 180, 14, "Orange", false, false},
        {"New York Avenue", 200, 16, "Orange", false, false},
        {"Kentucky Avenue", 220, 18, "Red", false, false},
        {"Indiana Avenue", 220, 18, "Red", false, false},
        {"Illinois Avenue", 240, 20, "Red", false, false},
        {"B&O Railroad", 200, 25, "", true, false},
        {"Atlantic Avenue", 260, 22, "Yellow", false, false},
        {"Ventnor Avenue", 260, 22, "Yellow", false, false},
        {"Water Works", 150, 0, "", false, true},
        {"Marvin Gardens", 280, 24, "Yellow", false, false},
        {"Go to Jail", 0, 0, "", false, false},
        {"Pacific Avenue", 300, 26, "Green", false, false},
        {"North Carolina Avenue", 300, 26, "Green", false, false},
        {"Community Chest", 0, 0, "", false, false},
        {"Pennsylvania Avenue", 320, 28, "Green", false, false},
        {"Short Line", 200, 25, "", true, false},
        {"Chance", 0, 0, "", false, false},
        {"Park Place", 350, 35, "Dark Blue", false, false},
        {"Boardwalk", 400, 50, "Dark Blue", false, false}
    };
}

Board::Board() {
    // Get the list of property data
    std::vector<PropertyData> propertyList = createPropertyList();

    // Iterate over the property list and create properties
    for (const auto& data : propertyList) {
        addProperty(data);
    }
}

void Board::addProperty(const PropertyData& data) {
    auto property = std::make_unique<Property>(
        data.name, data.price, data.rent, data.colorGroup, data.isRailroad, data.isUtility
    );
    auto ptr = property.get();
    slots.push_back(std::move(property));

    // If the property has a color group, add it to the group
    if (!data.colorGroup.empty()) {
        colorGroups[data.colorGroup].push_back(ptr);
    }
}

Property* Board::getSlot(int position) {
    return position < slots.size() ? slots[position].get() : nullptr;
}
