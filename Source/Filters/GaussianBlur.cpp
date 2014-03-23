///
/// A filter than performs gaussian blur on an image.
///
/// Created by Crystal Valente.
///

#include "GaussianBlur.h"
#include "ImageAlgorithms.h"

uchar*
GaussianBlur::RunFilter( uchar* source, int width, int height, int channels )
///
/// Runs gaussian blur on a given image and returns the result.
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
///  The image resulting from the gaussian blur in the same size and format as source.
///
{
	uchar* result = new uchar[width*height*channels];
	double kernel[3] = {1.0/4.0, 2.0/4.0, 1.0/4.0};
	int kernel_size = 3;

	ImageAlgorithms::HorizontalConvo(source, result, width, height, channels, kernel, kernel_size);
	ImageAlgorithms::VerticalConvo(result, result, width, height, channels, kernel, kernel_size);

	return result;
}