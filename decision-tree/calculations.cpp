#include <calculations.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
Node *Root;
Node *LNode;
Node *RNode;
void printInfo (Node *R, Node *LN, Node *RN) {
    cout << "Root Coordinates: ";
    if (R->exp_axis == 0) {
        cout << "X - ";
    }
    else if (R->exp_axis == 1) {
        cout << "Y - ";
    }
    cout << R->exp_coordinate << endl;
    cout << "Root I: " << R->I << endl;
    cout << "Left Node Coordinates: ";
    if (LN->exp_axis == 0) {
        cout << "X - ";
    }
    else if (LN->exp_axis == 1) {
        cout << "Y - ";
    }
    cout << LN->exp_coordinate << endl;
    cout << "Left Node I: " << LN->I << endl;
    cout << "Right Node Coordinates: ";
    if (RN->exp_axis == 0) {
        cout << "X - ";
    }
    else if (RN->exp_axis == 1) {
        cout << "Y - ";
    }
    cout << RN->exp_coordinate << endl;
    cout << "Right Node I: " << RN->I << endl;
}
void extractCoords () {

}
float calculation (int *LYellow, int *LRed, int *LGreen, int *RYellow, int *RRed, int *RGreen, int *lines) {
    float sYellow = (float)(*LYellow+*RYellow)/(*lines); //Summition of Yellow Apples
    float sRed = (float)(*LRed+*RRed)/(*lines); //Summition of Red Apples
    float sGreen = (float)(*LGreen+*RGreen)/(*lines); //Summition of Green Apples
    float dlYellow = (float)(*LYellow)/(*lines); //Division of Left Yellow Apples
    float dlRed = (float)(*LRed)/(*lines); //Division of Left Red Apples
    float dlGreen = (float)(*LGreen)/(*lines); //Division of Left Green Apples
    float drYellow = (float)(*RYellow)/(*lines); //Division of Right Yellow Apples
    float drRed = (float)(*RRed)/(*lines); //Division of Right Red Apples
    float drGreen = (float)(*RGreen)/(*lines); //Division of Right Green Apples
    float HS, HSL, HSR, I;
    if (sYellow == (float)0) {
        sYellow = 1;
    }
    if (sRed == (float)0) {
        sRed = 1;
    }
    if (sGreen == (float)0) {
        sGreen = 1;
    }
    if (dlYellow == (float)0) {
        dlYellow = 1;
    }
    if (dlRed == (float)0) {
        dlRed = 1;
    }
    if (dlGreen == (float)0) {
        dlGreen = 1;
    }
    if (drYellow == (float)0) {
        drYellow = 1;
    }
    if (drRed == (float)0) {
        drRed = 1;
    }
    if (drGreen == (float)0) {
        drGreen = 1;
    }
    HS = -1*(sYellow*log2f(sYellow) + sRed*log2f(sRed) + sGreen*log2f(sGreen));
    HSL = (dlYellow*log2f(dlYellow) + dlRed*log2f(dlRed) + dlGreen*log2f(dlGreen));
    HSR = (drYellow*log2f(drYellow) + drRed*log2f(drRed) + drGreen*log2f(drGreen));
    cout.flush();
    I = HS + ((float)(*LYellow+*LRed+*LGreen)/(*lines))*HSL + ((float)(*RYellow+*RRed+*RGreen)/(*lines))*HSR;
    cout << "Left Side - Colors [Y] = " << *LYellow << " Colors [R] " << *LRed << " Colors [G] " << *LGreen << endl;
    cout << "Right Side - Colors [Y] = " << *RYellow << " Colors [R] " << *RRed << " Colors [G] " << *RGreen << endl;
    cout << "HS = " << HS << endl;
    cout << "HSL = " << HSL << endl;
    cout << "HSR = " << HSR << endl;
    cout << "I = " << I << endl;
    return I;
}
void getData () {
    char perm = 'R';
    ifstream r_file;
    r_file.open("data.txt");
    int lines = 0;
    string ch;
    while (getline(r_file, ch)) {
        lines++;
    }
    int arr[lines];
    float **array = new float*[2];
    for (int i=0;i<2;i++) {
        array[i] = new float[lines];
    }
    cout << lines << endl;
    r_file.close();
    r_file.open("data.txt");
    cout << "[X] [Y] [C]" << endl;
    for (int i=0;i<lines;i++) {
        r_file >> array[0][i];
        r_file >> array[1][i];
        r_file >> arr[i];
        cout << array[0][i] << " " << array[1][i] << " " << arr[i] << endl;
    }
    r_file.close();
    ptr_Node goNode = nullptr;
    goNode->extractData(goNode, &lines, array, arr, &perm);
}
//Infgain here!
int Node::extractData(Node *start_Node, int *lines, float **coords, int *colors, char *perm) {
    ptr_Node cur_Node;
    int newLine = 0;
    if (start_Node == nullptr) {
        cur_Node = new Node;
        cur_Node->left_Node = new Node;
        cur_Node->right_Node = new Node;
        cur_Node->current_Depth = 0;
    }
    else {
        cur_Node = start_Node->left_Node;
        cur_Node->current_Depth = start_Node->current_Depth + 1;
        cout << cur_Node << endl;
        cout << start_Node->left_Node << endl;
        usleep(100000);

    }
    float *randCoord;
    int *randAxis;
    if (cur_Node) {
        cout << "cur_Node created!" << endl;
        cout << *lines << endl;
        cur_Node->line = *lines;
        cout << cur_Node->line << endl;
        cout << "Test!" << endl;
        cur_Node->refreshNode();
        cur_Node->perm = *perm;
        if (cur_Node->current_Depth < 2) {
            cout << cur_Node->perm << " " << cur_Node->current_Depth << endl;
            infGain(colors, lines, &cur_Node->exp_coordinate, &cur_Node->exp_axis, &cur_Node->perm, start_Node, coords, colors, cur_Node);
        }
        cout << "Left " << cur_Node->LCount << endl;
        cout << "Right " << cur_Node->RCount << endl;
        if (start_Node == nullptr) {
            for (int i=0;i<*lines;i++) {
                cur_Node->coordinates[0][i] = coords[0][i];
                cur_Node->coordinates[1][i] = coords[1][i];
                cur_Node->colors[i] = colors[i];
                newLine++;
            }
        }
        else {
            if (start_Node->exp_axis == 0) {
                if (cur_Node->exp_axis == 0) {//X-X
                    if (cur_Node->exp_coordinate >= start_Node->exp_coordinate) {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->exp_coordinate < start_Node->coordinates[start_Node->exp_axis][i]) {
                                cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                                cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                                cur_Node->colors[i] = start_Node->colors[i];
                                newLine++;
                            }
                        }
                    }
                    else {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->exp_coordinate > start_Node->coordinates[start_Node->exp_axis][i]) {
                                cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                                cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                                cur_Node->colors[i] = start_Node->colors[i];
                                newLine++;
                            }
                        }
                    }
                }
                else {//X-Y
                    if (cur_Node->perm == 'L') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] < start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                    else if (cur_Node->perm == 'R') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] > start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                }
            }
            else if (start_Node->exp_axis == 1) { //2
                if (cur_Node->exp_axis == 0) {//Y-X
                    if (cur_Node->perm == 'L') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] < start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                    else if (cur_Node->perm == 'R') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] > start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                }
                else if (cur_Node->exp_axis == 1) {//Y-Y
                    if (cur_Node->perm == 'L') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] < start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                    else if (cur_Node->perm == 'R') {
                        for (int i=0;i<*lines;i++) {
                            if (start_Node->coordinates[start_Node->exp_axis][i] > start_Node->exp_coordinate) {
                             cur_Node->coordinates[0][i] = start_Node->coordinates[0][i];
                             cur_Node->coordinates[1][i] = start_Node->coordinates[1][i];
                             cur_Node->colors[i] = start_Node->colors[i];
                             newLine++;
                            }
                        }
                    }
                }
            }
        }
        start_Node = cur_Node;
        if (cur_Node->current_Depth < 2) {
            *perm = 'L';
            cur_Node->extractData(start_Node, &cur_Node->LCount, coords, colors, perm);
            *perm = 'R';
            cur_Node->extractData(start_Node, &cur_Node->RCount, coords, colors, perm);
        }
        if (cur_Node->current_Depth == 0 && cur_Node->perm == 'R') {
            Root = cur_Node;
        }
        else if (cur_Node->current_Depth == 1 && cur_Node->perm == 'L') {
            LNode = cur_Node;
        }
        else if (cur_Node->current_Depth == 1 && cur_Node->perm == 'R') {
            RNode = cur_Node;
        }
    }
    else {
        cout << "Bad memory allocation." << endl;
    }
    if (cur_Node->current_Depth == 0) {
        printInfo(Root, LNode, RNode);
    }
    cout << "Finished" << endl;
}
