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
#ifndef itkSingleValuedCostFunction_h
#define itkSingleValuedCostFunction_h

#include "itkCostFunction.h"
#include "itkNumericTraits.h"
#include "itkIntermediateResults.h"
#include "ITKOptimizersExport.h"

namespace itk
{
/** \class SingleValuedCostFunction
 * \brief This class is a base for the CostFunctions returning a
 * single value
 *
 * \ingroup Numerics Optimizers
 * \ingroup ITKOptimizers
 */
class ITKOptimizers_EXPORT SingleValuedCostFunction : public CostFunction
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(SingleValuedCostFunction);

  /** Standard class type aliases. */
  using Self = SingleValuedCostFunction;
  using Superclass = CostFunction;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Run-time type information (and related methods). */
  itkTypeMacro(SingleValuedCostFunction, CostFunction);

  /**  MeasureType type alias.
   *  It defines a type used to return the cost function value. */
  using MeasureType = double;

  /**  ParametersType type alias.
   *  It defines a position in the optimization search space. */
  using ParametersType = Superclass::ParametersType;
  using ParametersValueType = Superclass::ParametersValueType;

  /** DerivativeType type alias.
   *  It defines a type used to return the cost function derivative.  */
  using DerivativeType = Array<ParametersValueType>;

  /** This method returns the value of the cost function corresponding
   * to the specified parameters.    */
  virtual MeasureType
  GetValue(const ParametersType & parameters) const = 0;

  /** This method returns the value of the cost function when it is evaluated partially. */
  virtual MeasureType
  GetValue(const ParametersType & parameters, int fosIndex, int individualIndex) const;

  virtual MeasureType
  GetValue(const IntermediateResults & evaluation) const
  {
    (void)evaluation;
    return NumericTraits<MeasureType>::Zero;
  }

  /** Calculates and stores the partial evaluation using current/old parameters. This evaluation is then used in
   * GetValue(params, index). This way the calls in optimizers's can still be done in a unified fashion across both the
   * single and combination metrics.
   */
  virtual void
  PreloadPartialEvaluation(const ParametersType & parameters, int fosIndex) const
  {
    (void)parameters;
    (void)fosIndex;
  }

  virtual void
  SavePartialEvaluation(int individualIndex)
  {
    (void)individualIndex;
  }

  virtual void
  CopyPartialEvaluation(int toCopy, int toChange)
  {
    (void)toCopy;
    (void)toChange;
  }

  virtual void
  SetTransformParameters(const ParametersType & parameters) const;

  /** Initializes partial evaluations data structures. */
  virtual void
  InitPartialEvaluations(int ** sets, int * set_length, int length, int pop_size);

  /** This method returns the derivative of the cost function corresponding
   * to the specified parameters.   */
  virtual void
  GetDerivative(const ParametersType & parameters, DerivativeType & derivative) const = 0;

  /** This method returns the value and derivative of the cost function corresponding
   * to the specified parameters    */
  virtual void
  GetValueAndDerivative(const ParametersType & parameters, MeasureType & value, DerivativeType & derivative) const;

protected:
  SingleValuedCostFunction() = default;
  ~SingleValuedCostFunction() override;
};
} // end namespace itk

#endif
