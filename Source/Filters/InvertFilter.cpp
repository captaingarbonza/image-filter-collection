#include "InvertFilter.h"

uchar*
InvertFilter::RunFilter( uchar* source, int width, int height, int channels )
{
	uchar* pointer = source;
	for( int i = 0; i < width*height*channels; i++ )
	{
		if( i%4 != 3 ) // alpha
		{
			*pointer = 255 - *pointer;
		}
		pointer++;
	}
	return source;
}