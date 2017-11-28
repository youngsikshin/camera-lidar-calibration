#pragma once
#include <memory>
#include <Eigen/Core>
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include "CameraModel.h"
#include "Datatypes.h"

namespace camlidar_calib {

class PinholeModel : public CameraModel {

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    typedef shared_ptr<PinholeModel> Ptr;

    PinholeModel (int width, int height, float fx, float fy, float cx, float cy,
                  float d0=0.0, float d1=0.0, float d2=0.0, float d3=0.0, float d4=0.0);

    ~PinholeModel();

    virtual inline bool is_in_image(Eigen::Vector2f uv, int boundary, float scale);
    virtual inline bool is_in_image(Eigen::Vector2f uv, int boundary);
    virtual inline bool is_in_image(const Point& point, int boundary);

    virtual inline Eigen::Vector2f xyz_to_uv(const Point& xyz);

    virtual void undistort_image(const cv::Mat& raw, cv::Mat& rectified);

    void show_intrinsic() { std::cerr << K_ << std::endl; }; 

    inline const Eigen::Matrix3f& K() const { return K_; };
    inline const Eigen::Matrix3f& K_inv() const { return K_inv_; };

    inline float fx() const { return fx_; };
    inline float fy() const { return fy_; };
    inline float cx() const { return cx_; };
    inline float cy() const { return cy_; };
    inline float d0() const { return d_[0]; };
    inline float d1() const { return d_[1]; };
    inline float d2() const { return d_[2]; };
    inline float d3() const { return d_[3]; };
    inline float d4() const { return d_[4]; };

private:
    const float fx_, fy_;
    const float cx_, cy_;

    bool distortion_;

    float d_[5];

    cv::Mat cvK_, cvD_;
    cv::Mat undist_map1_, undist_map2_;

    Eigen::Matrix3f K_;
    Eigen::Matrix3f K_inv_;

};

}   // namespace camlidar_calib
