// implementation of mps

#include "maximum_planar_subset.h"
#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>

// constructor
MaximumPlanarSubset::MaximumPlanarSubset() {}

// track used chords for maximum solution
set<int> MaximumPlanarSubset::track_chords(int start, int end, vector<vector<int>> &count_table, vector<int> &chords) {
  // recursive boundary
  if (start == end) {
    set<int> empty;
    return empty;
  }

  //cout << start << " " << end << endl;

  if (count_table[start][end] == count_table[start][end-1]) {
    // case 1: chord [?, end] not included
    return track_chords(start, end-1, count_table, chords);
  } else {
    int c = chords[end];
    // case 2: chord [?, end] included
    if (c == start) {
      set<int> sub_chords = track_chords(start+1, end-1, count_table, chords);
      sub_chords.insert(c);
      return sub_chords;
    } else {
      set<int> subchords1 = track_chords(start, c-1, count_table, chords);
      set<int> subchords2 = track_chords(c+1, end, count_table, chords);
      set<int> subchords;
      set_union(
        subchords1.begin(), subchords1.end(),
	subchords2.begin(), subchords2.end(),
	inserter(subchords, subchords.begin())
      );
      subchords.insert(c);
      return subchords;
    }
  }
}

// mps
tuple<int, set<int>> MaximumPlanarSubset::find_mps(int n, vector<int> chords) {
  // initialize solution table
  vector<vector<int>> maximum_count(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    maximum_count[i][i] = 0;
  }
  //cout << "initialization complete" << endl;

  // fill table
  // for every length, starting from 1
  for (int planar_length = 1; planar_length < n; planar_length++) {
    // speed observation
    //cout << planar_length << endl;

    // for all starting point
    for (int start = 0; start < n - planar_length; start++) {
      int end = start + planar_length;

      // solutions of previous subproblem
      int prev_count = maximum_count[start][end-1];

      // check chord [c, end]
      int c = chords[end];
      int num_of_chords = 0;
      if (c == start) {
        num_of_chords = 1 + maximum_count[start+1][end-1];
      } else if ( c > start && c < end) {
        num_of_chords = 1 + maximum_count[start][c-1] + maximum_count[c+1][end];
      }
      
      if (num_of_chords > prev_count) {
        maximum_count[start][end] = num_of_chords;
      } else {
        maximum_count[start][end] = prev_count;
      }
    }
  }

  //cout << "solution table completed" << endl;

  /*
  // print solution table
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < j; i++) {
      cout << maximum_count[i][j] << " ";
    }
    cout << endl;
  }
  */

  // find chords used in maximum solution
  set<int> maximum_chords = track_chords(0, n-1, maximum_count, chords);

  //cout << "chords tracking completed" << endl;

  return make_tuple(maximum_count[0][n-1], maximum_chords);
}
