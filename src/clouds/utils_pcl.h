#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <string>
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>


typedef pcl::PointCloud<pcl::PointXYZRGB> ColorCloud;
typedef pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr ConstColorCloudPtr;
typedef pcl::PointCloud<pcl::PointXYZRGB>::Ptr ColorCloudPtr;

pcl::PointCloud<pcl::PointXYZRGB>::Ptr readPCD(const std::string& pcdfile);

Eigen::MatrixXi xyz2uv(const Eigen::MatrixXf& xyz);

Eigen::MatrixXf toEigenMatrix(ColorCloudPtr);
Eigen::MatrixXf getDepthImage(ColorCloudPtr);
pcl::PointCloud<pcl::PointXYZ>::Ptr toPointCloud(const std::vector< std::vector<float> >&);

typedef Eigen::Matrix<uint8_t,Eigen::Dynamic,Eigen::Dynamic> MatrixXb;
MatrixXb toBGR(ColorCloudPtr);
cv::Mat toCVMat(Eigen::MatrixXf);

