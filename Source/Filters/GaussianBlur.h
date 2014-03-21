#ifndef _GAUSSIAN_BLUR_H_
#define _GAUSSIAN_BLUR_H_

#include "Filter.h"

class GaussianBlur : public Filter
{
	public:
		uchar* RunFilter( uchar* source, int width, int height, int channels );
};

#endif