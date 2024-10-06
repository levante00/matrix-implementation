#include "matrix.hpp"

#include <cassert>
#include <type_traits>

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix() : elements_(N, std::vector<T>(M, T())) {}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const std::vector<std::vector<T>>& matrix_vec)
    : elements_(matrix_vec) {}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T elem) : elements_(N, std::vector<T>(M, elem)) {}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transposed() const {
  Matrix<M, N, T> transposed_matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      transposed_matrix(j, i) = elements_[i][j];
    }
  }

  return transposed_matrix;
}
template <size_t N, size_t M, typename T>
template <size_t K, size_t F>
typename std::enable_if<K == F, T>::type Matrix<N, M, T>::Trace() const {
  T trace = T();

  for (size_t i = 0; i < N; ++i) {
    trace += elements_[i][i];
  }

  return trace;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(
    const Matrix<N, M, T>& other_matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      elements_[i][j] += other_matrix(i, j);
    }
  }

  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(
    const Matrix<N, M, T>& other_matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      elements_[i][j] -= other_matrix(i, j);
    }
  }

  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator*=(const T& multiplier) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      elements_[i][j] *= multiplier;
    }
  }

  return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& matrix, const T& multiplier) {
  Matrix<N, M, T> result_matrix;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      result_matrix(i, j) = matrix(i, j) * multiplier;
    }
  }

  return result_matrix;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const T& multiplier, const Matrix<N, M, T>& matrix) {
  Matrix<N, M, T> result_matrix = matrix;
  result_matrix *= multiplier;

  return result_matrix;
}

template <size_t N, size_t P, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, P, T>& matrix_1,
                          const Matrix<P, M, T>& matrix_2) {
  Matrix<N, M, T> result_matrix;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      for (size_t k = 0; k < P; ++k) {
        result_matrix(i, j) += (matrix_1(i, k) * matrix_2(k, j));
      }
    }
  }
  return result_matrix;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& matrix_1,
                          const Matrix<N, M, T>& matrix_2) {
  Matrix<N, M, T> result_matrix = matrix_1;
  result_matrix += matrix_2;

  return result_matrix;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& matrix_1,
                          const Matrix<N, M, T>& matrix_2) {
  Matrix<N, M, T> result_matrix = matrix_1;
  result_matrix -= matrix_2;

  return result_matrix;
}

template <size_t N, size_t M, typename T>
bool operator==(const Matrix<N, M, T>& matrix_1,
                const Matrix<N, M, T>& matrix_2) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix_1(i, j) - matrix_2(i, j) != 0) {
        return false;
      }
    }
  }

  return true;
}

template <size_t N, size_t M, typename T>
T& Matrix<N, M, T>::operator()(size_t index_1, size_t index_2) {
  assert(index_1 < N && index_2 < M && "Index out of bounds exception");
  return elements_[index_1][index_2];
}

template <size_t N, size_t M, typename T>
const T& Matrix<N, M, T>::operator()(size_t index_1, size_t index_2) const {
  assert(index_1 < N && index_2 < M && "Index out of bounds exception");
  return elements_[index_1][index_2];
}
