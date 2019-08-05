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

    namedWindow( "test", WINDOW_AUTOSIZE );

    // string uds = zmqUDS("/tmp/opencv_uds");
    HostInfo hi;
    string tcp = zmqTCP(hi.address, 9000);

    Subscriber s;
    s.connect(tcp);

    while(gecko::ok()){
        zmq::message_t msg = s.recv();

        if (msg.size() == 0) {
            cout << "Error: no image captured" << endl;
            gecko::msleep(50);
        }
        else {
            b_t b(msg);
            Mat src = b.get();

            imshow( "test", src );
            char c = (char) waitKey(10);
            if (c == 27) break;  // hit esc to quit
            else if (c == 'q') break;
        }
    }

    return 0;
}
