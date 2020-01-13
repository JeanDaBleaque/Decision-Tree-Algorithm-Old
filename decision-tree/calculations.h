#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <iostream>
using namespace std;
void getData();
typedef class Node{
public:
    char perm;
    int line = 0;
    float exp_coordinate;
    int exp_axis;
    float **coordinates;
    int *colors;
    Node *left_Node;
    Node *right_Node;
    int current_Depth = 0;
    float I;
    int LCount = 0;
    int LYellow = 0;
    int LRed = 0;
    int LGreen = 0;
    int RYellow = 0;
    int RRed = 0;
    int RGreen = 0;
    int RCount = 0;
    int extractData(Node *start_Node, int *lines, float **coords, int *colors, char *perm);
    void refreshNode() {
        coordinates = new float*[2];
        for (int i=0;i<2;i++) {
            coordinates[i] = new float[line];
        }
        colors = new int[line];
    }
}Node, *ptr_Node;

#endif // CALCULATIONS_H
