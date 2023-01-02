#pragma once

#include <numeric>
#include "itkArray.h"

namespace itk
{

struct Constraints
{
  double       missedPixelPct;
  unsigned int bsplineFolds;
};


class IntermediateResults
{
public:
  IntermediateResults() = default;
  IntermediateResults(const unsigned int n_operands)
    : m_Operands(n_operands, 0.0)
    , m_NumberOfOperands(n_operands)
  {}

  IntermediateResults &
  operator+=(const IntermediateResults & rhs)
  {
    for (unsigned int i = 0; i < m_NumberOfOperands; ++i)
    {
      m_Operands[i] += rhs.m_Operands[i];
    }

    constraints.missedPixelPct += rhs.constraints.missedPixelPct;
    constraints.bsplineFolds += rhs.constraints.bsplineFolds;

    return *this;
  }

  IntermediateResults &
  operator-=(const IntermediateResults & rhs)
  {
    for (unsigned int i = 0; i < m_NumberOfOperands; ++i)
    {
      m_Operands[i] -= rhs.m_Operands[i];
    }

    constraints.missedPixelPct -= rhs.constraints.missedPixelPct;
    constraints.bsplineFolds -= rhs.constraints.bsplineFolds;

    return *this;
  }

  friend IntermediateResults
  operator+(IntermediateResults lhs, const IntermediateResults & rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend IntermediateResults
  operator-(IntermediateResults lhs, const IntermediateResults & rhs)
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


public:
  Constraints constraints;

private:
  Array<double> m_Operands;
  unsigned int  m_NumberOfOperands;
};

class CostFunctionTest
{
public:
  virtual double
  GetValue(const IntermediateResults & evaluation) = 0;
};

class SimpleCostFunctionTest : public CostFunctionTest
{
public:
  double
  GetValue(const IntermediateResults & evaluation)
  {
    return evaluation[0];
  }
};


} // namespace itk
