#include "big_integer.hpp"

BigInt::BigInt() { digits_.push_back(0); }
BigInt::BigInt(std::string str) {
  if (str.length() == 0) {
    is_negative_ = false;
  } else {
    if (str[0] == '-') {
      str = str.substr(1);
      is_negative_ = true;
    } else {
      is_negative_ = false;
    }
    for (int i = str.length(); i > 0; i -= kBaselength) {
      if (i < kBaselength) {
        digits_.push_back(atoi(str.substr(0, i).c_str()));
      } else {
        digits_.push_back(
            atoi(str.substr(i - kBaselength, kBaselength).c_str()));
      }
    }
    Removezeroes();
  }
}
void BigInt::Removezeroes() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
  if (digits_.size() == 1 && digits_[0] == 0) {
    is_negative_ = false;
  }
}
BigInt::BigInt(int64_t chislo) {
  int otris = 1;
  if (chislo < 0) {
    is_negative_ = true;
    otris = -1;
  }
  if (chislo == 0) {
    is_negative_ = false;
    digits_.push_back(0);
  }
  while (chislo != 0) {
    digits_.push_back((chislo % kBase) * otris);
    chislo /= kBase;
  }
}
BigInt::BigInt(const BigInt& copy) { *this = copy; }
BigInt& BigInt::operator=(const BigInt& other) {
  is_negative_ = other.is_negative_;
  digits_ = other.digits_;
  return *this;
}
BigInt::~BigInt() {}
bool operator==(const BigInt& left, const BigInt& other) {
  if (left.is_negative_ != other.is_negative_) {
    return false;
  }
  if (left.digits_.size() != other.digits_.size()) {
    return false;
  }
  for (int i = 0; i < int(other.digits_.size()); ++i) {
    if (left.digits_[i] != other.digits_[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(const BigInt& left, const BigInt& other) {
  return !(left == other);
}
BigInt BigInt::operator-() const {
  BigInt tmp = *this;
  if (*this == 0) {
    return 0;
  }
  tmp.is_negative_ = !tmp.is_negative_;
  return tmp;
}
bool operator<(const BigInt& left, const BigInt& other) {
  if (left.is_negative_ && !other.is_negative_) {
    return true;
  }
  if (!left.is_negative_ && other.is_negative_) {
    return false;
  }
  if (left.is_negative_ && other.is_negative_) {
    return ((-other) < (-left));
  }
  if (left.digits_.size() != other.digits_.size()) {
    return (left.digits_.size() < other.digits_.size());
  }
  bool otvet = false;
  for (int i = left.digits_.size() - 1; i >= 0; --i) {
    if (left.digits_[i] != other.digits_[i]) {
      otvet = (left.digits_[i] < other.digits_[i]);
      return otvet;
    }
  }
  return otvet;
}
bool operator>=(const BigInt& left, const BigInt& other) {
  return !(left < other);
}
bool operator>(const BigInt& left, const BigInt& other) {
  return ((left != other) && (left >= other));
}
bool operator<=(const BigInt& left, const BigInt& other) {
  return (!(left > other));
}
BigInt operator-(const BigInt& left, const BigInt& other) {
  if (other.is_negative_) {
    return (left + (-other));
  }
  if (left.is_negative_) {
    return -(-left + other);
  }
  if (left < other) {
    return (-(other - left));
  }
  int carry = 0;
  BigInt copy = left;
  for (size_t i = 0; i < other.digits_.size() || carry != 0; ++i) {
    copy.digits_[i] -=
        carry + (i < other.digits_.size() ? other.digits_[i] : 0);
    carry = int(copy.digits_[i] < 0);
    if (carry != 0) {
      copy.digits_[i] += BigInt::kBase;
    }
  }
  copy.Removezeroes();

  return copy;
}
BigInt operator+(const BigInt& left, const BigInt& other) {
  if (left.is_negative_ && other.is_negative_) {
    return (-(-left + (-other)));
  }
  if (left.is_negative_ && !other.is_negative_) {
    return (other - (-left));
  }
  if (!left.is_negative_ && other.is_negative_) {
    return (left - (-other));
  }
  int carry = 0;
  BigInt copy = left;
  for (size_t i = 0;
       i < std::max(copy.digits_.size(), other.digits_.size()) || carry != 0;
       ++i) {
    if (i == copy.digits_.size()) {
      copy.digits_.push_back(0);
    }
    copy.digits_[i] +=
        carry + (i < other.digits_.size() ? other.digits_[i] : 0);
    carry = int(copy.digits_[i] >= BigInt::kBase);
    if (carry != 0) {
      copy.digits_[i] -= BigInt::kBase;
    }
  }
  return copy;
}
BigInt& BigInt::operator+=(const BigInt& other) {
  return (*this = (*this + other));
}
BigInt& BigInt::operator-=(const BigInt& other) {
  return (*this = (*this - other));
}
BigInt& BigInt::operator++() { return (*this += 1); }
BigInt BigInt::operator++(int) {
  *this += 1;
  return (*this - 1);
}
BigInt& BigInt::operator--() { return (*this -= 1); }
BigInt BigInt::operator--(int) {
  *this -= 1;
  return (*this + 1);
}
BigInt operator*(const BigInt& left, const BigInt& other) {
  BigInt otvet;
  otvet.digits_.resize(left.digits_.size() + other.digits_.size(), 0);
  for (size_t i = 0; i < left.digits_.size(); ++i) {
    int64_t carry = 0;
    for (size_t j = 0; j < other.digits_.size() || carry != 0; ++j) {
      long long cur = otvet.digits_[i + j] +
                      (left.digits_[i]) * 1LL *
                          (j < other.digits_.size() ? other.digits_[j] : 0) +
                      carry;
      otvet.digits_[i + j] = int(cur % BigInt::kBase);
      carry = int(cur / BigInt::kBase);
    }
  }
  otvet.is_negative_ = left.is_negative_ != other.is_negative_;
  otvet.Removezeroes();
  return otvet;
}
BigInt& BigInt::operator*=(const BigInt& other) {
  return (*this = (*this * other));
}
BigInt BigInt::Abs() const {
  BigInt copy = *this;
  copy.is_negative_ = false;
  return copy;
}
int Search(int first, int last, const BigInt& ddd, const BigInt& delim) {
  int ans = 0;
  while (first <= last) {
    int mid = (last + first) / 2;
    if (ddd * mid <= delim) {
      first = mid + 1;
      ans = mid;
    } else {
      last = mid - 1;
    }
  }
  return ans;
}
BigInt BigInt::operator/(const BigInt& other) const {
  BigInt otv = 0;
  BigInt tmp = 0;
  while (tmp * other.Abs() < Abs()) {
    tmp.Shift(true);
  }
  tmp.Shift(false);
  while (tmp != 0) {
    otv += tmp * Search(0, kBase, tmp * other.Abs(), Abs() - other.Abs() * otv);
    tmp.Shift(false);
  }
  if (other.is_negative_ == is_negative_) {
    otv.is_negative_ = is_negative_;
  } else {
    otv.is_negative_ = true;
  }
  otv.Removezeroes();
  return otv;
}
BigInt& BigInt::operator/=(const BigInt& other) {
  return (*this = (*this / other));
}
BigInt BigInt::operator%(const BigInt& other) const {
  BigInt otvet = *this - (*this / other) * (other);
  return otvet;
}
BigInt& BigInt::operator%=(const BigInt& other) {
  return (*this = (*this % other));
}
std::ostream& operator<<(std::ostream& out, const BigInt& other) {
  if (other.digits_.empty()) {
    out << 0;
  } else {
    if (other.is_negative_) {
      out << "-";
    }
    out << other.digits_.back();
    for (int i = other.digits_.size() - 2; i >= 0; --i) {
      int temp_zeros = 1;
      int temp = other.digits_[i];
      const int kTen = 10;
      while (temp > 0) {
        temp /= kTen;
        ++temp_zeros;
      }
      for (int j = 0; j < other.kBaselength - temp_zeros; ++j) {
        out << '0';
      }
      out << other.digits_[i];
    }
  }
  return out;
}
std::istream& operator>>(std::istream& input, BigInt& other) {
  std::string str;
  input >> str;
  BigInt tmp(str);
  other = tmp;
  return input;
}
void BigInt::Shift(bool add) {
  if (add) {
    digits_.push_back(1);
    digits_[digits_.size() - 2] = 0;

  } else {
    digits_.pop_back();
    if (!digits_.empty()) {
      digits_[digits_.size() - 1] = 1;
    } else {
      digits_.push_back(0);
    }
  }
}
