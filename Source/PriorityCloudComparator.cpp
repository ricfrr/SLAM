#include "../Headers/PriorityCloudComparator.hpp"

bool PriorityCloudComparator::operator()(PriorityPointCloud &a,PriorityPointCloud &b){
    return a.priority>b.priority;
}

PriorityCloudComparator::PriorityCloudComparator() {

}

PriorityCloudComparator::~PriorityCloudComparator() {

};
