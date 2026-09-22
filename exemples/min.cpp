#include <iostream>
#include <climits>
#include <cstring>
#include <limits>

// Minimum of two values

int min_int(int x, int y) {
  return x < y ? x : y;
}

float min_float(float x, float y) {
  return x < y ? x : y;
}

template <typename T>
T min(T x, T y) {
  return x < y ? x : y;
}

// Specialization for booleans

template<>
bool min(bool x, bool y) {
  return x && y;
}


// Minimum of an array

int min_int_array(int* array, size_t size) {
  int m = INT_MAX;
  for (size_t i = 0 ; i < size ; i++) {
    if (array[i] < m)
      m = array[i];
  }
  return m;
}

// Comparable trait

template<typename T>
class Comparable
{
public:
  static T max() {
    return std::numeric_limits<T>::max();
  }

  static bool compare(T &x, T &y) {
    return x < y;
  }
};

template <typename T, typename Comparable=Comparable<T>>
T min(T* array, size_t size) {
  T m = Comparable::max();
  for (size_t i = 0 ; i < size ; i++) {
    if (Comparable::compare(array[i],m))
      m = array[i];
  }
  return m;
}

// Specialization of trait Comparable for std::string

template<>
class Comparable<char const*> {
public:
  static char const* max() {
    return "\x7f"; // biggest ascii char
  }

  static bool compare(char const* &x, char const* &y) {
    return strcmp(x, y) < 0;
  }
};

// Array class

template <typename T>
class array {
  size_t allocated_size;
  T *contents;

public:
  explicit array(size_t size) :
    allocated_size(size),
    contents(new T[size])
  {}

  array(array &other) :
    allocated_size(other.allocated_size),
    contents(new T[other.allocated_size])
  {
    for (int i = 0; i < allocated_size; i++) {
      contents[i] = other.contents[i];
    }
  }

  ~array() {
    delete [] contents;
  }

  T get(size_t index) const {
    return contents[index];
  }

  void set(size_t index, T value) {
    contents[index] = value;
  }

  size_t size() {
    return allocated_size;
  }
};


template <typename T, typename C=Comparable<T>>
T min(array<T> array) {
  T m = C::max();
  for (size_t i = 0 ; i < array.size() ; i++) {
    T x = array.get(i);
    if (C::compare(x,m))
      m = x;
  }
  return m;
}

// Test

int main() {
  std::cout
    << "min_float(1000000042, 2000000000) = "
    << min_float(1000000042, 2000000000)
    << std::endl;

  std::cout
    << "min_int(3.14f, 2.72f) = "
    << min_int(3.14f, 2.72f)
    << std::endl;

  std::cout
    << "min(1000000000, 2000000000) = "
    << min(1000000000, 2000000000)
    << std::endl;

  std::cout
    << "min<double>(3.14f, 2.72f) = "
    << min<double>(3.14f, 2.72f)
    << std::endl;

  int a1[] = { 14, 3, 42, 12 };
  std::cout
    << "min_int_array{ 14, 3, 42, 12 } = "
    << min_int_array(a1, 4)
    << std::endl;

  std::cout
    << "min{ 14, 3, 42, 12 } = "
    << min(a1, 4)
    << std::endl;

  array<int> a2(4);
  a2.set(0, 41);
  a2.set(1, 5);
  a2.set(2, 7);
  a2.set(3, 55);
  std::cout
    << "min{ 41, 5, 7, 55 } = "
    << min(a2)
    << std::endl;

  array<char const*> a3(4);
  a3.set(0, "lorem");
  a3.set(1, "ipsum");
  a3.set(2, "dolor");
  a3.set(3, "sit");
  std::cout
    << "min{ \"lorem\", \"ipsum\", \"dolor\", \"sit\" } = "
    << min(a3)
    << std::endl;
}
