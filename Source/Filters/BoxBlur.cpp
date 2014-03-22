#include "BoxBlur.h"
#include "Convolution.h"

uchar*
BoxBlur::RunFilter( uchar* source, int width, int height, int channels )
{
	uchar* result = new uchar[width*height*channels];
	int kernel_size = 9;

	double* kernel = new double[kernel_size];
	for( int k = 0; k < kernel_size; k++ )
	{
		kernel[k] = 1.0/kernel_size;
	}

	Convolution::HorizontalConvo(source, result, width, height, channels, kernel, kernel_size);
	Convolution::VerticalConvo(result, result, width, height, channels, kernel, kernel_size);

	return result;
}