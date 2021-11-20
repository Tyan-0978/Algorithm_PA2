// implementation of mps

#include "maximum_planar_subset.h"
#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>

// constructor
MaximumPlanarSubset::MaximumPlanarSubset() {}

// mps
tuple<int, set<vector<int>>> MaximumPlanarSubset::find_mps(int n, vector<int> chords) {
  // initialize solution table
  vector<vector<int>> maximum_count(n, vector<int>(n));
  vector<vector<set<vector<int>>>> maximum_chords(n, vector<set<vector<int>>>(n));
  for (int i = 0; i < n; i++) {
    maximum_count[i][i] = 0;
    set<vector<int>> empty;
    maximum_chords[i][i] = empty;
  }
  //cout << "initialization complete" << endl;

  // fill table
  // for every length, starting from 1
  for (int planar_length = 1; planar_length < n; planar_length++) {
    cout << planar_length << endl;
    // for all starting point
    for (int start = 0; start < n - planar_length; start++) {
      int end = start + planar_length;

      // assign solutions of previous subproblem
      int max = maximum_count[start][end-1];
      set<vector<int>> chords_in_subset = maximum_chords[start][end-1];

      // check chord [start, end]
      if (chords[start] == end) {
        vector<int> C = {start, end};

        if (planar_length == 1) {
	  max = 1;
	  chords_in_subset.insert(C);
	} else {
	  int num_of_chords = 1 + maximum_count[start+1][end-1];
	  if (num_of_chords > max) {
	    max = num_of_chords;
	    chords_in_subset = maximum_chords[start+1][end-1];
	    chords_in_subset.insert(C);
	  }
	}
      }

      // check chord [mid,end] for mid = [start+1, end]
      for (int mid = start + 1; mid < end; mid++) {
	if (chords[mid] == end) { // chord [mid,end] is one of the given chords
          vector<int> c = {mid, end};
	  int n_of_chords = 1 + maximum_count[start][mid-1] + maximum_count[mid+1][end];
	  //cout << n_of_chords << endl;

	  if (n_of_chords > max) {
	    max = n_of_chords;
	    chords_in_subset.clear();
	    set_union(
	      maximum_chords[start][mid-1].begin(),
	      maximum_chords[start][mid-1].end(),
	      maximum_chords[mid+1][end].begin(),
	      maximum_chords[mid+1][end].end(),
	      inserter(chords_in_subset, chords_in_subset.begin())
	    );
	    chords_in_subset.insert(c);
	  }
	}
      }

      maximum_count[start][end] = max;
      maximum_chords[start][end] = chords_in_subset;
    }
  }

  /*
  // print solution table
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < j; i++) {
      cout << maximum_count[i][j] << " ";
    }
    cout << endl;
  }
  */

  return make_tuple(maximum_count[0][n-1], maximum_chords[0][n-1]);
}
