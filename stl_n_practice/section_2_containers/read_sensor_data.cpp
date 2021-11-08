//Task read sensor data from file and count the occurances of every value

//Seems good to use a map for this
//Read file, stream into string, and count using map

#include <iostream>
#include <fstream>
#include <map>
#include <string> //to access getline function

using namespace std;

int main(int argc, char const *argv[])
{
    map<string, int> sensor_readings;

    ifstream in_file("sensor_data.txt");
    string line;

    if (in_file.is_open())
    {
        while (!in_file.eof())
        {
            getline(in_file, line);
            sensor_readings[line]++;
        }
    }

    for (auto &reading : sensor_readings)
    {
        cout << "Sensor reading " << reading.first << " occured " << reading.second << " times." << endl;
    }
    return 0;
}
