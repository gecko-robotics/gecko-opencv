#include <iostream>
#include <string>
#include <gecko/gecko.hpp>
#include <gecko/msgpack/msgs.hpp>
#include <opencv2/opencv.hpp>

#include "message.hpp"

using namespace cv;
using namespace std;

int main(){
    gecko::init();
    Mat src;
    VideoCapture cam;
    cam.open(0);
    cam.set(CAP_PROP_FRAME_WIDTH, 640);
    cam.set(CAP_PROP_FRAME_HEIGHT, 480);
    // namedWindow( "test", WINDOW_AUTOSIZE );

    // string uds = zmqUDS("/tmp/opencv_uds");

    HostInfo hi;
    string tcp = zmqTCP(hi.address, 9000);

    Publisher p;
    p.bind(tcp);

    Rate rate(20);

    while(gecko::ok()){
        cam >> src;

        if (src.empty()) {
            cout << "Error: no image captured" << endl;
        }
        else {
            Mat grey;
            cvtColor(src, grey, COLOR_BGR2GRAY);
            b_t b(grey);
            zmq::message_t m = b.pack();
            p.publish(m);

            // imshow( "test", src );
            // char c = (char) waitKey(100);
            // if (c == 27) break;  // hit esc to quit
        }
        rate.sleep();
        // cout << "publish" << endl;
    }

    cam.release();

    return 0;
}
