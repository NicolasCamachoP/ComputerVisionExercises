#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


/** @function main */
 int main( int argc, char** argv )
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
  Mat src;
  src = imread( argv[1], 1 );

  if ( !src.data )
  {
    std::cerr << "Error: No image data" << std::endl;
    return( -1);
  
  } // fi
  
   //Create transformation matrix
    Mat Mt(2,3,CV_64F, cvScalar(0.0));
    Mt.at<double>(0,0) = 0.625;
    Mt.at<double>(0,1) = -0.7577722283;
    Mt.at<double>(0,2) = -21;
    Mt.at<double>(1,0) = 1.082531755;
    Mt.at<double>(1,1) = 0.4375;
    Mt.at<double>(1,2) = 15;    
    

    //Do de convolution and save it in resul
    Mat resul=Mat::zeros(src.rows,src.cols,src.type());
    warpAffine(src, resul, Mt, src.size());
    
    std::stringstream ss ( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );
    imwrite( basename + "_transformed.png", resul);
    
    return 0;
  } 
