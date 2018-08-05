# Color Transfer

## Getting Started

The `color_transfer.hpp` header file is an OpenCV implementation based on [Color Transfer
between Images](http://ieeexplore.ieee.org/document/946629/) [Reinhard et al., 2001] and [Adrian Rosebrock repository](https://github.com/jrosebr1/color_transfer) (for Python). The algorithm requires only the mean and standard deviation of pixel intensities for each channel in the L*a*b* color space.

This is an C++ approach from the above methods, for more information I recommend the above article or [Adrian's post on his blog](http://www.pyimagesearch.com/2014/06/30/super-fast-color-transfer-images/).


### Requirements

* OpenCV
* boost/program_options*

*Optional - Used to get the input images from terminal


### Installing

Just download this repository and use the header file `color_transfer.hpp` contained in the color_transfer folder.


## Running the tests

A example is in sample folder. After compiling it, run the code below

<code>$ ./color_transfer -s ../images/sunset.jpg -t ../images/ocean_day.jpg</code>
![alt text](https://github.com/Humberto-Neto/color_transfer/blob/master/docs/images/Results.png)

<code>$ ./color_transfer -s ../images/autumn.jpg -t ../images/woods.jpg</code>
![alt text](https://github.com/Humberto-Neto/color_transfer/blob/master/docs/images/Results2.png)

<code>$ ./color_transfer -s ../images/old_pic.jpg -t ../images/city.jpg</code>
![alt text](https://github.com/Humberto-Neto/color_transfer/blob/master/docs/images/Results3.png)

<code>$ ./color_transfer -s ../images/florest_day.jpg -t ../images/florest_dark.jpg</code>
![alt text](https://github.com/Humberto-Neto/color_transfer/blob/master/docs/images/Results4.png)


## Authors

* **Humberto da Silva Neto** - *Initial work*


## License

[MIT LICENSE](https://github.com/hsneto/color_transfer/blob/master/LICENSE)


## Acknowledgments

* [Adrian Rosebrock](https://github.com/jrosebr1)
* [Reinhard et al., 2001]
