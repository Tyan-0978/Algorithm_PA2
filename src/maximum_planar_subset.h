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
    tuple<int, set<int>> find_mps(int, vector<int>);

  private:
    set<int> track_chords(int, int, vector<vector<int>>&, vector<int>&);
};

#endif
