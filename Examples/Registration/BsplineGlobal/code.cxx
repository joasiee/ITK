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
#include "itkImageRegistrationMethod.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkTimeProbesCollectorBase.h"
#include "itkSpatialObjectToImageFilter.h"
#include "itkEllipseSpatialObject.h"
#include "itkBoxSpatialObject.h"

#if ITK_VERSION_MAJOR < 4
#  include "itkBSplineDeformableTransform.h"
#else
#  include "itkBSplineTransform.h"
#endif
#include "itkLBFGSOptimizer.h"
#include "itkGradientDescentOptimizer.h"
#include "itkGOMEAOptimizer.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkCastImageFilter.h"
#include "itkSquaredDifferenceImageFilter.h"

#ifdef ENABLE_QUICKVIEW
#  include "QuickView.h"
#endif

constexpr unsigned int ImageDimension = 2;
constexpr unsigned int ImageSize = 40;
constexpr unsigned int ObjectSize = 10;
using PixelType = float;

using ImageType = itk::Image<PixelType, ImageDimension>;

static void
CreateBoxImage(ImageType::Pointer image);
static void
CreateCircleImage(ImageType::Pointer image);

int
main(int itkNotUsed(argc), char * itkNotUsed(argv)[])
{

  const unsigned int     SpaceDimension = ImageDimension;
  constexpr unsigned int SplineOrder = 3;
  using CoordinateRepType = double;

  using TransformType =
    itk::BSplineTransform<CoordinateRepType, SpaceDimension, SplineOrder>;
  // using OptimizerType = itk::LBFGSOptimizer;
  using OptimizerType = itk::GOMEAOptimizer;


  using MetricType = itk::MeanSquaresImageToImageMetric<ImageType, ImageType>;

  using InterpolatorType =
    itk::LinearInterpolateImageFunction<ImageType, double>;

  using RegistrationType = itk::ImageRegistrationMethod<ImageType, ImageType>;

  MetricType::Pointer       metric = MetricType::New();
  OptimizerType::Pointer    optimizer = OptimizerType::New();
  InterpolatorType::Pointer interpolator = InterpolatorType::New();
  RegistrationType::Pointer registration = RegistrationType::New();


  // The old registration framework has problems with multi-threading
  // For now, we set the number of work units to 1
  registration->SetNumberOfWorkUnits(1);

  registration->SetMetric(metric);
  registration->SetOptimizer(optimizer);
  registration->SetInterpolator(interpolator);

  TransformType::Pointer transform = TransformType::New();
  registration->SetTransform(transform);

  // Create the synthetic images
  ImageType::Pointer fixedImage = ImageType::New();
  CreateCircleImage(fixedImage);

  ImageType::Pointer movingImage = ImageType::New();
  CreateBoxImage(movingImage);

  // using WriterType = itk::ImageFileWriter<ImageType>;
  // WriterType::Pointer writer = WriterType::New();
  // writer->SetFileName("fixed.png");
  // writer->SetInput(fixedImage);

  // try
  // {
  //   writer->Update();
  // }
  // catch (itk::ExceptionObject & error)
  // {
  //   std::cerr << "Error: " << error << std::endl;
  //   return EXIT_FAILURE;
  // }
  // return EXIT_SUCCESS;

  // Setup the registration
  registration->SetFixedImage(fixedImage);
  registration->SetMovingImage(movingImage);

  ImageType::RegionType fixedRegion = fixedImage->GetBufferedRegion();
  registration->SetFixedImageRegion(fixedRegion);

  //  Here we define the parameters of the BSplineDeformableTransform grid. We
  //  arbitrarily decide to use a grid with $5 \times 5$ nodes within the
  //  image. The reader should note that the BSpline computation requires a
  //  finite support region ( 1 grid node at the lower borders and 2
  //  grid nodes at upper borders). Therefore in this example, we set
  //  the grid size to be $8 \times 8$ and place the grid origin such that
  //  grid node (1,1) coincides with the first pixel in the fixed image.

  TransformType::PhysicalDimensionsType fixedPhysicalDimensions;
  TransformType::MeshSizeType           meshSize;
  for (unsigned int i = 0; i < ImageDimension; i++)
  {
    fixedPhysicalDimensions[i] =
      fixedImage->GetSpacing()[i] *
      static_cast<double>(
        fixedImage->GetLargestPossibleRegion().GetSize()[i] - 1);
  }
  unsigned int numberOfGridNodesInOneDimension = 7;
  meshSize.Fill(numberOfGridNodesInOneDimension - SplineOrder);
  transform->SetTransformDomainOrigin(fixedImage->GetOrigin());
  transform->SetTransformDomainPhysicalDimensions(fixedPhysicalDimensions);
  transform->SetTransformDomainMeshSize(meshSize);
  transform->SetTransformDomainDirection(fixedImage->GetDirection());

  using ParametersType = TransformType::ParametersType;

  const unsigned int numberOfParameters = transform->GetNumberOfParameters();

  ParametersType parameters(numberOfParameters);

  parameters.Fill(0.0);

  transform->SetParameters(parameters);

  //  We now pass the parameters of the current transform as the initial
  //  parameters to be used when the registration process starts.

  registration->SetInitialTransformParameters(transform->GetParameters());

  std::cout << "Intial Parameters = " << std::endl;
  std::cout << transform->GetParameters() << std::endl;

  //  Next we set the parameters of the LBFGS Optimizer.
  // optimizer->SetGradientConvergenceTolerance(0.1);
  // optimizer->SetLineSearchAccuracy(0.9);
  // optimizer->SetDefaultStepLength(0.75);
  // optimizer->TraceOn();
  // optimizer->SetMaximumNumberOfFunctionEvaluations(1000);

  // GOMEA
  optimizer->SetMaximumNumberOfIterations(3);
  optimizer->SetBasePopulationSize(50);
  // optimizer->SetPartialEvaluations(false);
  // optimizer->SetFosElementSize(-6);
  // optimizer->SetImageDimension(ImageDimension);
  // optimizer->SetWriteOutput(true);

  std::cout << std::endl << "Starting Registration" << std::endl;

  try
  {
    registration->Update();
    optimizer->PrintSelf(std::cout, *itk::Indent::New());
  }
  catch (itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    return EXIT_FAILURE;
  }

  // OptimizerType::ParametersType finalParameters =
  //   registration->GetLastTransformParameters();
  // transform->SetParameters(finalParameters);

  // using ResampleFilterType = itk::ResampleImageFilter<ImageType,
  // ImageType>;

  // ResampleFilterType::Pointer resample = ResampleFilterType::New();

  // resample->SetTransform(transform);
  // resample->SetInput(movingImage);

  // resample->SetSize(fixedImage->GetLargestPossibleRegion().GetSize());
  // resample->SetOutputOrigin(fixedImage->GetOrigin());
  // resample->SetOutputSpacing(fixedImage->GetSpacing());
  // resample->SetOutputDirection(fixedImage->GetDirection());
  // resample->SetDefaultPixelValue(100);

  // using WriterType = itk::ImageFileWriter<ImageType>;
  // WriterType::Pointer writer = WriterType::New();
  // writer->SetFileName("output.png");
  // writer->SetInput(resample->GetOutput());

  // try
  // {
  //   writer->Update();
  // }
  // catch (itk::ExceptionObject & error)
  // {
  //   std::cerr << "Error: " << error << std::endl;
  //   return EXIT_FAILURE;
  // }

  // using OutputPixelType = unsigned char;
  // using OutputImageType = itk::Image<OutputPixelType, ImageDimension>;
  // using CastFilterType = itk::CastImageFilter<ImageType, OutputImageType>;
  // using OutputWriterType = itk::ImageFileWriter<OutputImageType>;

  // OutputWriterType::Pointer writer = OutputWriterType::New();
  // CastFilterType::Pointer   caster = CastFilterType::New();


  // writer->SetFileName("output.vtk");

  // caster->SetInput(resample->GetOutput());
  // writer->SetInput(caster->GetOutput());

  // try
  // {
  //   writer->Update();
  // }
  // catch (itk::ExceptionObject & err)
  // {
  //   std::cerr << "ExceptionObject caught !" << std::endl;
  //   std::cerr << err << std::endl;
  //   return EXIT_FAILURE;
  // }

#ifdef ENABLE_QUICKVIEW
  QuickView viewer;
  viewer.AddImage(fixedImage.GetPointer(), true, "Fixed Image");
  viewer.AddImage(movingImage.GetPointer(), true, "Moving Image");
  viewer.AddImage(resample->GetOutput(), true, "Resampled Moving Image");

  viewer.Visualize();
#endif

  return EXIT_SUCCESS;
}

