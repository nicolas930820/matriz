#include <chrono>
#include "graphreader.hh"
//#include "timer.hh"
#include <cassert>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
using Mat = vector<vector<int>>;

void dot (const Mat &m1, const Mat &m2, int a, int b, int &res){
  int k = m2.size();    // number of rows in m2
  int j = m1[0].size(); // number of cols in m1
  int l = m2[0].size(); // number of cols in m2

  for (int b = 0; b < l; b++) {
    for (int c = 0; c < j; c++) {
      res[a][b] += m1[a][c] * m2[c][b];
    }
  }
}

void mult0(const Mat &m1, const Mat &m2, Mat &res) {
  int i = m1.size();    // number of rows in m1
  int j = m1[0].size(); // number of cols in m1
  int k = m2.size();    // number of rows in m2
  int l = m2[0].size(); // number of cols in m2
  vector<thread> ts;
  assert(j == k);
  //ts.resize(i*j*k);
  for (int a = 0; a < i; a++) {
    //for (int b = 0; b < l; b++) {
      //mov constructor que crea el hilo directamente en ts.
      // thread t(dot,cref(m1), cref(m2), ref(a), ref(b), ref(res[a][b]));
      // t.join();
      ts.push_back(thread(dot,cref(m1), cref(m2), ref(a), ref(res)));
    }

  for (thread &t: ts){
    t.join();
  }
}


int main(int argc, char **argv) {
  chrono::high_resolution_clock::time_point timet;
  if (argc != 2) {
    cerr << "Error!!" << endl;
  }
  string fileName(argv[1]);
  Mat g = readGraph(fileName);
  Mat r;
  r.resize(g.size());
  for (int i = 0; i < g.size(); i++) {
    r[i].resize(g.size());
  }
  chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  mult0(g, g, r);
  //cout << t.elapsed() << " ns." << endl;
  chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
  timet = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  return 0;
}
