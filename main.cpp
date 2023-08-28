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
