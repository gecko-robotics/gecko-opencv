#pragma once

#include <gecko/gecko.hpp>
#include <gecko/msgpack/msgs.hpp>
#include <opencv2/opencv.hpp>

class b_t: public base_t {
public:
    b_t(): base_t(31) {}
    b_t(const cv::Mat img): base_t(31), width(img.cols), height(img.rows), channels(img.channels()) {
        cv::imencode(".jpg", img, buffer);
    }
    b_t(const b_t& a): base_t(31), width(a.width), height(a.height), buffer(a.buffer), channels(a.channels) {}
    bool operator==(const b_t& v) const {
        if((width == v.width) && (height == v.height) && (buffer == v.buffer) && (channels == v.channels))
            return true;
        return false;
    }
    cv::Mat get(){
        return cv::imdecode(buffer, channels == 1 ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
    }
    uint32_t width, height, channels;
    std::vector<uint8_t> buffer;
    MSGPACK_DEFINE(width, height, channels, buffer);
    GECKO_MSG(b_t, 31);
};
