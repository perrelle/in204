#include <iostream>
#include <iomanip>

class Duration {
  int seconds;
  int minutes;
  int hours;

public:
  // Constructeur par défaut
  Duration() :
      seconds(0),
      minutes(0),
      hours(0)
  {
    // Rien d'autre à initialiser
  }

  // Constructeur de conversion
  Duration(int n) :
      seconds(n % 60),
      minutes(n / 60 % 60),
      hours(n / 60 / 60)
  {
    // Rien d'autre à initialiser
  }

  // Constructeur de copie
  Duration(Duration& other) :
      seconds(other.seconds),
      minutes(other.seconds),
      hours(other.seconds)
  {
    // Rien d'autre à initialiser
  }

  void increment() {
    seconds ++;
    if (seconds >= 60) {
      seconds = 0;
      minutes ++;
      if (minutes >= 60) {
        minutes = 0;
        hours ++;
      }
    }
  }

  void print() const {
    if (hours != 0) {
      std::cout
        << hours << ":"
        << std::setw(2) << std::setfill('0')
        << minutes << ":"
        << seconds;
    }
    else {
      std::cout
        << minutes << ":"
        << std::setw(2) << std::setfill('0')
        << seconds;
    }  
  }
};

int main() {
  Duration d0; // Appel du constructeur par défaut
  Duration d1 = d0; // Appel du constructeur par recopie
  Duration d = 60 + 59; // Appel du constructeur de conversion
  // d.minutes = 153; // Interdit ! minutes est une propriété privée
  d.increment();
  d.print();
  std::cout << std::endl;
  return 0;
}
