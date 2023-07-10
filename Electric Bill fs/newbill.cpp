#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Customer {
    std::string id;
    std::string name;
    double unitsConsumed;
    double billAmount;
};

std::vector<Customer> customers;

void addCustomer() {
    Customer customer;
    std::cout << "Enter customer name: ";
    std::cin.ignore();
    std::getline(std::cin, customer.name);
    std::cout << "Enter units consumed: ";
    std::cin >> customer.unitsConsumed;
    customer.billAmount = customer.unitsConsumed * 0.10 * 74.50; 
    
    // Generate unique ID
    std::string uniqueID = "C" + std::to_string(customers.size() + 1);
    customer.id = uniqueID;
    
    customers.push_back(customer);
    std::cout << "Customer added successfully! ID: " << uniqueID << std::endl;
}

void generateBill() {
    std::string customerID;
    std::cout << "Enter customer ID: ";
    std::cin.ignore();
    std::getline(std::cin, customerID);

    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer& customer) {
        return customer.id == customerID;
    });

    if (it != customers.end()) {
        std::ofstream file("bills.txt", std::ios_base::trunc); // Open the file in truncation mode

        for (const auto& customer : customers) {
            file << "Customer ID: " << customer.id << std::endl;
            file << "Customer name: " << customer.name << std::endl;
            file << "Units consumed: " << customer.unitsConsumed << std::endl;
            file << "Bill amount: " << customer.billAmount << std::endl;
            file << "-----------------------" << std::endl;
        }
        file.close();

        std::cout << "Bill generated and stored successfully!" << std::endl;
    } else {
        std::cout << "Customer not found!" << std::endl;
    }
}


void displayBills() {
    std::ifstream file("bills.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
    
    if (file.eof()) {
        std::cout << "End of bill records." << std::endl;
    } else {
        std::cout << "Error occurred while reading bill records." << std::endl;
    }
}

void displayIndividualBill() {
    std::string customerID;
    std::cout << "Enter customer ID: ";
    std::cin.ignore();
    std::getline(std::cin, customerID);
    
    std::ifstream file("bills.txt");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line.find("Customer ID: " + customerID) != std::string::npos) {
            std::cout << line << std::endl;
            for (int i = 0; i < 3; i++) {
                std::getline(file, line);
                std::cout << line << std::endl;
            }
            found = true;
            break;
        }
    }
    file.close();
    
    if (!found) {
        std::cout << "Customer not found!" << std::endl;
    }
}

void deleteBill() {
    std::string customerID;
    std::cout << "Enter customer ID: ";
    std::cin.ignore();
    std::getline(std::cin, customerID);
    
    auto it = std::find_if(customers.begin(), customers.end(), [&](const Customer& customer) {
        return customer.id == customerID;
    });
    
    if (it != customers.end()) {
        customers.erase(it);
        std::cout << "Bill deleted successfully!" << std::endl;

        std::ofstream file("bills.txt");
        for (const auto& customer : customers) {
            file << "-----------------------" << std::endl;
            file << "Customer ID: " << customer.id << std::endl;
            file << "Customer name: " << customer.name << std::endl;
            file << "Units consumed: " << customer.unitsConsumed << std::endl;
            file << "Bill amount: " << customer.billAmount << std::endl;
            file << "-----------------------" << std::endl;
        }
        file.close();
    } else {
        std::cout << "Customer not found!" << std::endl;
    }
}

int main() {
    int choice;
    while (true) {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Electric Bill System" << std::endl;
        std::cout << "1. Add Customer" << std::endl;
        std::cout << "2. Generate Bill" << std::endl;
        std::cout << "3. Display Bills" << std::endl;
        std::cout << "4. Display Individual Bill" << std::endl;
        std::cout << "5. Delete Bill" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "-----------------------" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                generateBill();
                break;
            case 3:
                displayBills();
                break;
            case 4:
                displayIndividualBill();
                break;
            case 5:
                deleteBill();
                break;
            case 6:
                std::cout << "Exiting program..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
        
        std::cout << std::endl;
    }
}
