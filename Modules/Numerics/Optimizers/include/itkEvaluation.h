#pragma once

#include <array>
#include <vector>
#include <numeric>

namespace itk
{
class Evaluation
{
public:
  Evaluation() = default;
  Evaluation(const unsigned int n_operands)
    : m_Operands(n_operands, 0.0)
    , m_NumberOfOperands(n_operands)
  {}

  Evaluation &
  operator+=(const Evaluation & rhs)
  {
    for (unsigned int i = 0; i < m_NumberOfOperands; ++i)
    {
      m_Operands[i] += rhs.m_Operands[i];
    }
    return *this;
  }

  Evaluation &
  operator-=(const Evaluation & rhs)
  {
    for (unsigned int i = 0; i < m_NumberOfOperands; ++i)
    {
      m_Operands[i] -= rhs.m_Operands[i];
    }
    return *this;
  }

  friend Evaluation
  operator+(Evaluation lhs, const Evaluation & rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend Evaluation
  operator-(Evaluation lhs, const Evaluation & rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  double &
  operator[](std::size_t idx)
  {
    return m_Operands[idx];
  }

  double
  operator[](std::size_t idx) const
  {
    return m_Operands[idx];
  }

private:
  std::vector<double> m_Operands;
  unsigned int        m_NumberOfOperands;
};

class CostFunctionTest
{
public:
  virtual double
  GetValue(const Evaluation & evaluation) = 0;
};

class SimpleCostFunctionTest : public CostFunctionTest
{
public:
  double
  GetValue(const Evaluation & evaluation)
  {
    return evaluation[0];
  }
};


} // namespace itk