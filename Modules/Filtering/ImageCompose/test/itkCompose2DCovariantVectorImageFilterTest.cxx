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

#include <iostream>
#include "itkComposeImageFilter.h"
#include "itkMath.h"

int
itkCompose2DCovariantVectorImageFilterTest(int, char *[])
{
  using PixelType = unsigned char;
  using InputImageType = itk::Image<PixelType, 3>;

  using OutputPixelType = itk::CovariantVector<float, 2>;
  using OutputImageType = itk::Image<OutputPixelType, 3>;

  using FilterType = itk::ComposeImageFilter<InputImageType, OutputImageType>;

  using RegionType = InputImageType::RegionType;
  using SizeType = InputImageType::SizeType;
  using IndexType = InputImageType::IndexType;

  auto filter = FilterType::New();

  auto zeroImage = InputImageType::New();
  auto oneImage = InputImageType::New();

  SizeType size;
  size[0] = 2;
  size[1] = 2;
  size[2] = 2;

  IndexType start;
  start.Fill(0);

  RegionType region;
  region.SetIndex(start);
  region.SetSize(size);

  zeroImage->SetRegions(region);
  oneImage->SetRegions(region);

  zeroImage->Allocate();
  oneImage->Allocate();

  zeroImage->FillBuffer(29);
  oneImage->FillBuffer(51);

  filter->SetInput1(zeroImage);
  filter->SetInput2(oneImage);

  try
  {
    filter->Update();
  }

  catch (const itk::ExceptionObject & excp)
  {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excp << std::endl;
    return EXIT_FAILURE;
  }

  using OutputImageType = FilterType::OutputImageType;

  OutputImageType::Pointer twoVectorImage = filter->GetOutput();

  using OutputIterator = itk::ImageRegionIterator<OutputImageType>;
  using InputIterator = itk::ImageRegionIterator<InputImageType>;

  InputIterator i0(zeroImage, region);
  InputIterator i1(oneImage, region);

  OutputIterator ot(twoVectorImage, region);

  i0.GoToBegin();
  i1.GoToBegin();

  ot.GoToBegin();

  using OutputPixelType = OutputImageType::PixelType;

  while (!ot.IsAtEnd())
  {
    OutputPixelType outp = ot.Get();
    if (itk::Math::NotExactlyEquals(i0.Get(), outp[0]))
    {
      std::cerr << "Error in zeroth component" << std::endl;
      return EXIT_FAILURE;
    }
    if (itk::Math::NotExactlyEquals(i1.Get(), outp[1]))
    {
      std::cerr << "Error in first component" << std::endl;
      return EXIT_FAILURE;
    }
    ++ot;
    ++i0;
    ++i1;
  }

  std::cout << "Test Passed !" << std::endl;

  return EXIT_SUCCESS;
}
