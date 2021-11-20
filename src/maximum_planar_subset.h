// header file for MaximumPlanarSubset class

#ifndef _MPS
#define _MPS

#include <vector>
#include <set>
#include <tuple>
using namespace std;

class MaximumPlanarSubset {
  public:
    MaximumPlanarSubset(); // constructor
    tuple<int, set<vector<int>>> find_mps(int, vector<int>);
};

#endif
