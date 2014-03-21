#include "InvertFilter.h"

uchar*
InvertFilter::RunFilter( uchar* source, int width, int height, int channels )
{
	uchar* data = new uchar[width*height*channels];
	uchar* pointer = source;
	for( int i = 0; i < width*height*channels; i++ )
	{
		if( i%4 != 3 ) // alpha
		{
			data[i] = 255 - pointer[i];
		}
		else
		{
			data[i] = pointer[i];
		}
	}
	return data;
}