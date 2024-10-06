#pragma once
#include <cstdint>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix();

  explicit Matrix(const std::vector<std::vector<T>>& matrix_vec);

  explicit Matrix(T elem);

  Matrix<M, N, T> Transposed() const;

  template <size_t K = N, size_t F = M>
  typename std::enable_if<K == F, T>::type Trace() const;

  Matrix& operator+=(const Matrix& other_matrix);

  Matrix& operator-=(const Matrix& other_matrix);

  Matrix& operator*=(const T& multiplier);

  T& operator()(size_t index_1, size_t index_2);

  const T& operator()(size_t index_1, size_t index_2) const;

  ~Matrix() = default;

 private:
  std::vector<std::vector<T>> elements_;
};

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& matrix, const T& multiplier);

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const T& multiplier, const Matrix<N, M, T>& matrix);

template <size_t N, size_t P, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, P, T>& matrix_1,
                          const Matrix<P, M, T>& matrix_2);

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& matrix_1,
                          const Matrix<N, M, T>& matrix_2);

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& matrix_1,
                          const Matrix<N, M, T>& matrix_2);

template <size_t N, size_t M, typename T>
bool operator==(const Matrix<N, M, T>& matrix_1,
                const Matrix<N, M, T>& matrix_2);