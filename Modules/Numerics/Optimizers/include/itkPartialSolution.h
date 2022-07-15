#include <array>

class Solution
{
public:
  virtual double
  Evaluate();

  double
  Peek()
  {
    return this->m_Value;
  }

  void
  Set(double value)
  {
    this->m_Value = value;
  }

private:
    double m_Value{};
};

template <unsigned int NumberOfOperands>
class PartialSolution : Solution
{
public:
  PartialSolution() = default;
  PartialSolution(std::array<double, NumberOfOperands> && operands)
    : m_Operands{ operands }
  {}

  double
  Evaluate() override
  {
    this->m_Value = 0.0;
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      this->m_Value += this->m_Operands[i];
    }
    return this->Peek();
  }

  PartialSolution &
  operator+=(const PartialSolution & rhs)
  {
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      this->m_Operands[i] += rhs.m_Operands[i];
    }
    return *this;
  }

  PartialSolution &
  operator-=(const PartialSolution & rhs)
  {
    for (unsigned int i = 0; i < NumberOfOperands; ++i)
    {
      this->m_Operands[i] -= rhs.m_Operands[i];
    }
    return *this;
  }

  friend PartialSolution
  operator+(PartialSolution lhs, const PartialSolution & rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend PartialSolution
  operator-(PartialSolution lhs, const PartialSolution & rhs)
  {
    lhs -= rhs;
    return lhs;
  }

private:
  std::array<double, NumberOfOperands> m_Operands{};
};