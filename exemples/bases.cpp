#include <iostream>
#include <string>

std::string int_to_string10(unsigned int n) {
  char buffer[10];
  int i = 10;
  buffer[--i] = '\0';
  do {
    buffer[--i] = n % 10 + '0';
    n = n / 10;
  }
  while (n > 0);
  return std::string(buffer + i);
}

std::string int_to_string2(unsigned int n) {
  char buffer[33];
  int i = 33;
  buffer[--i] = '\0';
  do {
    buffer[--i] = n % 2 + '0';
    n = n / 2;
  }
  while (n > 0);
  return std::string(buffer + i);
}

std::string int_to_string(unsigned int n, int base = 10) {
  char buffer[33];
  int i = 33;
  buffer[--i] = '\0';
  do {
    buffer[--i] = n % base + '0';
    n = n / base;
  }
  while (n > 0);
  return std::string(buffer + i);
}

int main() {
  int n;
  std::cout << "in base 10: " << int_to_string(42,10) << std::endl;
  std::cout << "in base 2: " << int_to_string(42,2) << std::endl;
  return 0;
}

