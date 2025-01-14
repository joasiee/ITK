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
#ifndef itkBinaryBallStructuringElement_hxx
#define itkBinaryBallStructuringElement_hxx

#include "itkFlatStructuringElement.h"

namespace itk
{
// Create the structuring element
template <typename TPixel, unsigned int VDimension, typename TAllocator>
void
BinaryBallStructuringElement<TPixel, VDimension, TAllocator>::CreateStructuringElement()
{
  // Carry out all of the computations using the FlatStructuringElement.
  using SEType = FlatStructuringElement<VDimension>;
  SEType flatKernel = SEType::Ball(this->GetRadius());

  // Copy the ellipsoid into the kernel
  std::copy(flatKernel.Begin(), flatKernel.End(), this->Begin());
}
} // namespace itk

#endif