void
CreateCircleImage(ImageType::Pointer image)
{
  using EllipseType = itk::EllipseSpatialObject<ImageDimension>;

  using SpatialObjectToImageFilterType =
    itk::SpatialObjectToImageFilter<EllipseType, ImageType>;

  SpatialObjectToImageFilterType::Pointer imageFilter =
    SpatialObjectToImageFilterType::New();

  ImageType::SizeType size;
  size.Fill(ImageSize);

  imageFilter->SetSize(size);

  ImageType::SpacingType spacing;
  spacing.Fill(1);
  imageFilter->SetSpacing(spacing);

  EllipseType::Pointer   ellipse = EllipseType::New();
  EllipseType::ArrayType radiusArray;
  radiusArray.Fill(ObjectSize);
  ellipse->SetRadiusInObjectSpace(radiusArray);

  using TransformType = EllipseType::TransformType;
  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  TransformType::OutputVectorType translation;
  translation.Fill(ImageSize / 2);
  transform->Translate(translation, false);

  ellipse->SetObjectToParentTransform(transform);

  imageFilter->SetInput(ellipse);

  ellipse->SetDefaultInsideValue(255);
  ellipse->SetDefaultOutsideValue(0);
  imageFilter->SetUseObjectValue(true);
  imageFilter->SetOutsideValue(0);

  imageFilter->Update();

  image->Graft(imageFilter->GetOutput());
}

