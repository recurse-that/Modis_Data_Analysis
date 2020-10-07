
#ifndef TEST_H
#define TEST_H

#include "Scene.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
class test {
public:
    test();

    void write_scene_file_tests(string path);
    void write_scene_tests();
    void write_MXVI_tests();

    string get_test_scene_file_name(int i) { return test_scene_file_names[i]; }
    Scene get_test_scene(int i) { return test_scenes[i]; }
    MXVI get_test_MXVI(int i) { return test_MXVIs[i]; }

private:
    string *test_names;
    string *test_scene_file_names;
    Scene *test_scenes;
    MXVI *test_MXVIs;

    int start_year = 2002;
    int end_year = 2019;
    int num_scenes = 2;
    int size = 100;

};
#endif