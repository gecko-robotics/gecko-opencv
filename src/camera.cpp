#include <iostream>
// #include <gecko/gecko.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
    Mat src;
    VideoCapture cam;
    cam.open(0);
    // cam.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    // cam.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    // namedWindow( "test", WINDOW_AUTOSIZE );

    while(1){
        cam >> src;

        if (src.empty()) {
            cout << "Error: no image captured" << endl;
        }
        else {
            // imshow( "test", src );
            // char c = (char) waitKey(100);
            // if (c == 27) break;  // hit esc to quit
        }
    }

    cam.release();
    return 0;
}
