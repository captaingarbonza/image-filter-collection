#ifndef _IMAGE_ALGORITHMS_H_
#define _IMAGE_ALGORITHMS_H_

#include "Filter.h"

class ImageAlgorithms
{
	public:
		static void HorizontalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );
		static void VerticalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );
		static void TwoDConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );

		static void GrayScale( uchar* source, uchar* destination, int width, int height, int channels = 4, int alpha_channel = 3);
		static void ConvertToOneChannel( uchar* source, uchar* destination, int width, int height, int channels = 4, int alpha_channel = 3);
		static void ConvertFromOneChannel( uchar* source, uchar* destination, int width, int height, int channels = 4, int alpha_channel = 3);
		static void AddImages(uchar* image1, uchar* image2, uchar* result, int width, int height, int channels = 4);

		static void Sobel(uchar* source, uchar* gradient_magnitude, uchar* gradient_direction, int width, int height, int channels = 4);
};

#endif