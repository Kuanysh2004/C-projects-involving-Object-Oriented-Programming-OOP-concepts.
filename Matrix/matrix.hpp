#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix();
  Matrix(T element);
  Matrix(std::vector<std::vector<T>> vector);
  ~Matrix() = default;
  Matrix(Matrix<N, M, T>& other);
  Matrix<N, M, T> operator+(const Matrix<N, M, T>& other);
  Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& other);
  Matrix<N, M, T> operator-(const Matrix<N, M, T>& other);
  Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& other);
  Matrix<N, M, T> operator*(const T& par);
  template <size_t K>
  Matrix<N, K, T> operator*(const Matrix<M, K, T>& other);
  Matrix<M, N, T> Transposed();
  T operator()(size_t iii, size_t jjj) const;
  T& operator()(size_t iii, size_t jjj);
  bool operator==(Matrix<N, M, T>& other);

 private:
  std::vector<std::vector<T>> matrix_;
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() {
  matrix_.resize(N, std::vector<T>(M, T()));
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T element) {
  matrix_.resize(N, std::vector<T>(M, element));
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(std::vector<std::vector<T>> vector) {
  matrix_ = vector;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(Matrix<N, M, T>& other) {
  matrix_ = other.matrix_;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator+(const Matrix<N, M, T>& other) {
  Matrix<N, M, T> otvet = *this;
  otvet += other;
  return otvet;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator-(const Matrix<N, M, T>& other) {
  Matrix<N, M, T> otvet = *this;
  otvet -= other;
  return otvet;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> Matrix<N, M, T>::operator*(const T& par) {
  Matrix<N, M, T> otvet = *this;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      otvet.matrix_[i][j] *= par;
    }
  }
  return otvet;
}

template <size_t N, size_t M, typename T>
template <size_t K>
Matrix<N, K, T> Matrix<N, M, T>::operator*(const Matrix<M, K, T>& other) {
  std::vector<std::vector<T>> mat(N, std::vector<T>(K));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < K; ++j) {
      for (size_t k = 0; k < M; ++k) {
        mat[i][j] += matrix_[i][k] * other(k, j);
      }
    }
  }
  Matrix<N, K, T> otvet(mat);
  return otvet;
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() {
  std::vector<std::vector<T>> mat(M, std::vector<T>(N));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      mat[j][i] = matrix_[i][j];
    }
  }
  Matrix<M, N, T> otvet(mat);
  return otvet;
}

template <size_t N, size_t M, typename T>
T Matrix<N, M, T>::operator()(size_t iii, size_t jjj) const {
  return matrix_[iii][jjj];
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t iii, size_t jjj) {
  return matrix_[iii][jjj];
}

template <size_t N, size_t M, typename T>
bool Matrix<N, M, T>::operator==(Matrix<N, M, T>& other) {
  bool otvet = false;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix_[i][j] == other.matrix_[i][j]) {
        otvet = true;
      }
    }
  }
  return otvet;
}

template <size_t N, typename T>
class Matrix<N, N, T> {
 public:
  Matrix();
  Matrix(T element);
  Matrix(std::vector<std::vector<T>> vector);
  ~Matrix() = default;
  Matrix(Matrix<N, N, T>& other);
  Matrix<N, N, T> operator+(const Matrix<N, N, T>& other);
  Matrix<N, N, T>& operator+=(const Matrix<N, N, T>& other);
  Matrix<N, N, T> operator-(const Matrix<N, N, T>& other);
  Matrix<N, N, T>& operator-=(const Matrix<N, N, T>& other);
  Matrix<N, N, T> operator*(const T& par);
  Matrix<N, N, T> operator*(const Matrix<N, N, T>& other);
  Matrix<N, N, T> Transposed();
  T operator()(size_t iii, size_t jjj) const;
  bool operator==(Matrix<N, N, T>& other);
  T Trace();

 private:
  std::vector<std::vector<T>> matrix_;
};

template <size_t N, typename T>
Matrix<N, N, T>::Matrix() {
  matrix_.resize(N, std::vector<T>(N, T()));
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(T element) {
  matrix_.resize(N, std::vector<T>(N, element));
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(std::vector<std::vector<T>> vector) {
  matrix_ = vector;
}

template <size_t N, typename T>
Matrix<N, N, T>::Matrix(Matrix<N, N, T>& other) {
  matrix_ = other.matrix_;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator+(const Matrix<N, N, T>& other) {
  return (*this += other);
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator+=(const Matrix<N, N, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator-(const Matrix<N, N, T>& other) {
  return (*this -= other);
}

template <size_t N, typename T>
Matrix<N, N, T>& Matrix<N, N, T>::operator-=(const Matrix<N, N, T>& other) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator*(const T& par) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix_[i][j] *= par;
    }
  }
  return *this;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::operator*(const Matrix<N, N, T>& other) {
  std::vector<std::vector<T>> mat(N, std::vector<T>(N));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      for (size_t k = 0; k < N; ++k) {
        mat[i][j] += matrix_[i][k] * other(k, j);
      }
    }
  }
  Matrix<N, N, T> otvet(mat);
  return otvet;
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::Transposed() {
  std::vector<std::vector<T>> mat(N, std::vector<T>(N));
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      mat[j][i] = matrix_[i][j];
    }
  }
  Matrix<N, N, T> otvet(mat);
  return otvet;
}

template <size_t N, typename T>
T Matrix<N, N, T>::operator()(size_t iii, size_t jjj) const {
  return matrix_[iii][jjj];
}

template <size_t N, typename T>
bool Matrix<N, N, T>::operator==(Matrix<N, N, T>& other) {
  bool otvet = false;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      if (matrix_[i][j] == other.matrix_[i][j]) {
        otvet = true;
      }
    }
  }
  return otvet;
}

template <size_t N, typename T>
T Matrix<N, N, T>::Trace() {
  T otvet;
  for (size_t i = 0; i < N; ++i) {
    otvet += matrix_[i][i];
  }
  return otvet;
}
