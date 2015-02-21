#include "ANNDriver.h"

using namespace std;

ANNDriver::ANNDriver(Car *car, bool collect, bool load){
    this->car = car;
    if_drive = false;

    collect_data = collect;
    data_count = 0;

    if (!collect_data && load){
        load_ann();
    }

    if (!collect_data && !load){
        create_ann("sensor.csv");
    }
}

void ANNDriver::load_ann(){

    ann = fann_create_from_file("ann.model");

}

void ANNDriver::create_ann(char *file_path){
    ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, file_path, max_epochs, epochs_between_reports, desired_error);

    fann_save(ann, "ann.model");

    //    fann_destroy(ann);
}

void ANNDriver::drive(){
    double* sensor_data = car->SensorData();
    int steering_angle = (int)(car->SteeringAngle() / car->MaxSteeringAngle());

    static double last_angle = 0;

    if (if_drive){
        car->EngineSpeed(-car->HorsePower());

        fann_type sensor_data_disc[car->SENSOR_COUNT];
        for (int i = 0; i < car->SENSOR_COUNT; i++){
            sensor_data_disc[i] = (int)sensor_data[i];
        }

        fann_type *predicted_angle;
        predicted_angle = fann_run(ann, sensor_data_disc);

        cout << "Predited value: " << predicted_angle[0] << endl;

        double diff = 0;
        if (last_angle == 0){
            last_angle = predicted_angle[0];
        }else{
            diff = last_angle - predicted_angle[0];
        }

        if (abs(diff) < MIN_CHANGE_IN_PREDICTION){
            diff = 0;
        }

        if (diff < 0){
            car->SteeringAngle(car->MaxSteeringAngle());
        }else if (diff > 0){
            car->SteeringAngle(-car->MaxSteeringAngle());
        }else{
            car->SteeringAngle(0);
        }
    }

    if (collect_data){
        for (int i = 0; i < car->SENSOR_COUNT; i++){
            if (i != car->SENSOR_COUNT - 1)
                mystring << (int) sensor_data[i] << " ";
        }
        mystring << endl;

        mystring << steering_angle * 10;
        mystring << endl;

        data_count++;

    }else{
        //        cout << "Sensor data: ";
        //        for (int i = 0; i < car->SENSOR_COUNT; i++){
        //            cout << (int) sensor_data[i] << "\t";
        //        }
        //        cout << "True value: " << steering_angle;
        //        cout << endl;
    }

}

ANNDriver::~ANNDriver(){

    if (collect_data){
        myfile.open("sensor.csv");

        myfile << data_count << " " << car->SENSOR_COUNT + 1 << " " << 1 << endl;
        myfile << mystring.str();

        myfile.close();

        create_ann("sensor.csv");
    }

}

void ANNDriver::Restart(){

}


