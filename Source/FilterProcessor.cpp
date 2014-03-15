#include "FilterProcessor.h"

using namespace std;

FilterProcessor::FilterProcessor()
///
/// Constructor
///
{

}

FilterProcessor::~FilterProcessor()
///
/// Destructor
///
{
    wait();
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
        mImage.invertPixels();

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
	start();
}