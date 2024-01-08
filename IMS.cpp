#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(std::string name, int quantity, float price)
        : name(std::move(name)), quantity(quantity), price(price) {}

    std::string get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string &other) const {
        return name == other;
    }
};

class Inventory {
private:
    std::vector<Item> items;
    float total_money;

    static void display_data(const Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

public:
    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // more generic approach in ignoring characters in input buffer.
        std::cout << "\nEnter item name: ";
        std::getline(std::cin, name);
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        items.emplace_back(name, quantity, price);
    }

    void sell_item() {
        std::string item_to_check;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter item name: ";
        std::getline(std::cin, item_to_check);

        auto it = std::find_if(items.begin(), items.end(),
                               [item_to_check](const Item &item) {
                                   return item.is_match(item_to_check);
                               });

        if (it != items.end()) {
            remove_item(it);
        } else {
            std::cout << "\nThis item is not in your Inventory";
        }
    }

    void remove_item(std::vector<Item>::iterator item_iter) {     // function can handle erasing items from the middle of the vector without causing issues
        int input_quantity;
        Item &item = *item_iter;
        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item.get_quantity();
        if (input_quantity <= quantity) {
            float price = item.get_price();
            float money_earned = price * input_quantity;
            item.set_quantity(quantity - input_quantity);

            if (item.get_quantity() == 0) {
                // Completely remove the item from the vector if its quantity is zero
                items.erase(item_iter);
            }

            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() const {
        if (items.empty()) {
            std::cout << "\nInventory empty.";
            return;
        }

        for (const auto &item : items) {
            display_data(item);
            std::cout << "\n";
        }
    }
};

int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (true) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                return 0;

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}