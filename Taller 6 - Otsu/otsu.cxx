#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
  // Get command line arguments
  if ( argc < 2 )
  {
  	std::cerr << "Usage: " << argv[ 0 ] << " image_file" << std::endl;
    return( -1 );

  } // fi

  // Review given command line arguments
  std::cout << "-------------------------" << std::endl;
  for( int a = 0; a < argc; a++ )
    std::cout << argv[ a ] << std::endl;
  std::cout << "-------------------------" << std::endl;

  // Read an image
  Mat image;
  image = imread( argv[1], 1 );

  if ( !image.data )
  {
    std::cerr << "Error: No image data" << std::endl;
    return( -1);
  
  } // fi
  
  //Save basename 
  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename ,'.' );
  
  //Turn into GrayScale
  Mat image_gray;
  cvtColor( image, image_gray, COLOR_RGB2GRAY );
  
  //Threshold
  Mat image_TH;
  threshold(image_gray, image_TH, 127, 256, THRESH_BINARY);


  //Write something
  imwrite( basename + "_gray.png", image_gray);
  imwrite( basename + "_ThreshTest.png", image_TH);
  return( 0 );
}

// eof - example.cxx