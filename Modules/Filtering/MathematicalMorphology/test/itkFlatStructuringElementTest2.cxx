/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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

#include "itkFlatStructuringElement.h"
#include <itkRescaleIntensityImageFilter.h>
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include <itkConstantPadImageFilter.h>
#include "itkImageRegionIterator.h"
using namespace itk;

/**
 * Return bool image from input FlatStructuringElement kernel
 */
template< unsigned int VDimension >
typename itk::Image< bool, VDimension>::Pointer
GetImage(const itk::FlatStructuringElement<VDimension> & flatElement)
{
  typedef typename FlatStructuringElement< VDimension >::ImageType
                   ImageType;
  typedef typename FlatStructuringElement< VDimension >::RadiusType
                   RadiusType;
  typedef typename FlatStructuringElement< VDimension >::ConstIterator
                   ConstIterator;
  typedef bool     PixelType;

  typename ImageType::Pointer image = ImageType::New();
  typename ImageType::RegionType region;
  RadiusType size = flatElement.GetRadius();
  Index< VDimension > centerIdx;

  for( unsigned int i = 0; i < VDimension; ++i )
    {
    centerIdx[i] = size[i];
    size[i] = 2*size[i] + 1;
    }
  region.SetSize( size );
  image->SetRegions( region );
  image->Allocate();

  ImageRegionIterator< ImageType > img_it(image, region);
  ConstIterator kernel_it;
  for ( img_it.GoToBegin(), kernel_it = flatElement.Begin(); !img_it.IsAtEnd(); ++img_it, ++kernel_it )
    {
    if(*kernel_it)
      {
      img_it.Set( NumericTraits< PixelType >::OneValue() );
      }
    else
      {
      img_it.Set( NumericTraits< PixelType >::ZeroValue() );
      }
    }
  return image;
};

/** Test. Compare the result of GetImage() with the original input image. */
int itkFlatStructuringElementTest2(int argc, char * argv[])
{
  if ( argc < 1 )
    {
    std::cerr << "Missing argument" << std::endl;
    std::cerr << "Usage: " << argv[0] << " InputImg OutputImg" << std::endl;
    std::cerr << "Images must be odd in size in all dimensions" << std::endl;
    return EXIT_FAILURE;
    }
  const static unsigned int Dimension = 2;
  /**********************************************************/
  /*******Read test image as unsigned int********/
  /**********************************************************/
  typedef itk::Image< unsigned short, Dimension >  Input2DImageType;
  typedef itk::ImageFileReader< Input2DImageType > Reader2DType;
  Reader2DType::Pointer reader2D = Reader2DType::New();
  reader2D->SetFileName( argv[1] );
  try
    {
    reader2D->UpdateLargestPossibleRegion();
    }
  catch (itk::ExceptionObject& e)
    {
    std::cerr << "Exception detected while reading "
      << argv[1] << " : "  << e;
    return 1000;
    }

  Input2DImageType::Pointer testImg = reader2D->GetOutput();
  typedef itk::FlatStructuringElement< Dimension > FSEType;

  /**********************************************************/
  /*******Cast to Bool Image. Required by constructor *******/
  /**********************************************************/
  typedef itk::Image< bool , Dimension> ImageBoolType;

  typedef itk::RescaleIntensityImageFilter< Input2DImageType, Input2DImageType > RescaleType;
  RescaleType::Pointer rescale = RescaleType::New();
  rescale->SetInput( testImg );
  rescale->SetOutputMinimum( itk::NumericTraits< bool >::ZeroValue()  );
  rescale->SetOutputMaximum( itk::NumericTraits< bool >::OneValue() );

  typedef itk::CastImageFilter<Input2DImageType, ImageBoolType> castFilterType;
  castFilterType::Pointer cast = castFilterType::New();
  cast->SetInput(rescale->GetOutput());
  cast->Update();
  ImageBoolType::Pointer testImgBool = cast->GetOutput();

  FSEType flatStructure = FSEType::FromImage(testImgBool);
  ImageBoolType::Pointer imgFromStructure = GetImage(flatStructure);

  /**********************************************************/
  /**Cast back and write for comparisson with input image ***/
  /**********************************************************/

  typedef itk::CastImageFilter<ImageBoolType, Input2DImageType> castBackFilterType;
  castBackFilterType::Pointer castBack = castBackFilterType::New();
  castBack->SetInput(imgFromStructure);
  castBack->Update();

  typedef itk::RescaleIntensityImageFilter< Input2DImageType, Input2DImageType > RescaleBackType;
  RescaleBackType::Pointer rescaleBack = RescaleBackType::New();
  rescaleBack->SetInput( castBack->GetOutput() );
  rescaleBack->SetOutputMinimum( 0  );
  rescaleBack->SetOutputMaximum( 255 );

  Input2DImageType::Pointer testImgAfter = rescaleBack->GetOutput();

  typedef itk::ImageFileWriter< Input2DImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput(testImgAfter);

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excp )
    {
    std::cerr << "Exception writing test image:" << excp << std::endl;
    return  EXIT_FAILURE;
    }

  /**********************************************************/
  /****Even input image sizes generate exception ************/
  /**********************************************************/
  // Pad test image to even size
  typedef itk::ConstantPadImageFilter<ImageBoolType,ImageBoolType>
    ConstPadFilterType;
  ConstPadFilterType::Pointer padFilter = ConstPadFilterType::New();
  padFilter->SetInput(testImgBool);
  Input2DImageType::SizeType lowerExtendRegion;
  lowerExtendRegion[0] = 1;
  lowerExtendRegion[1] = 1;
  padFilter->SetPadLowerBound(lowerExtendRegion);
  ImageBoolType::PixelType constPixel = true;
  padFilter->SetConstant(constPixel);
  padFilter->Update();

  ImageBoolType::Pointer evenImg =  padFilter->GetOutput();
  bool evenSizeImgGeneratesException = false;
  try
    {
    FSEType flatSFromEven = FSEType::FromImage(evenImg);
    }
  catch( itk::ExceptionObject & )
    {
    evenSizeImgGeneratesException = true;
    }

  if (evenSizeImgGeneratesException)
    {
    return EXIT_SUCCESS;
    }
  else
    {
    std::cout << "Failure:: exception not caught on constructor when image has even size" << std::endl;
    return EXIT_FAILURE;
    }

}