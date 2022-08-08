#include <iostream>
#include "itkEvaluation.h"

int
main(int argc, char const * argv[])
{
  using namespace itk;
  Evaluation eval1;
  Evaluation eval2;

  eval1.Set(50.0);
  eval2.Set(60.0);

  std::cout << (eval1 - eval2).Evaluate() << std::endl;

  return 0;
}