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

#include "itkQuadEdgeMesh.h"
#include "itkRegularSphereMeshSource.h"
#include "itkQuadEdgeMeshScalarDataVTKPolyDataWriter.h"
#include "itkTestingMacros.h"

#include <iostream>

int
itkQuadEdgeMeshScalarDataVTKPolyDataWriterTest1(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << itkNameOfTestExecutableMacro(argv);
    std::cerr << " outputFileName.vtk" << std::endl;
    return EXIT_FAILURE;
  }

  using MeshType = itk::QuadEdgeMesh<float, 3>;

  using SphereMeshSourceType = itk::RegularSphereMeshSource<MeshType>;

  auto mySphereMeshSource = SphereMeshSourceType::New();

  using PointType = SphereMeshSourceType::PointType;
  using VectorType = SphereMeshSourceType::VectorType;

  PointType center;
  center.Fill(0.0);

  VectorType scale;
  scale.Fill(1.0);

  mySphereMeshSource->SetCenter(center);
  mySphereMeshSource->SetResolution(1);
  mySphereMeshSource->SetScale(scale);

  mySphereMeshSource->Modified();

  ITK_TRY_EXPECT_NO_EXCEPTION(mySphereMeshSource->Update());


  std::cout << "mySphereMeshSource: " << mySphereMeshSource;

  MeshType::Pointer myMesh = mySphereMeshSource->GetOutput();

  PointType pt;
  pt.Fill(0.);

  std::cout << "Testing itk::RegularSphereMeshSource " << std::endl;

  myMesh->Print(std::cout);

  for (unsigned int i = 0; i < myMesh->GetNumberOfPoints(); ++i)
  {
    myMesh->GetPoint(i, &pt);
    std::cout << "Point[" << i << "]: " << pt << std::endl;
  }

  using CellsContainerPointer = MeshType::CellsContainerPointer;
  using CellType = MeshType::CellType;

  CellsContainerPointer cells = myMesh->GetCells();

  unsigned faceId = 0;

  for (MeshType::CellsContainerIterator cells_it = cells->Begin(); cells_it != cells->End(); ++cells_it, faceId++)
  {
    CellType * cellPointer = cells_it.Value();
    if (static_cast<int>(cellPointer->GetType()) != 1)
    {
      std::cout << "Face " << faceId << " has " << cellPointer->GetNumberOfPoints() << " points" << std::endl;
    }
  }

  std::cout << "Test End " << std::endl;

  using WriterType = itk::QuadEdgeMeshScalarDataVTKPolyDataWriter<MeshType>;

  auto writer = WriterType::New();

  writer->SetInput(mySphereMeshSource->GetOutput());
  writer->SetFileName(argv[1]);

  ITK_TRY_EXPECT_NO_EXCEPTION(writer->Update());


  return EXIT_SUCCESS;
}
