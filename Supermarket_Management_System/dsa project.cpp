#include <iostream>
#include <string>

using namespace std;

class Item {
public:
    int id;
    string name;
    double price;
    int stockQuantity;
    Item* next;

    Item(int _id, const string& _name, double _price, int _stockQuantity)
        : id(_id), name(_name), price(_price), stockQuantity(_stockQuantity), next(nullptr) {}
};

class LinkedList {
private:
    Item* head;

public:
    LinkedList() : head(nullptr) {}

    void addItem(int id, const string& name, double price, int stockQuantity) {
        Item* newItem = new Item(id, name, price, stockQuantity);
        newItem->next = head;
        head = newItem;
        cout << "Item added successfully." << endl;
    }

    void deleteItem(int id) {
        Item* current = head;
        Item* prev = nullptr;

        while (current != nullptr && current->id != id) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr) {
            if (prev != nullptr) {
                prev->next = current->next;
            } else {
                head = current->next;
            }

            delete current;
            cout << "Item deleted successfully." << endl;
        } else {
            cout << "Item not found." << endl;
        }
    }

    void showAllItems() const {
        Item* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->id << "\tName: " << current->name
                 << "\tPrice: $" << current->price << "\tStock Quantity: " << current->stockQuantity << endl;
            current = current->next;
        }
    }

    Item* searchById(int id) const {
        Item* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    Item* searchByName(const string& name) const {
        Item* current = head;
        while (current != nullptr) {
            if (current->name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Item* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class ArrayStack {
private:
    static const int MAX_SIZE = 100;
    string data[MAX_SIZE];
    int top;

public:
    ArrayStack() : top(-1) {}

    void push(const string& message) {
        if (top < MAX_SIZE - 1) {
            data[++top] = message;
        } else {
            cerr << "Stack overflow\n";
        }
    }

    void pop() {
        if (!isEmpty()) {
            --top;
        } else {
            cerr << "Stack underflow\n";
        }
    }

    bool isEmpty() const {
        return top == -1;
    }

    const string& topMessage() const {
        if (!isEmpty()) {
            return data[top];
        }
        throw runtime_error("Stack is empty");
    }
};

class Supermarket {
private:
    LinkedList itemList;
    ArrayStack warningMessages;

public:
    void addItem(int id, const string& name, double price, int stockQuantity) {
        itemList.addItem(id, name, price, stockQuantity);
        if (stockQuantity < 5) {
            warningMessages.push("Low stock warning for item: " + name);
        }
    }

    void deleteItem(int id) {
        itemList.deleteItem(id);
    }

    void showAllItems() const {
        itemList.showAllItems();
    }

    void searchItemById(int id) const {
        Item* item = itemList.searchById(id);
        if (item != nullptr) {
            cout << "ID: " << item->id << "\tName: " << item->name
                 << "\tPrice: $" << item->price << "\tStock Quantity: " << item->stockQuantity << endl;
        } else {
            cout << "Item not found." << endl;
        }
    }

    void searchItemByName(const string& name) const {
        Item* item = itemList.searchByName(name);
        if (item != nullptr) {
            cout << "ID: " << item->id << "\tName: " << item->name
                 << "\tPrice: $" << item->price << "\tStock Quantity: " << item->stockQuantity << endl;
        } else {
            cout << "Item not found." << endl;
        }
    }

    void makeBill(int id) {
        Item* item = itemList.searchById(id);
        if (item != nullptr && item->stockQuantity > 0) {
            cout << "Item added to the bill: " << item->name << endl;
            item->stockQuantity--;
            if (item->stockQuantity < 5) {
                warningMessages.push("Low stock warning for item: " + item->name);
            }
        } else {
            cout << "Item not available in stock." << endl;
        }
    }

    void showWarningMessages() {
        cout << "Warning Messages:\n";
        while (!warningMessages.isEmpty()) {
            cout << warningMessages.topMessage() << endl;
            warningMessages.pop();
        }
    }
};

void task_entry(string array[], const string& str) {
    for (int i = 0; i < 10; i++) {
        array[i] = str;
    }
}

void display_tasks(const string array[]) {
    cout << "\nTasks Are:";
    for (int i = 0; i < 10; i++) {
        cout << array[i];
    }
}
int main() {
    Supermarket supermarket;
    int item_id, price, quanti;
    string item_name;
    int choice_variable;
    string task_manager[100];

    while (true) {
        // Display menu options
        cout << "Enter 1 for adding item :" << endl;
        cout << "Enter 2 for deleting item :" << endl;
        cout << "Enter 3 for showing all item list :" << endl;
        cout << "Enter 4 for search by id :" << endl;
        cout << "Enter 5 for search by name :" << endl;
        cout << "Enter 6 for making a bill :" << endl;
        cout << "Enter 7 for displaying warning :" << endl;
        cout << "Enter 8 for task manager :" << endl;
        cout << "Enter 0 to exit :" << endl;

        // Get user input
        cin >> choice_variable;

        if (choice_variable == 0) {
            // Exit the loop if the user chooses to exit
            break;
        }

        // Handle user choices
        switch (choice_variable) {
            case 1: {
                cout << "\nEnter name of Item: ";
                cin >> item_name;

                cout << "\nEnter id of Item: ";
                cin >> item_id;

                cout << "\nEnter Quantity of Item: ";
                cin >> quanti;

                cout << "\nEnter Price of Item: ";
                cin >> price;
                supermarket.addItem(item_id, item_name, price, quanti);
                break;
            }
            case 2: {
                cout << "\nENTER ID TO DELETE ITEM:";
                cin >> item_id;
                supermarket.deleteItem(item_id);
                break;
            }
            case 3: {
                cout << "\nShowing all item list:";
                supermarket.showAllItems();
                break;
            }
            case 4: {
                cout << "\nEnter id to search:";
                cin >> item_id;
                supermarket.searchItemById(item_id);
                break;
            }
            case 5: {
                cout << "\nEnter Name:";
                cin >> item_name;
                supermarket.searchItemByName(item_name);
                break;
            }
            case 6: {
                cout << "\nEnter 0 when billing complete";
                int var;
                cout << "\nBilling:";
                while (true) {
                    cout << "\nEnter Id of Item to bill:";
                    cin >> var;
                    if (var == 0) {
                        break;
                    } else {
                        supermarket.makeBill(var);
                    }
                }
                break;
            }
            case 7: {
                cout << "\n.........WARNINGS..........:";
                supermarket.showWarningMessages();
                break;
            }
            case 8: {
                int t_manager_choice;
                cout << "\nEnter 1 TO ADD TASKS";
                cout << "\nEnter 2 TO Show all TASKS";
                cin >> t_manager_choice;
                if (t_manager_choice == 1) {
                    cout << "\n....Task Manager....";
                    string task;
                    getline(cin, task);
                    task_entry(task_manager, task);
                } else if (t_manager_choice == 2) {
                    display_tasks(task_manager);
                }
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}