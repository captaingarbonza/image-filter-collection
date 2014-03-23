///
/// A filter that performs Canny edge detection.
///
/// Created by Crystal Valente.
///

#include "Canny.h"
#include "ImageAlgorithms.h"

void 
NonmaximumSupression( uchar* gradient_magnitude, uchar* gradient_direction, uchar* edges, int width, int height )
///
/// Supresses the gradient magnitude if it is not the local maximum in it's search direction.
///
/// @param gradient_magnitude
///  The intensity of the gradient at each point in the image.
///
/// @param gradient_direction
///  The direction of the gradient at each point in the image.
///
/// @param edges
///  An empty image that stores the resulting edge information.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @return
///  Nothing.
/// 
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			// Set gradient strength to zero if edges are not the maximum in their search direction.
			int search_direction = gradient_direction[j*width + i];
			if( search_direction > 180 ) search_direction = search_direction % 180;
			int x_pos = 0;
			int y_pos = 0;
			if( search_direction > 22.5 && search_direction <= 67.5 )
			{
				// 45 degrees, north-west/south-east
				x_pos = 1;
				y_pos = 1;
			}
			else if( search_direction > 67.5 && search_direction <= 112.5 )
			{
				// 90 degrees, east/west
				x_pos = 0;
				y_pos = 1;
			}
			else if( search_direction > 112.5 && search_direction <= 157.5)
			{
				// 135 degrees, north-east/south-west
				x_pos = -1;
				y_pos = 1;
			}
			else
			{
				// 0 degrees, north/south
				x_pos = 1;
				y_pos = 0;
			}
			edges[j*width + i] = gradient_magnitude[j*width + i];
			if( j - y_pos >= 0 && i - x_pos >= 0 && j - y_pos < height && i - x_pos < width && !(x_pos == 0 && y_pos == 0) )
			{
				if( gradient_magnitude[(j - y_pos)*width + i - x_pos] > gradient_magnitude[j*width + i])
				{
					edges[j*width + i] =  0;
				}
			}
			if( j + y_pos >= 0 && i + x_pos >= 0 && j + y_pos < height && i + x_pos < width && !(x_pos == 0 && y_pos == 0) )
			{
				if( gradient_magnitude[(j + y_pos)*width + i + x_pos] > gradient_magnitude[j*width + i])
				{
					edges[j*width + i] = 0;
				}
			}
		}
	}
}

void 
Hysteresis( uchar* edges, int width, int height, int max_threshold, int min_threshold )
///
/// Traces connected edges to minimize noise. An edge begins if it strength is greater than
/// or equal to the maximum threshold and continues until it drops below the minimum threshold.
///
/// @param edges
///  The gradient magnitude at each point in the image.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param max_threshold
///  The maximum threshold. Edge tracing begins if an edge is at least this intensity.
///
/// @param min_threshold
///  The minimum threshold. Edge tracing ends if an edge drops below this intensity.
///
/// @return
///  Nothing.
{
	for( int j = 0; j < height; j++ )
	{
		for( int i = 0; i < width; i++ )
		{
			if( edges[j*width + i] >= max_threshold )
			{
				// Set pixels that definitely edges to 255
				edges[j*width + i] = 255;
			} 
			else if( edges[j*width + i] >= min_threshold )
			{
				// Set pixels that might be edges to 100
				edges[j*width + i] = 100;
			}
			else
			{
				// Set pixels that are not edges to 0
				edges[j*width + i] = 0;
			}

		}
	}

	// Perform hysteresis on the image until the whole image is traversed with no new edges
	bool done = false;
	while( !done )
	{
		done = true;
		for( int j = 1; j < height - 1; j++ )
		{
			for( int i = 1; i < width - 1; i++ )
			{
				if( edges[j*width + i] > 0 && edges[j*width + i] < 255 )
				{
					// If a pixel is undecided, set it to be an edge if it has any neighbours that are edges
					if( edges[(j-1)*width + (i-1)] == 255 || edges[(j-1)*width + i] == 255 || edges[(j-1)*width + (i+1)] == 255 ||
						edges[j*width + (i-1)] == 255 || edges[j*width + (i+1)] == 255 ||
						edges[(j+1)*width + (i-1)] == 255 || edges[(j+1)*width + i] == 255 || edges[(j+1)*width + (i+1)] == 255 )
					{
						edges[j*width + i] = 255;
						done = false;
					}
						
				}
			}
		}
	}

	// We have found all the edges, so set any remaining undecided pixels to 0
	for( int j = 0; j < height; j ++ )
	{
		for( int i = 0; i < width; i++ )
		{
			if( edges[j*width + i] < 255 && edges[j*width + i] > 0)
			{
				edges[j*width + i] = 0;
			}
		}
	}
}

uchar*
CannyEdge::RunFilter( uchar* source, int width, int height, int channels )
///
/// Runs Canny edge detection on a given image and returns the result.
///
/// @param source
///  The source image to perform the edge detection on.
///
/// @param width
///  The width of the image.
///
/// @param height
///  The height of the image.
///
/// @param channels
///  The number of color channels that the image contains.
///
/// @return
///  The image resulting from the edge detection in the same size and format as source.
///
{
	uchar* result = new uchar[width*height*channels];
	uchar* smoothed = new uchar[width*height*channels];

	// Apply a Gaussian blur with kernel size 5 to get rid of any noise
	double kernel[5] = {5.0/49, 12.0/49, 15.0/49, 12.0/49, 5.0/49};
	int kernel_size = 5;
	ImageAlgorithms::HorizontalConvo(source, smoothed, width, height, channels, kernel, kernel_size);
	ImageAlgorithms::VerticalConvo(smoothed, smoothed, width, height, channels, kernel, kernel_size);

	// Apply the sobel operator to the smoothed image to approximate the image gradients
	uchar* gradient_magnitude = new uchar[width*height];
	uchar* gradient_direction = new uchar[width*height];
	ImageAlgorithms::Sobel( smoothed, gradient_magnitude, gradient_direction, width, height, channels );
	delete [] smoothed;

	// Apply nonmaximum supression to thin edges
	uchar* edges = new uchar[width*height];
	NonmaximumSupression( gradient_magnitude, gradient_direction, edges, width, height );
	delete [] gradient_magnitude;
	delete [] gradient_direction;

	// Apply hysteresis to minimize streaking
	double max_threshold = 80;
	double min_threshold = 20;
	Hysteresis( edges, width, height, max_threshold, min_threshold );

	// Convert the result back to a four channel image to be displayed
	// This step is only necessary if the image is being displayed rather
	// than used by another filter for it's edge information
	ImageAlgorithms::ConvertFromOneChannel( edges, result, width, height, channels);

	delete [] edges;

	return result;
}