#ifndef PriorityCloudComparator_hpp
#define PriorityCloudComparator_hpp

#include <vector>
#include <string>
#include "PriorityPointCloud.hpp"



class PriorityCloudComparator {

public:
    PriorityCloudComparator();
    ~PriorityCloudComparator();

    bool operator()(PriorityPointCloud &a,PriorityPointCloud &b);

};

#endif /* PriorityCloudComparator_hpp */
