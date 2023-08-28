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
}

class Store {
 public:
  void AddGame(const Game& game) { games.push_back(game); }
  void MakeSale(const Sale &sale);

  void DisplayGame() const;
  void DisplayMenu() const;  // For User Interaction. 

  const vector<Game> &get_game() const { return games; }

  bool SaveDataToFile(const string &game_file) const;
  bool LoadDataFromFile(const string &game_file);

 private:
  vector<Game> games;
}
