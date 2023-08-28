#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

class Game {
 public:
  Game(const string &title, int quantity, double game_price) : game_title(title), game_quantity(quantity), game_price(price) {}
  void set_game(int new_quantity) { game_quantity = new_quantity; }
  string get_title() const { return game_title; }
  int get_quantity() const { return game_quantity; }
  double get_price() const { return game_price; }

 private: 
  string game_title;
  int game_quantity;
  double game_price;
};

class Customer {
 public:
  Customer(double funds = 0.0) : funds(funds) {}
  void set_funds(double new_funds) { funds = new_funds; }
  double get_funds() const { return funds; }

 private:
  double funds
};

class Sale {
 public:
  Sale(const Customer &customer, const Game &game, int quantity) : customer(customer), game(game), quantity(quantity) {}
  const Customer &get_customer() const { return customer; }
  const Game &get_game() const { return game; }
  int get_quantity() const { return quantity; }

 private:
  Customer customer;
  Game game;
  int quantity;
};

class Store {
 public:
  void AddGame(const Game& game) { games.push_back(game); }
  void MakeSale(const Sale &sale);

  void DisplayMenu() const;  // For User Interaction. 
  void DisplayGame() const;
  
  const vector<Game> &get_game() const { return games; }

  bool SaveDataToFile(const string &game_file) const;
  bool LoadDataFromFile(const string &game_file);

 private:
  vector<Game> games;
};

void Store::MakeSale(const Sale &sale) {
  Game game = const_cast<Game&>(sale.get_game());
  Customer customer = const_cast<Customer&>(sale.get_customer());

  if (game.get_quantity() >= sale.get_quantity()) {
    const double california_tax = 0.1025;
    double subtotal = game.get_price() * sale.get_quantity();
    double taxes = subtotal * california_tax;
    double total = subtotal + taxes;
    if (customer.get_funds() >= total) {
      game.set_quantity(game.get_quantity() - sale.get_quantity());
      customer.set_funds(customer.get_funds() - total);
      cout << "Sale Successful. Thank you for shopping with us. Have a wonderful day!" << endl;
    } else {
        cerr << "Error: Insufficient funds" << endl;
    }
  } else {
      cerr << "Error: Insufficient quantity of " << game.get_title() << " in stock." << endl;
  }
}

void DisplayMenu() const {
  cout << "===== Sales Management System Menu =====" << endl;
  cout << "1. Add Game" << endl;
  cout << "2. Display Available Game" << endl;
  cout << "3. Make Sale" << endl;
  cout << "4. Save Data to File" << endl;
  cout << "5. Exit" << endl;
  cout << "Your Selection >> ";
}
