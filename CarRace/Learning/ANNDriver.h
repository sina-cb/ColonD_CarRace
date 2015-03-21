#ifndef ANN_DRIVER_H
#define ANN_DRIVER_H

#include "Driver.h"
#include "fann.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

class ANNDriver : public Driver{

public:
    ANNDriver(Car* car, bool collect, bool load);
    ~ANNDriver();
    void drive();
    void Restart();
    char* Name(){return "ANN Driver";}
    void CollectData(bool collect){collect_data = collect;}
    void create_ann(char* file_path);
    void load_ann();
    void toggle_train();

private:

    ofstream myfile;
    ostringstream mystring;
    bool collect_data;
    int data_count;

    struct fann *ann;

    static const unsigned int num_layers = 5;
    static const unsigned int num_input = 5;
    static const unsigned int num_output = 1;
    static const unsigned int num_neurons_hidden = 10;

    static const float desired_error = 0.01;
    static const float momentum = 0.2;
    static const float learning_rate = 0.1;
    static const unsigned int max_epochs = 10000;
    static const unsigned int epochs_between_reports = 100;

    static const double MIN_CHANGE_IN_PREDICTION = 0.15;

};

#endif
