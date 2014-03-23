#ifndef _CANNY_H_
#define _CANNY_H_

#include "Filter.h"

class CannyEdge : public Filter
{
	public:
		uchar* RunFilter( uchar* source, int width, int height, int channels );
};


#endif