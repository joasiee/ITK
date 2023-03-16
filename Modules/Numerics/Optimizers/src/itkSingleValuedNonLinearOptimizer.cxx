/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkSingleValuedNonLinearOptimizer.h"

namespace itk
{
SingleValuedNonLinearOptimizer::SingleValuedNonLinearOptimizer()
{
  m_CostFunction = nullptr;
}

/**
 * Connect a Cost Function
 */
void
SingleValuedNonLinearOptimizer::SetCostFunction(CostFunctionType * costFunction)
{
  if (m_CostFunction == costFunction)
  {
    return;
  }

  itkDebugMacro("setting CostFunction  to " << costFunction);

  m_CostFunction = costFunction;

  if (!m_ScalesInitialized)
  {
    const unsigned int numberOfParameters = m_CostFunction->GetNumberOfParameters();

    ScalesType scales(numberOfParameters);
    scales.Fill(1.0f);
    SetScales(scales);
    m_ScalesInitialized = true;
  }

  this->Modified();
}

/**
 * Get the cost function value at the given parameters
 */
SingleValuedNonLinearOptimizer::MeasureType
SingleValuedNonLinearOptimizer::GetValue(const ParametersType & parameters) const
{
  itkDebugMacro("Computing CostFunction value at " << parameters);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling GetValue");
    throw ex;
  }

  return this->GetCostFunction()->GetValue(parameters);
}

/**
 * Get the constrained cost function value at the given parameters
 */
SingleValuedNonLinearOptimizer::MeasureType
SingleValuedNonLinearOptimizer::GetValue(const ParametersType & parameters, MeasureType & constraintValue) const
{
  itkDebugMacro("Computing CostFunction value at " << parameters);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling GetValue");
    throw ex;
  }

  return this->GetCostFunction()->GetValue(parameters, constraintValue);
}

/**
 * Get the cost function value at the given parameters using a partial evaluation
 */
SingleValuedNonLinearOptimizer::MeasureType
SingleValuedNonLinearOptimizer::GetValue(const ParametersType & parameters, int fosIndex, int individualIndex, MeasureType & constraintValue) const
{
  itkDebugMacro("Computing CostFunction value at " << parameters);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling GetValue");
    throw ex;
  }

  return this->GetCostFunction()->GetValue(parameters, fosIndex, individualIndex, constraintValue);
}

void
SingleValuedNonLinearOptimizer::PreloadPartialEvaluation(const ParametersType & parameters, int fosIndex)
{
  itkDebugMacro("Pre-computing partial cost function evaluation at " << parameters);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling PreloadPartialEvaluation");
    throw ex;
  }

  this->GetCostFunction()->PreloadPartialEvaluation(parameters, fosIndex);
}

void
SingleValuedNonLinearOptimizer::SavePartialEvaluation(int individualIndex)
{
  itkDebugMacro("Saving partial cost function evaluation at index " << individualIndex);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling SavePartialEvaluation");
    throw ex;
  }

  this->GetCostFunction()->SavePartialEvaluation(individualIndex);
}

void
SingleValuedNonLinearOptimizer::CopyPartialEvaluation(int toCopy, int toChange)
{
  itkDebugMacro("Copying partial cost function evaluation at index " << toCopy << " to index at " << toChange);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling CopyPartialEvaluation");
    throw ex;
  }

  this->GetCostFunction()->CopyPartialEvaluation(toCopy, toChange);
}

void
SingleValuedNonLinearOptimizer::SetTransformParameters(const ParametersType & parameters)
{
  itkDebugMacro("Setting Transform Parameters to: " << parameters);

  if (!m_CostFunction)
  {
    ExceptionObject ex;
    ex.SetLocation(__FILE__);
    ex.SetDescription("The costfunction must be set prior to calling SetTransformParameters");
    throw ex;
  }

  this->GetCostFunction()->SetTransformParameters(parameters);
}

void
SingleValuedNonLinearOptimizer::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  if (m_CostFunction)
  {
    os << indent << "Cost Function: " << m_CostFunction.GetPointer() << std::endl;
  }
}
} // namespace itk
