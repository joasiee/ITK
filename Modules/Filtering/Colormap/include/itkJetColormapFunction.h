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
#ifndef itkJetColormapFunction_h
#define itkJetColormapFunction_h

#include "itkColormapFunction.h"

namespace itk
{
namespace Function
{
/**
 * \class JetColormapFunction
 * \brief Function object which maps a scalar value into an RGB colormap value.
 *
 * \image html JetColormapFunction.png "Jet colormap."
 *
 * \author Nicholas Tustison, Hui Zhang, Gaetan Lehmann, Paul Yushkevich
 * and James C. Gee
 *
 * This code was contributed in the Insight Journal paper:
 *
 * "Meeting Andy Warhol Somewhere Over the Rainbow: RGB Colormapping and ITK"
 * https://www.insight-journal.org/browse/publication/285
 *
 * \ingroup ITKColormap
 *
 * \sphinx
 * \sphinxexample{Filtering/Colormap/MapScalarsIntoJetColormap,Map Scalars Into Jet Colormap}
 * \endsphinx
 */
template <typename TScalar, typename TRGBPixel>
class ITK_TEMPLATE_EXPORT JetColormapFunction : public ColormapFunction<TScalar, TRGBPixel>
{
public:
  ITK_DISALLOW_COPY_AND_MOVE(JetColormapFunction);

  using Self = JetColormapFunction;
  using Superclass = ColormapFunction<TScalar, TRGBPixel>;
  using Pointer = SmartPointer<Self>;
  using ConstPointer = SmartPointer<const Self>;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  using typename Superclass::RGBPixelType;
  using typename Superclass::ScalarType;
  using typename Superclass::RealType;

  RGBPixelType
  operator()(const TScalar &) const override;

protected:
  JetColormapFunction() = default;
  ~JetColormapFunction() override = default;
};
} // end namespace Function
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#  include "itkJetColormapFunction.hxx"
#endif

#endif
