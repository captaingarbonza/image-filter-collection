///
/// A filter than inverts an image.
///
/// Created by Crystal Valente.
///

#include "InvertFilter.h"

uchar*
InvertFilter::RunFilter( uchar* source, int width, int height, int channels )
///
/// Inverts each pixel in an image and returns the result.
///
/// @param source
///  The image to be inverted.
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
///  The image resulting from the inversion in the same size and format as source.
///
{
	uchar* result = new uchar[width*height*channels];
	for( int i = 0; i < width*height*channels; i++ )
	{
		if( i%4 != 3 ) // alpha
		{
			result[i] = 255 - source[i];
		}
		else
		{
			result[i] = source[i];
		}
	}
	return result;
}