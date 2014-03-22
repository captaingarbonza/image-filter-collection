#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include "Filter.h"

class Convolution
{
	public:
		static void HorizontalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );
		static void VerticalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );
		static void TwoDConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size );
};

#endif