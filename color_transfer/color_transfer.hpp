#ifndef COLOR_TRANSFER_HPP
#define COLOR_TRANSFER_HPP

#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

vector<Scalar> imageStats(Mat image) {
    Mat channel[3];
    Scalar mean[3], dev[3];
    vector<Scalar> meanDev;

    split(image, channel);
    for (int i=0; i<3;i++) {
        meanStdDev(channel[i], mean[i], dev[i]);
        meanDev.push_back(mean[i]);
        meanDev.push_back(dev[i]);        
    }

    // meanDev = (mean(channel[0]), devStd(channel[0]), mean(channel[1]), devStd(channel[1]), mean(channel[1]), devStd(channel[1])) 
    return meanDev;
}

Mat colorTransfer(Mat source, Mat target) {
    // Convert the images from the RGB to L*ab*.
    cvtColor(source, source, CV_BGR2Lab);
    cvtColor(target, target, CV_BGR2Lab);

    // Convert the images to float32 
    source.convertTo(source, CV_32F);   
    target.convertTo(target, CV_32F);

    // Compute color statistics for the source and target images
    vector<Scalar> meanDevScr = imageStats(source);
    vector<Scalar> meanDevTar = imageStats(target);

    // Split the target image into 3 channels (L, *a, *b) 
    Mat channel[3];
    split(target, channel);
    
    // Subtract the means from the target image
	channel[0] -= meanDevTar[0];
	channel[1] -= meanDevTar[2];
    channel[2] -= meanDevTar[4];
 
    // Scale by the standard deviations
    double a = meanDevTar[1](0) / meanDevScr[1](0);
    double b = meanDevTar[3](0) / meanDevScr[3](0);
    double c = meanDevTar[5](0) / meanDevScr[5](0);

	channel[0] *= a;
    channel[1] *= b;
	channel[2] *= c;
     
	// Add in the source mean
	channel[0] += meanDevScr[0];
	channel[1] += meanDevScr[2];
    channel[2] += meanDevScr[4];
    
	// Merge the channels together and convert back to the BGR color space.
    Mat transfer;
    merge(channel, 3, transfer);
    transfer.convertTo(transfer, CV_8U);          
    cvtColor(transfer, transfer, CV_Lab2BGR);

    return transfer;
}

#endif //COLOR_TRANSFER_HPP
