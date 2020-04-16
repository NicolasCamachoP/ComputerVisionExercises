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
    //Create destination Mats
    Mat dstH1H2 = Mat::zeros( src.size(), CV_8UC3);
    Mat dstH2H3 = Mat::zeros( src.size(), CV_8UC3);

    //Create H1H2 Kernel
    float coefs1[9] = {-0.25,0,0.25,-0.5,0,0.5,-0.25,0,0.25};
    Mat kerH1H2 = Mat(3,3,CV_32FC1,&coefs1);
    //Create H2H3 Kernel
    float coefs2[9] = {-0.25,-0.5,-0.25,0.75,1.5,0.75,-0.25,-0.5,-0.25};
    Mat kerH2H3 = Mat(3,3,CV_32FC1,&coefs2);    

    //Apply the Kernels
    Point anchor = Point(-1,-1);
    int ddepth = -1;
    double delta = 0;
    //Kernel H1H2
    filter2D(src, dstH1H2, ddepth, kerH1H2, anchor, delta, BORDER_DEFAULT);
    //Kernel H2H3
    filter2D(src, dstH2H3, ddepth, kerH2H3, anchor, delta, BORDER_DEFAULT);
    
    std::stringstream ss ( argv[ 1 ] );
    std::string basename;
    getline( ss, basename, '.' );
    imwrite( basename + "_H1H2.png", dstH1H2);
    imwrite( basename + "_H2H3.png", dstH2H3);
    
    return 0;
  } 
