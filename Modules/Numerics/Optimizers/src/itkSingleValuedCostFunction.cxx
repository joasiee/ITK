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
#include "itkSingleValuedCostFunction.h"

namespace itk
{
void
SingleValuedCostFunction::GetValueAndDerivative(const ParametersType & parameters,
                                                MeasureType &          value,
                                                DerivativeType &       derivative) const
{
  value = this->GetValue(parameters);
  this->GetDerivative(parameters, derivative);
}


Evaluation
SingleValuedCostFunction::GetValue(const ParametersType & parameters, int fosIndex) const
{
  (void)fosIndex;
  (void) parameters;
  itkWarningMacro(<< Self::GetNameOfClass() << ": Missing partial evaluations implementation.");
  Evaluation res;
  return res;
}

typename SingleValuedCostFunction::MeasureType
SingleValuedCostFunction::GetValue(const Evaluation & evaluation) const
{
  (void)evaluation;
  itkWarningMacro(<< Self::GetNameOfClass() << ": Missing partial evaluations implementation.");
  return 0.0;
}

void
SingleValuedCostFunction::SetTransformParameters(const ParametersType & parameters) const
{
  (void)parameters;
}
void
SingleValuedCostFunction::InitPartialEvaluations(int ** sets, int * set_length, int length)
{
  (void)sets;
  (void)set_length;
  (void)length;
  itkWarningMacro(<< Self::GetNameOfClass() << ": Missing partial evaluations implementation.");
}

SingleValuedCostFunction::~SingleValuedCostFunction() = default;
} // namespace itk
