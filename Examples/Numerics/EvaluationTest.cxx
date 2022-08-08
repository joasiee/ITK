#include <iostream>
#include "itkEvaluation.h"

namespace itk
{
class SimplePartialEvaluation : public PartialEvaluation<2>
{
public:
  double
  Evaluate() override
  {
    return (*this)[0] + (*this)[1];
  }
};
} // namespace itk

int
main(int argc, char const * argv[])
{
  using namespace itk;
  SimpleEvaluation eval1;
  SimpleEvaluation eval2;

  eval1.Set(50.0);
  eval2.Set(60.0);

  std::cout << (eval1 - eval2).Evaluate() << std::endl;

  SimplePartialEvaluation seval1;
  seval1[0] = 10.0;
  seval1[1] = 5.0;

  Evaluation * seval2 = &seval1;

  std::cout << seval1.Evaluate() << std::endl;
  std::cout << seval2->Evaluate() << std::endl;


  return 0;
}