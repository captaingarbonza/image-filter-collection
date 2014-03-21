#include "FilterProcessor.h"
#include "Filters/InvertFilter.h"
#include "Filters/GaussianBlur.h"

typedef boost::shared_ptr<Filter> filter_ptr;

using namespace std;

FilterProcessor::FilterProcessor()
///
/// Constructor
///
{
	InitFilterLibrary();
}

FilterProcessor::~FilterProcessor()
///
/// Destructor
///
{
    wait();
    mFilterLibrary.clear();
}

void
FilterProcessor::run()
///
/// Runs the thread work for the filter processing thread. 
/// Runs a loop which continues until the thread is aborted.
/// The thread starts running by calling the start() function.
///
/// @return
///  Nothing
///
{
	if( !mImage.isNull() )
	{
		QMutexLocker locker(&mutex);
        uchar* source = mImage.bits();
        uchar* result = mFilterLibrary[mFilterName]->RunFilter(source, mImage.width(), mImage.height(), 4);
        mImage = QImage(result, mImage.width(), mImage.height(), mImage.format());

        // Pass the processed canvas to anyone who is interested
		emit FilterDone( mImage );
	}
}

void
FilterProcessor::InitFilterLibrary()
///
/// Adds the default filters to the filter collection
///
{
	mFilterLibrary["invert"] = filter_ptr( new InvertFilter() );
	mFilterLibrary["gaussian"] = filter_ptr( new GaussianBlur() );
}

void
FilterProcessor::StartFilter( string filter_name, QImage image )
///
/// Runs a given filter on a given image and returns the resulting image.
///
/// @param filter_name
///  The name of the filter to be applied
///
/// @param image
///  The image to be filtered
///
/// @return
///  The image resulting from the filtering process
///
{
	QMutexLocker locker(&mutex);
	mImage = image.copy();
	mFilterName = filter_name;
	start();
}