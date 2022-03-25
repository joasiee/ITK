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
#ifndef itkStatisticsRelabelImageFilter_hxx
#define itkStatisticsRelabelImageFilter_hxx

#include "itkProgressAccumulator.h"

namespace itk
{
template <typename TInputImage, typename TFeatureImage>
StatisticsRelabelImageFilter<TInputImage, TFeatureImage>::StatisticsRelabelImageFilter()
{
  m_BackgroundValue = NumericTraits<OutputImagePixelType>::NonpositiveMin();
  m_ReverseOrdering = false;
  m_Attribute = LabelObjectType::MEAN;
  this->SetNumberOfRequiredInputs(2);
}

template <typename TInputImage, typename TFeatureImage>
void
StatisticsRelabelImageFilter<TInputImage, TFeatureImage>::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();

  // We need all the input.
  InputImagePointer input = const_cast<InputImageType *>(this->GetInput());
  if (input)
  {
    input->SetRequestedRegion(input->GetLargestPossibleRegion());
  }
}

template <typename TInputImage, typename TFeatureImage>
void
StatisticsRelabelImageFilter<TInputImage, TFeatureImage>::EnlargeOutputRequestedRegion(DataObject *)
{
  this->GetOutput()->SetRequestedRegion(this->GetOutput()->GetLargestPossibleRegion());
}

template <typename TInputImage, typename TFeatureImage>
void
StatisticsRelabelImageFilter<TInputImage, TFeatureImage>::GenerateData()
{
  // Create a process accumulator for tracking the progress of this minipipeline
  auto progress = ProgressAccumulator::New();

  progress->SetMiniPipelineFilter(this);

  // Allocate the output
  this->AllocateOutputs();

  auto labelizer = LabelizerType::New();
  labelizer->SetInput(this->GetInput());
  labelizer->SetBackgroundValue(m_BackgroundValue);
  labelizer->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(labelizer, .3f);

  auto valuator = LabelObjectValuatorType::New();
  valuator->SetInput(labelizer->GetOutput());
  valuator->SetFeatureImage(this->GetFeatureImage());
  valuator->SetLabelImage(this->GetInput());
  valuator->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  valuator->SetComputeHistogram(false);
  if (m_Attribute != LabelObjectType::PERIMETER && m_Attribute != LabelObjectType::ROUNDNESS)
  {
    valuator->SetComputePerimeter(false);
  }
  if (m_Attribute == LabelObjectType::FERET_DIAMETER)
  {
    valuator->SetComputeFeretDiameter(true);
  }
  progress->RegisterInternalFilter(valuator, .3f);

  auto opening = RelabelType::New();
  opening->SetInput(valuator->GetOutput());
  opening->SetReverseOrdering(m_ReverseOrdering);
  opening->SetAttribute(m_Attribute);
  opening->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(opening, .2f);

  auto binarizer = BinarizerType::New();
  binarizer->SetInput(opening->GetOutput());
  binarizer->SetNumberOfWorkUnits(this->GetNumberOfWorkUnits());
  progress->RegisterInternalFilter(binarizer, .2f);

  binarizer->GraftOutput(this->GetOutput());
  binarizer->Update();
  this->GraftOutput(binarizer->GetOutput());
}

template <typename TInputImage, typename TFeatureImage>
void
StatisticsRelabelImageFilter<TInputImage, TFeatureImage>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "ReverseOrdering: " << m_ReverseOrdering << std::endl;
  os << indent
     << "BackgroundValue: " << static_cast<typename NumericTraits<OutputImagePixelType>::PrintType>(m_BackgroundValue)
     << std::endl;
  os << indent << "Attribute: " << LabelObjectType::GetNameFromAttribute(m_Attribute) << " (" << m_Attribute << ")"
     << std::endl;
}
} // end namespace itk
#endif
