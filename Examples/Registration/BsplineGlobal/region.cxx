#include "itkImageRegion.h"
#include "itkIndex.h"
#include "itkSize.h"

int
main(int, char *[])
{
  constexpr unsigned int Dimension = 2;

  using RegionType = itk::ImageRegion<Dimension>;
  using SizeType = RegionType::SizeType;
  using IndexType = RegionType::IndexType;

  SizeType size;
  size.Fill(3);

  IndexType start;
  start.Fill(0);

  RegionType region(start, size);

  IndexType testPixel1;
  testPixel1[0] = 1;
  testPixel1[1] = 1;

  IndexType testPixel2;
  testPixel2[0] = 2;
  testPixel2[1] = 2;

  std::cout << testPixel1 << " ";

  if (region.IsInside(testPixel1))
  {
    std::cout << "1 Inside";
  }
  else
  {
    std::cout << "1 Outside";
    return EXIT_FAILURE;
  }
  std::cout << std::endl;

  std::cout << testPixel2 << " ";
  if (region.IsInside(testPixel2))
  {
    std::cout << "2 Inside";
    return EXIT_FAILURE;
  }
  else
  {
    std::cout << "2 Outside";
  }
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
