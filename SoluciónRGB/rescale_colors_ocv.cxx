#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    //Get command line arguments
    if( argc < 3)
    {
        std::cerr<< "Usage: " << argv[ 0 ] << "image_file number_of_bits" << std::endl;
        return( -1 );
    } // fi


//Review given command line arguments
std::cout << "------------------" << std::endl;
for ( int a = 0; a < argc; a++ )
    std::cout << argv[ a ] << std::endl;
std::cout << "------------------" << std::endl;

//Read an image
Mat image;
image = imread( argv[1], 1 );

if( !image.data )
{
    std::cerr << "Error: No image data" << std::endl;
    return( -1 );
}

//Split channels
//Red
Mat redImage;
extractChannel(image, redImage, 2);
//Green
Mat greenImage;
extractChannel(image, greenImage, 1);
//Blue
Mat blueImage;
extractChannel(image, blueImage, 0);

//Quantize channels
  // Quantize Red
  uchar redTable[ 256 ];
  int scale = pow( 2, 8 - atoi( argv[ 2 ] ) );
  for (int i = 0; i < 256; ++i)
    redTable[ i ] = ( uchar )( scale * ( i / scale ) );

  Mat resint_red = Mat::zeros( image.size( ), CV_8UC1 );
  MatIterator_< uchar > itR, endR;
  for( itR = resint_red.begin< uchar >( ), endR = resint_red.end< uchar >( ); itR != endR; ++itR)
    *itR = redTable[*itR];

  // Quantize Green
  uchar greenTable[ 256 ];
  scale = pow( 2, 8 - atoi( argv[ 2 ] ) );
  for (int i = 0; i < 256; ++i)
    greenTable[ i ] = ( uchar )( scale * ( i / scale ) );

  Mat resint_green = Mat::zeros( image.size( ), CV_8UC1 );
  MatIterator_< uchar > itG, endG;
  for( itG = resint_green.begin< uchar >( ), endG = resint_green.end< uchar >( ); itG != endG; ++itG)
    *itG = greenTable[*itG];

  // Quantize Blue
  uchar blueTable[ 256 ];
  scale = pow( 2, 8 - atoi( argv[ 2 ] ) );
  for (int i = 0; i < 256; ++i)
    blueTable[ i ] = ( uchar )( scale * ( i / scale ) );

  Mat resint_blue = Mat::zeros( image.size( ), CV_8UC1 );
  MatIterator_< uchar > itB, endB;
  for( itB = resint_blue.begin< uchar >( ), endB = resint_blue.end< uchar >( ); itB != endB; ++itB)
    *itB = blueTable[*itB];

//Rescale channels
  // Rescale Red
  Mat lookUpTableR(1, 256, CV_8U);
  uchar* pR = lookUpTableR.data;
  for( int i = 0; i < 256; ++i)
    pR[i] = redTable[i];
  LUT(redImage, lookUpTableR, resint_red);

    // Rescale Green
  Mat lookUpTableG(1, 256, CV_8U);
  uchar* pG = lookUpTableG.data;
  for( int i = 0; i < 256; ++i)
    pG[i] =greenTable[i];
  LUT(greenImage, lookUpTableG, resint_green);

    // Rescale Blue
  Mat lookUpTableB(1, 256, CV_8U);
  uchar* pB = lookUpTableB.data;
  for( int i = 0; i < 256; ++i)
    pB[i] = blueTable[i];
  LUT(blueImage, lookUpTableB, resint_blue);


//Merging Channels
  Mat g, merged_image, blue_channel, green_channel, red_channel;
  vector<Mat> channels;
  g = Mat::zeros( image.size( ), CV_8UC1 ); //Zeros Mat
  
  //BGR complete image
  channels.push_back(resint_blue);
  channels.push_back(resint_green);
  channels.push_back(resint_red);
  merge(channels, merged_image);
  
  //Blue image
  channels.clear();
  channels.push_back(resint_blue);
  channels.push_back(g);
  channels.push_back(g);
  merge(channels, blue_channel);
  
  //Red image
  channels.clear();
  channels.push_back(g);
  channels.push_back(g);
  channels.push_back(resint_red);
  merge(channels, red_channel);
  
  //Blue image
  channels.clear();
  channels.push_back(g);
  channels.push_back(resint_green);
  channels.push_back(g);
  merge(channels, green_channel);
// Write results
  std::stringstream ss ( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );
  imwrite( basename + "_rescaleRed.png", red_channel );
  imwrite( basename + "_rescaleGreen.png", green_channel );
  imwrite( basename + "_rescaleBlue.png", blue_channel );
  imwrite( basename + "_rescaleImage.png", merged_image );
return (0);
}
