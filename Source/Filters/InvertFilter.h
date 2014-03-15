#ifndef _INVERT_FILTER_H_
#define _INVERT_FILTER_H_

#include "Filter.h"

class InvertFilter : public Filter
{
	public:
		uchar* RunFilter( uchar* source, int width, int height, int channels );
};

#endif