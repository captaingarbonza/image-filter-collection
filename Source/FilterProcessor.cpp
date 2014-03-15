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

}

void
InitFilterLibrary()
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
	QImage result = image.copy();
	result.invertPixels();
	emit FilterDone( result );
}