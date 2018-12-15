#ifndef Register_hpp
#define Register_hpp

#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <string>

#include "Utilities.hpp"
#include "BruteICP.hpp"
#include "NormalICP.hpp"
#include "PriorityPointCloud.hpp"
#include "PriorityCloudComparator.hpp"


class Register {

public:
    Register();

    Register(int alg,
             std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points);

    ~Register();

    //perform the actual registration
    void registration();

private:
    int alg =0;
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points = nullptr;
    BruteICP bruteICP = BruteICP();
    NormalICP normalICP = NormalICP();
    Utilities utilities;

};

#endif /* PriorityPointCloud_hpp */
