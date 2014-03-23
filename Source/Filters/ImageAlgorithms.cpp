///
/// A helper class for image filtering that performs convolutions for given images and kernels.
///
/// Created by Crystal Valente.
///

#include "ImageAlgorithms.h"

#include <math.h>

#define PI 3.14159265

void
ImageAlgorithms::HorizontalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a horizontal convolution using a given 1D kernel.
///
/// @param source
///  The source image data.
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source).
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels in the image.
///
/// @param kernel
///  A pointer to the 1D kernel to be used for convolution.
///
/// @param kernel_size
///  The size of the given kernel.
///
/// @return
///  Nothing.
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
ImageAlgorithms::VerticalConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a vertical convolution using a given 1D kernel.
///
/// @param source
///  The source image data.
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source).
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels in the image.
///
/// @param kernel
///  A pointer to the 1D kernel to be used for convolution.
///
/// @param kernel_size
///  The size of the given kernel.
///
/// @return
///  Nothing.
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
ImageAlgorithms::TwoDConvo( uchar* source, uchar* destination, int width, int height, int channels, double* kernel, int kernel_size )
///
/// Performs a 2D convolution using a given 2D kernel.
///
/// @param source
///  The source image data.
///
/// @param destination
///  The image data where the result is to be stored (must be the same dimensions as source).
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels in the image.
///
/// @param kernel
///  A pointer to the 2D kernel to be used for convolution.
///
/// @param kernel_size
///  The width and height of the given kernel i.e the kernel is an kernel_size * kernel_size array.
///
/// @return
///  Nothing.
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

void
ImageAlgorithms::GrayScale(uchar* source, uchar* destination, int width, int height, int channels, int alpha_channel )
///
/// Converts an RGB image to gray scale by averaging each color component while retaining the same number of channels.
///
/// @param source
///  The image to be converted.
///
/// @param destination
///  The image that will store the resulting gray scale image.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels that the image contains. 4 by default.
///
/// @param alpha_channel
///  The index of the image's alpha channel. -1 if it has no alpha. 3 by default.
///
/// @return
///  Nothing.
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			double average = 0;
			for( int c = 0; c < channels; c++ )
			{
				if( c%channels != alpha_channel || alpha_channel == -1 ) // don't include the alpha channel
				{
					average += source[j*width*channels + i*channels + c];
				}
			}
			average /= alpha_channel == - 1 ? channels : channels - 1;
			if( average > 255 ) average = 255;
			if( average < 0 ) average = 0;
			for( int c = 0; c < channels; c++ )
			{
				if( c%channels != alpha_channel || alpha_channel == -1 ) // don't include the alpha channel
				{
					destination[j*width*channels + i*channels + c] = (uchar)average;
				}
				else
				{
					destination[j*width*channels + i*channels + c] = source[j*width*channels + i*channels + c];
				}
			}
		}
	}
}

void
ImageAlgorithms::ConvertToOneChannel(uchar *source, uchar *destination, int width, int height, int channels, int alpha_channel)
///
/// Converts a multichannel image to a one channel image by averaging each color component excluding the alpha channel.
///
/// @param source
///  The image to be converted.
///
/// @param destination
///  The image that will store the resulting one channel image.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels that the source image contains. 4 by default.
///
/// @param alpha_channel
///  The index of the source image's alpha channel. -1 if it has no alpha. 3 by default.
///
/// @return
///  Nothing.
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			double average = 0.0;
			for( int c = 0; c < channels; c++ )
			{
				if( c%channels != alpha_channel || alpha_channel == -1) // don't include the alpha channel
				{
					average += source[j*width*channels + i*channels + c];
				}
			}
			average /= alpha_channel == -1 ? channels : channels - 1;
			if( average < 0 ) average = 0;
			if( average > 255 ) average = 255;
			destination[j*width + i] = average;
		}
	}
}

void
ImageAlgorithms::ConvertFromOneChannel(uchar *source, uchar *destination, int width, int height, int channels, int alpha_channel)
///
/// Converts a one channel image to a multichannel image by setting each color component to the pixel value of the one channel image,
/// (except the alpha channel if there is one, which is set to 255).
///
/// @param source
///  The image to be converted.
///
/// @param destination
///  The image that will store the resulting multichannel image.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels that the destination image will contain. 4 by default.
///
/// @param alpha_channel
///  The index of the destination image's alpha channel. -1 if it has no alpha. 3 by default.
///
/// @return
///  Nothing.
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			for( int c = 0; c < channels; c++ )
			{
				if( c%channels != alpha_channel || alpha_channel == -1 ) // don't include the alpha channel
				{
					destination[j*width*channels + i*channels + c] = source[j*width + i];
				}
				else
				{
					destination[j*width*channels + i*channels + c] = 255;
				}
			}
		}
	}
}

void
ImageAlgorithms::AddImages(uchar *image1, uchar *image2, uchar *result, int width, int height, int channels)
///
/// Adds two images by adding their color components at every pixel. Values are clipped at 0 and 255.
///
/// @param image1
///  The first image to be added.
///
/// @param image2
///  The second image to be added.
///
/// @param result
///  The image that results from adding the two images.
///
/// @param width
///  The width of the images.
///
/// @param height
///  The height of the images.
///
/// @param channels
///  The number of color channels that the images contain. 4 by default.
///
/// @return
///  Nothing.
///
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			for( int c = 0; c < channels; c++ )
			{
				int pixel = j*width*channels + i*channels + c;
				int total = image1[pixel] + image2[pixel];
				if( total < 0 ) total = 0;
				if( total > 255 ) total = 255;
				result[pixel] = total;
			}
		}
	}
}

void
ImageAlgorithms::Sobel(uchar *source, uchar *gradient_magnitude, uchar* gradient_direction, int width, int height, int channels)
///
/// Performs the sobel operator on a given image, which gives an approximation of the image
/// gradients which is useful for edge detection.
///
/// @param source
///  The source image.
///
/// @param gradient_magnitude
///  A one channel image that stores the gradient strength returned by the sobel operator at each point.
///
/// @param gradient_direction
///  A one channel image that stores the gradient direction returned by the sobel operator at each point.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of channels in the source image.
///
/// @return
///  Nothing.
{
	ImageAlgorithms::ConvertToOneChannel( source, gradient_magnitude, width, height, channels);

	uchar* gx = new uchar[width*height];
	uchar* gy = new uchar[width*height];
	double sobel_x[9] = {-1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0};
	double sobel_y[9] = {1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0};

	ImageAlgorithms::TwoDConvo(gradient_magnitude, gx, width, height, 1, sobel_x, 3);
	ImageAlgorithms::TwoDConvo(gradient_magnitude, gy, width, height, 1, sobel_y, 3);

	// Added together the gradient images in the x and y direction
	ImageAlgorithms::AddImages(gx, gy, gradient_magnitude, width, height, 1);

	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			if( gx[j*width + i] != 0)
			{
				int direction = atan(gy[j*width + i]/gx[j*width + i]) * 180 / PI;
				gradient_direction[j*width + i] = direction;
			}
			else if( gy[j*width + i] == 0)
			{
				gradient_direction[j*width + i] = 0;
			}
			else
			{
				gradient_direction[j*width + i] = 90;
			}
		}
	}

	delete [] gx;
	delete [] gy;
}