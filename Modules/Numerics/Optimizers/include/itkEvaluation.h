#pragma once

#include <array>

namespace itk
{
class Evaluation
{
public:
  virtual double
  Evaluate();

  double
  Peek()
  {
    return m_Value;
  }

  void
  Set(double value)
  {
    m_Value = value;
  }

protected:
  double m_Value{};
};

template <unsigned int NumberOfOperands>
class PartialEvaluation : public Evaluation
{
public:
  PartialEvaluation() = default;
  PartialEvaluation(std::array<double, NumberOfOperands> && operands)
    : m_Operands{ operands }
  {}

  double
  Evaluate() override
  {
    m_Value = 0.0;
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      m_Value += m_Operands[i];
    }
    return Peek();
  }

  PartialEvaluation &
  operator+=(const PartialEvaluation & rhs)
  {
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      m_Operands[i] += rhs.m_Operands[i];
    }
    return *this;
  }

  PartialEvaluation &
  operator-=(const PartialEvaluation & rhs)
  {
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      m_Operands[i] -= rhs.m_Operands[i];
    }
    return *this;
  }

  friend PartialEvaluation
  operator+(PartialEvaluation lhs, const PartialEvaluation & rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend PartialEvaluation
  operator-(PartialEvaluation lhs, const PartialEvaluation & rhs)
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
  std::array<double, NumberOfOperands> m_Operands{};
};
} // namespace itk
