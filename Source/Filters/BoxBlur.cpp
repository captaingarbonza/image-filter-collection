///
/// A filter than performs box blur on an image.
///
/// Created by Crystal Valente.
///

#include "BoxBlur.h"
#include "ImageAlgorithms.h"

uchar*
BoxBlur::RunFilter( uchar* source, int width, int height, int channels )
///
/// Runs the box blur filter on an image and returns the result.
///
/// @param source
///  The image to be blurred.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels that the image contains.
///
/// @return
///  The image resulting from the box blur in the same size and format as source.
///
{
	uchar* result = new uchar[width*height*channels];
	int kernel_size = 9;

	double* kernel = new double[kernel_size];
	for( int k = 0; k < kernel_size; k++ )
	{
		kernel[k] = 1.0/kernel_size;
	}

	ImageAlgorithms::HorizontalConvo(source, result, width, height, channels, kernel, kernel_size);
	ImageAlgorithms::VerticalConvo(result, result, width, height, channels, kernel, kernel_size);

	return result;
}