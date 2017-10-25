#ifndef COLOR_TRANSFER_HPP
#define COLOR_TRANSFER_HPP

#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

vector<Scalar> imageStats(
    const Mat& scr  // input image
);

void colorTransfer(
    const Mat& scr, // source image (color that will be dst) 
    const Mat& tgt, // targer image (image that will receive the new color)
    Mat& dst        // output image
);
    
vector<Scalar> imageStats(const Mat& image) {
    Mat channels[3];
    Scalar mean[3], dev[3];
    vector<Scalar> meanDev;

    split(image, channels);
    for (int i=0; i<3;i++) {
        meanStdDev(channels[i], mean[i], dev[i]);
        meanDev.push_back(mean[i]);
        meanDev.push_back(dev[i]);        
    }

        // meanDev = (
            // mean(channel[0]),    -   mean from blue channel  
            // devStd(channel[0]),  -   devStd from blue channel 
            // mean(channel[1]),    -   mean from green channel 
            // devStd(channel[1]),  -   devStd from green channel 
            // mean(channel[1]),    -   mean from red channel 
            // devStd(channel[1])   -   devStd from red channels 
        // ) 
    return meanDev;
}

void colorTransfer(const Mat& scr, const Mat& tgt, Mat& dst) {
    Mat newScr, newTgt;

    // Convert the images from the RGB to L*ab*.
    cvtColor(scr, newScr, CV_BGR2Lab);
    cvtColor(tgt, newTgt, CV_BGR2Lab);

    // Convert the images to float32 
    newScr.convertTo(newScr, CV_32F);   
    newTgt.convertTo(newTgt, CV_32F);

    // Compute color statistics for the scr and tgt images
    vector<Scalar> meanDevScr = imageStats(newScr);
    vector<Scalar> meanDevTgt = imageStats(newTgt);

    // Split the tgt image into 3 channels (L, *a, *b) 
    Mat channels[3];
    split(newTgt, channels);
    
    // Subtract the means from the tgt image
	channels[0] -= meanDevTgt[0];
	channels[1] -= meanDevTgt[2];
    channels[2] -= meanDevTgt[4];
 
    // Scale by the standard deviations
    double a = meanDevTgt[1](0) / meanDevScr[1](0);
    double b = meanDevTgt[3](0) / meanDevScr[3](0);
    double c = meanDevTgt[5](0) / meanDevScr[5](0);

	channels[0] *= a;
    channels[1] *= b;
	channels[2] *= c;
     
	// Add in the scr mean
	channels[0] += meanDevScr[0];
	channels[1] += meanDevScr[2];
    channels[2] += meanDevScr[4];
    
	// Merge the channelss together and convert back to the BGR color space.
    merge(channels, 3, dst);
    dst.convertTo(dst, CV_8U);          
    cvtColor(dst, dst, CV_Lab2BGR);
}

#endif //COLOR_TRANSFER_HPP
