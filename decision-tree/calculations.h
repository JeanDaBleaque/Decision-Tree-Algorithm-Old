#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <iostream>
using namespace std;
void getData();
typedef class Node{
public:
    char perm;
    int line, lline, rline = 0;
    float exp_coordinate;
    int exp_axis;
    float **coordinates;
    int *colors;
    float **left_coordinates;
    int *left_colors;
    float **right_coordinates;
    int *right_colors;
    Node *pre_Node;
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
    void refreshCoords() {
        left_coordinates = new float*[2];
        right_coordinates = new float*[2];
        for (int i=0;i<2;i++) {
            left_coordinates[i] = new float[lline];
            right_coordinates[i] = new float[rline];
        }
        left_colors = new int[lline];
        right_colors = new int[rline];
    }
}Node, *ptr_Node;

#endif // CALCULATIONS_H
