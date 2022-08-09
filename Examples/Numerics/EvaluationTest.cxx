#include <iostream>
#include "itkEvaluation.h"

int
main(int argc, char const * argv[])
{
  using namespace itk;

  Evaluation a1{1};
  a1[0] = 5.0;
  Evaluation a2{1};
  a2[0] = 7.0;
  Evaluation r1 = a1 + a2;

  CostFunctionTest * costFunction = new SimpleCostFunctionTest;

  std::cout << costFunction->GetValue(r1) << std::endl;

  delete costFunction;

  return 0;
}