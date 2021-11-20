// main.cpp for PA2

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <tuple>
#include "maximum_planar_subset.h"

using namespace std;

int main(int arg_num, char* args[]) {
  // read input
  if (arg_num != 3) {
    cout << "argument number error" << endl;
    return 0;
  }

  ifstream input_file(args[1]);
  string size;
  input_file >> size;
  int n = stoi(size);

  // given chords
  vector<int> chords(n, 0);
  int i,j;
  while (input_file >> i >> j) {
    chords[i] = j;
  }

  input_file.close();
  //cout << "input file is read" << endl;

  // find mps
  tuple<int, set<vector<int>>> result;
  int result_num;
  set<vector<int>> result_chords;

  MaximumPlanarSubset MPS;
  result = MPS.find_mps(n, chords);
  result_num = get<0>(result);
  result_chords = get<1>(result);

  //cout << result_num << endl;

  // write output file
  ofstream output_file(args[2]);
  output_file << result_num << endl;
  set<vector<int>>::iterator itr;
  for (itr = result_chords.begin(); itr != result_chords.end(); itr++) {
    vector<int> c = *itr;
    output_file << c[0] << " " << c[1] << endl;
  }
  output_file.close();

  return 0;
}
