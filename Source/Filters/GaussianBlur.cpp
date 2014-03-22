#include "GaussianBlur.h"
#include "Convolution.h"

uchar*
GaussianBlur::RunFilter( uchar* source, int width, int height, int channels )
{
	uchar* result = new uchar[width*height*channels];
	double kernel[9] = {0.0947416, 0.118318, 0.0947416, 0.118318, 0.147761, 0.118318, 0.0947416, 0.118318, 0.0947416 };
	//double kernel[3] = {0.118318, 0.147761, 0.118318};
	int kernel_size = 3;

	Convolution::TwoDConvo(source, result, width, height, channels, kernel, kernel_size);
	//Convolution::HorizontalConvo(source, result, width, height, channels, kernel, kernel_size);
	//Convolution::VerticalConvo(result, result, width, height, channels, kernel, kernel_size);

	return result;
}