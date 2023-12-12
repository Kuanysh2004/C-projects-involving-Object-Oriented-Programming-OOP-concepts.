#pragma once
#include <iostream>
#include <vector>

class BigInt {
 public:
  BigInt();
  BigInt(std::string str);
  BigInt(int64_t chislo);
  BigInt(const BigInt& copy);
  BigInt& operator=(const BigInt& other);
  ~BigInt();
  BigInt operator-() const;
  friend bool operator==(const BigInt& left, const BigInt& other);
  friend bool operator!=(const BigInt& left, const BigInt& other);
  friend bool operator<(const BigInt& left, const BigInt& other);
  friend bool operator>=(const BigInt& left, const BigInt& other);
  friend bool operator>(const BigInt& left, const BigInt& other);
  friend bool operator<=(const BigInt& left, const BigInt& other);
  friend BigInt operator+(const BigInt& left, const BigInt& other);
  BigInt& operator+=(const BigInt& other);
  friend BigInt operator-(const BigInt& left, const BigInt& other);
  BigInt& operator-=(const BigInt& other);
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);
  friend BigInt operator*(const BigInt& left, const BigInt& other);
  BigInt& operator*=(const BigInt& other);
  BigInt operator/(const BigInt& other) const;
  BigInt& operator/=(const BigInt& other);
  BigInt operator%(const BigInt& other) const;
  BigInt& operator%=(const BigInt& other);
  friend std::ostream& operator<<(std::ostream& out, const BigInt& other);
  BigInt Abs() const;

 private:
  std::vector<int> digits_;
  bool is_negative_ = false;
  static const int kBase = 1e9;
  const int kBaselength = 9;
  void Removezeroes();
  void Shift(bool add);
};
std::istream& operator>>(std::istream& input, BigInt& other);
