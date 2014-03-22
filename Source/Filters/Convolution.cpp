///
/// A helper class for image filtering that performs convolutions for given images and kernels.
///
/// Created by Crystal Valente
///

#include "Convolution.h"

void
Convolution::HorizontalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a horizontal convolution using a given 1D kernel.
///
/// @param source
///  The source image data
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source)
///
/// @param width
///  The width of the image
///
/// @param height
///  The height of the image
///
/// @param channels
///  The number of color channels in the image
///
/// @param kernel
///  A pointer to the 1D kernel to be used for convolution
///
/// @param kernel_size
///  The size of the given kernel
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			for( int c = 0; c < channels; c++ )
			{
				double total = 0.0;
				for( int kx = 0; kx < kernel_size; kx++ )
				{
                    int x_pos = i + kx - kernel_size/2;
                    if( x_pos < 0 ) x_pos = 0;
                    if( x_pos >= width ) x_pos = width - 1;

                    total += source[j*width*channels + x_pos*channels + c]*kernel[kx];
				}
                if( total > 255 ) total = 255;
                if( total < 0 ) total = 0;
				destination[(j)*width*channels + (i)*channels + c] = (uchar)total;
			}
		}
	}
}

void
Convolution::VerticalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a vertical convolution using a given 1D kernel.
///
/// @param source
///  The source image data
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source)
///
/// @param width
///  The width of the image
///
/// @param height
///  The height of the image
///
/// @param channels
///  The number of color channels in the image
///
/// @param kernel
///  A pointer to the 1D kernel to be used for convolution
///
/// @param kernel_size
///  The size of the given kernel
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			for( int c = 0; c < channels; c++ )
			{
				double total = 0.0;
				for( int ky = 0; ky < kernel_size; ky++ )
				{
                    int y_pos = j + ky - kernel_size/2;
                    if( y_pos < 0 ) y_pos = 0;
                    if( y_pos >= height ) y_pos = height - 1;

                    total += source[y_pos*width*channels + i*channels + c]*kernel[ky];
				}
                if( total > 255 ) total = 255;
                if( total < 0 ) total = 0;
				destination[(j)*width*channels + (i)*channels + c] = (uchar)total;
			}
		}
	}
}

void
Convolution::TwoDConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a 2D convolution using a given 2D kernel.
///
/// @param source
///  The source image data
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source)
///
/// @param width
///  The width of the image
///
/// @param height
///  The height of the image
///
/// @param channels
///  The number of color channels in the image
///
/// @param kernel
///  A pointer to the 2D kernel to be used for convolution
///
/// @param kernel_size
///  The width and height of the given kernel i.e the kernel is an kernel_size * kernel_size array
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			for( int c = 0; c < channels; c++ )
			{
				double total = 0.0;
				for( int ky = 0; ky < kernel_size; ky++ )
				{
					for( int kx = 0; kx < kernel_size; kx++ )
					{
                    	int y_pos = j + ky - kernel_size/2;
                    	if( y_pos < 0 ) y_pos = 0;
                    	if( y_pos >= height ) y_pos = height - 1;

                    	int x_pos = i + kx - kernel_size/2;
                    	if( x_pos < 0 ) x_pos = 0;
                    	if( x_pos >= width ) x_pos = width - 1;

                    	total += source[y_pos*width*channels + x_pos*channels + c]*kernel[ky*kernel_size + kx];
					}
				}
                if( total > 255 ) total = 255;
                if( total < 0 ) total = 0;
				destination[(j)*width*channels + (i)*channels + c] = (uchar)total;
			}
		}
	}
}