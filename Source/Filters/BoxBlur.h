#ifndef _BOX_BLUR_H_
#define _BOX_BLUR_H_

#include "Filter.h"

class BoxBlur : public Filter
{
	public:
		uchar* RunFilter( uchar* source, int width, int height, int channels );
};


#endif