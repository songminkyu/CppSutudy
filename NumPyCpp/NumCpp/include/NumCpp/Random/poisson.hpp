/// @file
/// @author David Pilger <dpilger26@gmail.com>
/// [GitHub Repository](https://github.com/dpilger26/NumCpp)
///
/// License
/// Copyright 2020 David Pilger
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this
/// software and associated documentation files(the "Software"), to deal in the Software
/// without restriction, including without limitation the rights to use, copy, modify,
/// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
/// permit persons to whom the Software is furnished to do so, subject to the following
/// conditions :
///
/// The above copyright notice and this permission notice shall be included in all copies
/// or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
/// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
/// PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
/// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
/// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
/// DEALINGS IN THE SOFTWARE.
///
/// Description
/// "poisson" distribution
///
#pragma once

#include "NumCpp/Core/Internal/Error.hpp"
#include "NumCpp/Core/Internal/StaticAsserts.hpp"
#include "NumCpp/Core/Internal/StlAlgorithms.hpp"
#include "NumCpp/Core/Shape.hpp"
#include "NumCpp/NdArray.hpp"
#include "NumCpp/Random/generator.hpp"

#include "boost/random/poisson_distribution.hpp"

#include <string>

namespace nc
{
    namespace random
    {
        //============================================================================
        // Method Description:
        ///						Single random value sampled from the "poisson" distribution.
        ///
        ///                     NumPy Reference: https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.poisson.html#numpy.random.poisson
        ///
        /// @param				inMean (default 1)
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        dtype poisson(double inMean = 1)
        {
            STATIC_ASSERT_ARITHMETIC(dtype);

            if (inMean <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input mean must be greater than zero.");
            }

            const boost::random::poisson_distribution<dtype, double> dist(inMean);
            return dist(generator_); 
        }

        //============================================================================
        // Method Description:
        ///						Create an array of the given shape and populate it with
        ///						random samples from the "poisson" distribution.
        ///
        ///                     NumPy Reference: https://docs.scipy.org/doc/numpy/reference/generated/numpy.random.poisson.html#numpy.random.poisson
        ///
        /// @param				inShape
        /// @param				inMean (default 1)
        /// @return
        ///				NdArray
        ///
        template<typename dtype>
        NdArray<dtype> poisson(const Shape& inShape, double inMean = 1)
        {
            STATIC_ASSERT_ARITHMETIC(dtype);

            if (inMean <= 0)
            {
                THROW_INVALID_ARGUMENT_ERROR("input mean must be greater than zero.");
            }

            NdArray<dtype> returnArray(inShape);

            const boost::random::poisson_distribution<dtype, double> dist(inMean);

            stl_algorithms::for_each(returnArray.begin(), returnArray.end(),
                [&dist](dtype& value)  -> void
                { 
                    value = dist(generator_); 
                });

            return returnArray;
        }
    }  // namespace random
}  // namespace nc