void
CreateBoxImage(ImageType::Pointer image)
{
  using BoxType = itk::BoxSpatialObject<ImageDimension>;

  using SpatialObjectToImageFilterType =
    itk::SpatialObjectToImageFilter<BoxType, ImageType>;

  SpatialObjectToImageFilterType::Pointer imageFilter =
    SpatialObjectToImageFilterType::New();

  ImageType::SizeType size;
  size.Fill(ImageSize);

  imageFilter->SetSize(size);

  ImageType::SpacingType spacing;
  spacing.Fill(1);
  imageFilter->SetSpacing(spacing);

  BoxType::Pointer  box = BoxType::New();
  BoxType::SizeType sizeArray;
  sizeArray.Fill(2 * ObjectSize - 1);
  box->SetSizeInObjectSpace(sizeArray);
  box->Update();

  using TransformType = BoxType::TransformType;
  TransformType::Pointer transform = TransformType::New();
  transform->SetIdentity();

  TransformType::OutputVectorType translation;
  translation.Fill((ImageSize / 2) - ObjectSize);
  transform->Translate(translation, false);

  box->SetObjectToParentTransform(transform);

  imageFilter->SetInput(box);

  box->SetDefaultInsideValue(255);
  box->SetDefaultOutsideValue(0);
  imageFilter->SetUseObjectValue(true);
  imageFilter->SetOutsideValue(0);

  imageFilter->Update();

  image->Graft(imageFilter->GetOutput());
}
