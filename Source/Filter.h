#ifndef _FILTER_H_
#define _FILTER_H_

typedef unsigned char uchar;

class Filter
{
	public:
		virtual ~Filter() {}
		virtual uchar* RunFilter( uchar* source, int width, int height, int channels ) = 0;
};
#endif