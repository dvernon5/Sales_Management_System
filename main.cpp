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
  Game(const string &title = "", int quantity = 0, double game_price = 0) : game_title(title), game_quantity(quantity), game_price(price) {}
  void set_game(int new_quantity) { game_quantity = new_quantity; }
  string get_title() const { return game_title; }
  int get_quantity() const { return game_quantity; }
  double get_price() const { return game_price; }

 private: 
  string game_title;
  int game_quantity;
  double game_price;
};

class Sale {
 public:
  Sale(const Game &game, int quantity) : game(game), quantity(quantity) {}
  const Game &get_game() const { return game; }
  int get_quantity() const { return quantity; }

 private:
  Game game;
  int quantity;
};

class Store {
 public:
  void set_customer_funds(double funds = 0.0) : customer_funds(funds) {}
  void AddGame(const Game& game) { games.push_back(game); }
  void MakeSale(const Sale &sale);

  void DisplayMenu() const;  // For User Interaction. 
  void DisplayGame() const;
  
  const vector<Game> &get_game() const { return games; }

  bool SaveDataToFile(const string &games_file) const;
  bool LoadDataFromFile(const string &games_file);

 private:
  vector<Game> games;
  double customer_funds;
};

void Store::MakeSale(const Sale &sale) {
  Game game = const_cast<Game&>(sale.get_game());

  if (game.get_quantity() >= sale.get_quantity()) {
    const double california_tax = 0.1025;
    double subtotal = game.get_price() * sale.get_quantity();
    double taxes = subtotal * california_tax;
    double total = subtotal + taxes;
    if (customer_funds >= total) {
      game.set_quantity(game.get_quantity() - sale.get_quantity());
      customer_funds -= total;
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

void DisplayGame() const {
  cout << "Available games:" << endl;
  for (const auto &game : games) {
    cout << game.get_title() << " | Quantity: " << game.get_quantity() << " | Price: " << game.get_price() << endl;
  }
}

bool SaveDataToFile(const string &games_file) const {
  ofstream game_outfile(games_file);
  if (!game_outfile.is_open()) {
    cerr << "Error: Unable to open games file for writing." << endl;
    return false;
  }
 
  for (const auto &game : games) {
    game_outfile << game.get_title() << "," << game.get_quantity() << "," << game.get_price() << endl;
  }
  game_outfile.close();
 
  return true;
}

bool LoadDataFromFile(const string &games_file) {
  ifstream game_infile(games_file)
  if (!game_infile.is_open()) {
    cerr << "Error: Unable to open game file for reading." << endl
    return false;
  }
  string game_title;
  int quantity;
  double price;

  while (game_infile >> game_title >> quantity >> price) {
    Game game(game_title, quantity, price);
    games.push_back(game);
  }
  game_infile.close();

  return true;
}

int main(int argv, char *argc[]) {
  Store store;
  if (!store.LoadDataFromFile("games.txt")) {
    cerr << "Error: Unable to load from files. Starting with empty records." << endl;
  } else {
    cout << "Data loaded from files." << endl;
  }

  // Set the initial customer funds
  double initial_funds;
  cout << "Enter Customer Funds: $";
  cin >> initial_funds;
  cin.ignore();
  store.set_customer_funds(initial_funds);
 
  int selection;
  while (true) {
    store.DisplayMenu();
    cin >> selection;
    cin.ignore();

    switch (selection) {
      case 1: {
        string game_title;
        cout << "Enter Game Title: ";
        getline(cin, game_title);
       
        int quantity;
        cout << "Enter Game Quantity: ";
        cin >> quantity;
        cin.ignore();
       
        double price;
        cout << "Enter Game Price: ";
        cin >> price;
        cin.ignore();

        store.AddGame(Game(game_title, quantity, price));
        break;
      }
     case 2: {
       store.DisplayGame();
       break;
     }
     case 3: {
       string game_title;
       cout << "Enter Game Title: ";
       getline(cin, game_title);

       cout << "Enter Quantity to Purchase: ";
       int quantity;

       bool game_found = false;
       Game found_game("", 0, 0.0);
       for (const auto &game : store.getGames()) {
         if (game.getTitle() == game_title) {
           game_found = true;
           found_game = game;
           break;
         }
       }
       if (!game_found) {
         cout << "Game with title " << game_title << " not found." << endl;
         break;
       }
       store.MakeSale(Sale(found_game, quantity));
       break;
     }
     case 4: {
       if (store.saveDataToFile("games.txt")) {
         cout << "Data saved to files." << endl;
       } else {
         cerr << "Error occurred while saving data to files." << endl;
       }
       break;
     }
     case 5: {
       cout << "Exiting the Sales Management System. Goodbye!" << endl;
       return 0;
     }
     default: {
       cout << "Invalid choice. Please try again." << endl;
       break;
     }
    }
  }
 return 0;
}
