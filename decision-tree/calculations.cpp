#include <calculations.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
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
void extractCoords (Node *current_node) {
    float **left_coordinates;
    int *left_colors;
    float **right_coordinates;
    int *right_colors;
    int left_count = 0;
    int right_count = 0;
    cout << "Current Line: " << current_node->line << endl;
    left_coordinates = new float*[2];
    right_coordinates = new float*[2];
    for (int i=0;i<2;i++) {
        left_coordinates[i] = new float[current_node->line];
        right_coordinates[i] = new float[current_node->line];
    }
    left_colors = new int[current_node->line];
    right_colors = new int[current_node->line];
    /*
    for (int i=0;i<current_node->line;i++) {
        cout << current_node->coordinates[0][i] << " " << current_node->coordinates[1][i] << " " << current_node->colors[i] <<endl;
    }
    */
    for (int j=0;j<current_node->line;j++) {
        if (current_node->coordinates[current_node->exp_axis][j]<current_node->exp_coordinate) {
            cout << current_node->coordinates[0][j] << endl;
            left_coordinates[0][left_count] = current_node->coordinates[0][j];
            left_coordinates[1][left_count] = current_node->coordinates[1][j];
            left_colors[left_count] = current_node->colors[j];
            left_count++;
            //hata burada!
        }
        else {
            //cout << current_node->coordinates[0][j] << endl;
            right_coordinates[0][right_count] = current_node->coordinates[0][j];
            right_coordinates[1][right_count] = current_node->coordinates[1][j];
            right_colors[j] = current_node->colors[j];
            right_count++;
        }
    }
    current_node->lline = left_count;
    current_node->rline = right_count;
    current_node->refreshCoords();
    for (int p=0;p<current_node->lline;p++) {
        current_node->left_coordinates[0][p] = left_coordinates[0][p];
        current_node->left_coordinates[1][p] = left_coordinates[1][p];
        current_node->left_colors[p] = left_colors[p];
        cout << current_node->left_coordinates[0][p] << " " << current_node->left_coordinates[1][p] << " " << current_node->left_colors[p] << endl;
    }
    cout << "*****************************************************************************" << endl;
    for (int k=0;k<current_node->rline;k++) {
        current_node->right_coordinates[0][k] = right_coordinates[0][k];
        current_node->right_coordinates[1][k] = right_coordinates[1][k];
        current_node->right_colors[k] = right_colors[k];
        cout << current_node->right_coordinates[0][k] << " " << current_node->right_coordinates[1][k] << " " << current_node->right_colors[k] << endl;
    }
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
    char perm = 'M';
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
void infGain (Node *current_node, int *lines) {
    srand(time(nullptr));
    cout << current_node->perm << endl;
    unsigned int microseconds;
    microseconds = 1000000;
    //usleep(microseconds);
    int randAxis;
    int control = 0;
    float randCoords;
    float *PrandCoords;
    PrandCoords = &randCoords;
    float infGainVar = 0;
    float curInf = 0;
    static int leftArray[3];
    static int rightArray[3];
    cout << current_node->perm << endl;
    if (current_node->perm == 'S') {
        control = 1;
    }
    for (int i=0;i<1000;i++) {
        randAxis = rand() % 2; //
        if (control == 1) {
            cout << "test" << endl;
            *PrandCoords = (((float)rand())/RAND_MAX * (float)7);
        }
        else {
            if (current_node->pre_Node->exp_axis == randAxis) {
                if (current_node->perm == 'L') {
                    *PrandCoords = (((float)rand()*5));
                }
                else if (current_node->perm == 'R') {
                    *PrandCoords = current_node->pre_Node->exp_coordinate + (((float)rand()*5));
                }
            }
            else {
                *PrandCoords = (((float)rand())/RAND_MAX * (float)7);
            }
        }
        for (int j=0;j<*lines;j++) {
            if (randAxis == 0) {
                if (current_node->coordinates[0][j]<randCoords) {
                    if (current_node->colors[j] == 1) {
                        leftArray[0]++;
                    }
                    else if (current_node->colors[j] == 2) {
                        leftArray[1]++;
                    }
                    else if (current_node->colors[j] == 3) {
                        leftArray[2]++;
                    }
                }
                else {
                    if (current_node->colors[j] == 1) {
                        rightArray[0]++;
                    }
                    else if (current_node->colors[j] == 2) {
                        rightArray[1]++;
                    }
                    else if (current_node->colors[j] == 3) {
                        rightArray[2]++;
                    }
                }
            }
            else if (randAxis == 1) {
                if (current_node->coordinates[1][j]<randCoords) {
                    if (current_node->colors[j] == 1) {
                        leftArray[0]++;
                    }
                    else if (current_node->colors[j] == 2) {
                        leftArray[1]++;
                    }
                    else if (current_node->colors[j] == 3) {
                        leftArray[2]++;
                    }
                }
                else {
                    if (current_node->colors[j] == 1) {
                        rightArray[0]++;
                    }
                    else if (current_node->colors[j] == 2) {
                        rightArray[1]++;
                    }
                    else if (current_node->colors[j] == 3) {
                        rightArray[2]++;
                    }
                }
            }
        }
        curInf = calculation(&leftArray[0], &leftArray[1], &leftArray[2], &rightArray[0], &rightArray[1], &rightArray[2], lines);
        if (curInf>infGainVar) {
            infGainVar = curInf;
            current_node->I = curInf;
            current_node->exp_axis = randAxis;
            current_node->exp_coordinate = randCoords;
        }
        for (int k=0;k<=2;k++) {
            leftArray[k] = 0;
            rightArray[k] = 0;
        }
    }
    cout << "Selected infGainVar = " << current_node->I << endl;
    cout << "Selected axis = " << current_node->exp_axis << endl;
    cout << "Selected coordinates = " << current_node->exp_coordinate << endl;
}
int Node::extractData(Node *start_Node, int *lines, float **coords, int *colors, char *perm) {
    ptr_Node cur_Node;
    int newLine = 0;
    char lPerm;
    char rPerm;
    if (start_Node == nullptr) {
        cur_Node = new Node;
        cur_Node->depth = 0;
        start_Node = cur_Node;
        cur_Node->perm = 'S';
        cur_Node->pre_Node = nullptr;
        cur_Node->line = *lines;
        cur_Node->refreshNode();
        for (int i=0;i<cur_Node->line;i++) {
            cout << "test" << endl;
            cur_Node->coordinates[0][i] = coords[0][i];
            cout << i << ". " << cur_Node->coordinates[0][i] << endl;
            cur_Node->coordinates[1][i] = coords[1][i];
            cur_Node->colors[i] = colors[i];
        }
    }
    else {
        cur_Node = new Node;
        if (*perm == 'L') {
            start_Node->left_Node = cur_Node;
            cur_Node->perm = 'L';
            cur_Node->line = *lines;
            cur_Node->pre_Node = start_Node;
            cur_Node->refreshNode();
            cur_Node->coordinates = cur_Node->pre_Node->left_coordinates;
            cur_Node->colors = cur_Node->pre_Node->left_colors;
            cur_Node->depth = cur_Node->pre_Node->depth + 1;
            for (int i=0;i<cur_Node->line;i++) {
                cout << cur_Node->coordinates[0][i] << " " << cur_Node->coordinates[1][i] << " " << cur_Node->colors[i] << endl;
            }
        }
        else if (*perm == 'R') {
            start_Node->right_Node = cur_Node;
            cur_Node->perm = 'R';
            cur_Node->line = *lines;
            cur_Node->pre_Node = start_Node;
            cur_Node->refreshNode();
            cur_Node->coordinates = cur_Node->pre_Node->right_coordinates;
            cur_Node->colors = cur_Node->pre_Node->right_colors;
            cur_Node->depth = cur_Node->pre_Node->depth + 1;
        }
    }
    if (cur_Node) {
        cout << "Current Node created!" << endl;
        cout << "Total lines = " << *lines << endl;
        if (cur_Node->depth <= 2) { //cur_Node->perm == 'S'
            cout << "Current Side: " << cur_Node->perm << ". Current Depth = " << cur_Node->depth << endl;
            //cout << "********************************************************************************" << endl;
            infGain(cur_Node, &cur_Node->line);
            start_Node = cur_Node;
            extractCoords(cur_Node);
            lPerm = 'L';
            extractData(start_Node, &cur_Node->lline, cur_Node->left_coordinates, cur_Node->left_colors, &lPerm);
            //rPerm = 'R';
            //extractData(start_Node, &cur_Node->lline, cur_Node->left_coordinates, cur_Node->left_colors, &rPerm);
        }
    }
    else {
        cout << "Memory allocation failed!" << endl;
    }
}
