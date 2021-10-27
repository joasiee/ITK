/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef ExampleCostFunction_h
#define ExampleCostFunction_h

#include "itkSingleValuedCostFunction.h"

namespace itk
{
class ExampleCostFunction2 : public SingleValuedCostFunction
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(ExampleCostFunction2);
  /** Standard class typedefs. */
  typedef ExampleCostFunction2     Self;
  typedef SingleValuedCostFunction Superclass;
  typedef SmartPointer<Self>       Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(ExampleCostFunction2, SingleValuedCostfunction);

  unsigned int
  GetNumberOfParameters() const override
  {
    return 2;
  } // itk::CostFunction

  MeasureType
  GetValue(const ParametersType & parameters) const override
  {
    return pow(parameters[0] + 5, 2) + pow(parameters[1] - 7, 2) + 5;
  }

  void
  GetDerivative(const ParametersType &,
                DerivativeType & /*derivative*/) const override
  {
    throw itk::ExceptionObject(
      __FILE__,
      __LINE__,
      "No derivative is available for this cost function.");
  }

protected:
  ExampleCostFunction2() = default;
  ~ExampleCostFunction2() override = default;
};

} // end namespace itk

#endif
