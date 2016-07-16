// file: quat2eul.cpp, style: indent -kr -ci2 -cli2 -i2 -l80 -nut <file>
//
// License http://opensource.org/licenses/BSD-3-Clause
// Copyright (c) 2016, ItsmeJulian (github.com/ItsmeJulian)
// All rights reserved.
//
// Takes quaternion (imaginary or full) and converts it to Euler angles
// supported sequence: xyz, zyx
//
// Date          Author      	 		Notes
// 12/07/2016    Julian     				Initial release
//
// Source https://scholar.google.de/scholar?cluster=3204262265835591787
//        http://de.mathworks.com/help/robotics/ref/quat2eul.html
//
// TODO verify other sequences from Fullers spincalc
//
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// user output
void printInfo(){
  printf("$ ./quat2eul <arg1-5> converts quaternion to euler-angle sequence.\n");
  // printf(" arg1: xyz, yzx, zxy, xzy, yxz, zyx rotation sequence (J. Fuller SpinCalc)\n");
  printf(" arg1: rotation sequence (Matlab analog)\n");
  printf(" arg2: q1\n");
  printf(" arg3: q2\n");
  printf(" arg4: q3\n");
  printf("[arg5: q0 (largeq)]\n");
  printf("for example $ ./quat2eul zyx 0 0 0.7071\n");
  printf("convention: i-axis has psi, j-axis has theta, k-axis has phi\n");
  printf(" psi is always the first angle, then theta and lastly phi\n");
  printf(" the rotation is a right-handed helix\n");
  printf(" R(psi,theta,phi) = R_k(phi) R_j(theta) R_i(psi)\n");
}

// quaternation to euler, from John Fullers SpinCalc Matlab-Function
void quat2eul(string seq, double* q){
  double psi = 0;
  double theta = 0;
  double phi = 0;

  // if (seq.compare("xyz") == 0) {
  //   psi=atan2(2*(q[0] *q[3] -q[1] *q[2] ),(q[3] *q[3] -q[0] *q[0] -q[1] *q[1] +q[2] *q[2] ));
  //   theta=asin(2*(q[0] *q[2] +q[1] *q[3] ));
  //   phi=atan2(2*(q[2] *q[3] -q[0] *q[1] ),(q[3] *q[3] +q[0] *q[0] -q[1] *q[1] -q[2] *q[2] ));
  // } else if (seq.compare("yzx") == 0) {
  //   psi=atan2(2*(q[1] *q[3] -q[0] *q[2] ),(q[3] *q[3] +q[0] *q[0] -q[1] *q[1] -q[2] *q[2] ));
  //   theta=asin(2*(q[0] *q[1] +q[2] *q[3] ));
  //   phi=atan2(2*(q[0] *q[3] -q[2] *q[1] ),(q[3] *q[3] -q[0] *q[0] +q[1] *q[1] -q[2] *q[2] ));
  // } else if (seq.compare("zxy") == 0) {
  //   psi=atan2(2*(q[2] *q[3] -q[0] *q[1] ),(q[3] *q[3] -q[0] *q[0] +q[1] *q[1] -q[2] *q[2] ));
  //   theta=asin(2*(q[0] *q[3] +q[1] *q[2] ));
  //   phi=atan2(2*(q[1] *q[3] -q[2] *q[0]),(q[3] *q[3] -q[0] *q[0] -q[1] *q[1] +q[2] *q[2] ));
  // } else if (seq.compare("xzy") == 0) {
  //   psi=atan2(2*(q[0] *q[3] +q[1] *q[2] ),(q[3] *q[3] -q[0] *q[0] +q[1] *q[1] -q[2] *q[2] ));
  //   theta=asin(2*(q[2] *q[3] -q[0] *q[1] ));
  //   phi=atan2(2*(q[0] *q[2] +q[1] *q[3] ),(q[3] *q[3] +q[0] *q[0] -q[1] *q[1] -q[2] *q[2] ));
  // } else if (seq.compare("yxz") == 0) {
  //   psi=atan2(2*(q[0] *q[2] +q[1] *q[3] ),(q[3] *q[3] -q[0] *q[0] -q[1] *q[1] +q[2] *q[2] ));
  //   theta=asin(2*(q[0] *q[3] -q[1] *q[2] ));
  //   phi=atan2(2*(q[0] *q[1] +q[2] *q[3] ),(q[3] *q[3] -q[0] *q[0] +q[1] *q[1] -q[2] *q[2] ));
  if (seq.compare("zyx") == 0) {
    // psi=atan2(2*(q[0] *q[1] +q[2] *q[3] ),(q[3] *q[3] +q[0] *q[0] -q[1] *q[1] -q[2] *q[2] ));
    // theta=asin(2*(q[1] *q[3] -q[0] *q[2] ));
    // phi=atan2(2*(q[0] *q[3] +q[2] *q[1] ),(q[3] *q[3] -q[0] *q[0] -q[1] *q[1] +q[2] *q[2] ));
    // matlab way:
    psi = atan2( 2.*(q[1]*q[2] + q[0]*q[3]) , q[0]*q[0] + q[1]*q[1]- q[2]*q[2] - q[3]*q[3]);
    theta = asin( 2.*( - q[1]*q[3] + q[0]*q[2]));
    phi = atan2( 2.*(q[2]*q[3] + q[0]*q[1]) , q[0]*q[0] - q[1]*q[1]- q[2]*q[2] + q[3]*q[3]);
  } else {
    printf("meh...sequence not supported.\n");
    exit(1);
  }
  //save var. by pushing them back into the array
  q[1] = psi;
  q[2] = theta;
  q[3] = phi;
}

//rad to deg
void rad2deg(double* rads) {
  rads[1] *= (180./M_PI);
  rads[2] *= (180./M_PI);
  rads[3] *= (180./M_PI);
}

// handle I/O stream, functions compute euler-angles
int main(int argc, char **argv)
{
  if(argc <5){
    printInfo();
    exit(1);
  }

  double q [4]; //full quaternion
  string seq = "";// sequence
  stringstream s1(argv[1]);
  stringstream s2(argv[2]);
  stringstream s3(argv[3]);
  stringstream s4(argv[4]);
  s1 >> seq;
  s2 >> q[1];
  s3 >> q[2];
  s4 >> q[3];

  if (argc == 5) {// we have imaginary part of unit-q
    q[0] = sqrt(1. - q[1]*q[1] - q[2]*q[2] - q[3]*q[3]);
    printf("your q = [%f, %f, %f, %f] \n", q[0], q[1], q[2], q[3]);

  } else if (argc == 6) {// we also have real part
    stringstream s5(argv[5]);
    s5 >> q[0];
    // normalize with euklidean-norm if ||q|| != 1
    double q_norm2 = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    if(q_norm2 != 1) {
      for(int i = 0; i<4; i++) {
        q[i] /= q_norm2;
      }
      printf("unit q = [%f, %f, %f, %f] \n", q[0], q[1], q[2], q[3]);
    }
    printf("your q = [%f, %f, %f, %f] \n", q[0], q[1], q[2], q[3]);
  }

  // unit-q is known, call functions to convert to euler-angles
  quat2eul(seq,q);

  // output the euler-angles
  printf("angles psi, theta, phi for %s are in \n", seq.c_str());
  printf("rad    %f, %f, %f \n", q[1], q[2], q[3]);
  rad2deg(q);
  printf("deg    %f, %f, %f \n", q[1], q[2], q[3]);
}
// EOF
