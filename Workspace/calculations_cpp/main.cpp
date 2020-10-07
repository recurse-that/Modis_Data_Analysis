

#include "Executive.h"
#include "Data.h"
#include "Scene.h"
#include "MXVI.h"

// #include <gtest/gtest.h>


using namespace std;



// class ExecutiveTest : public testing::Test {
//   protected:
//     void SetUp() override {
//     }  // End SetUp
//     // void TearDown() override {
//     // }  // End TearDown
    
//     Executive _exec;
    
// };  // End ExecutiveTest class

// TEST_F(ExecutiveTest, TestFileGenerated) {
//   EXPECT_NE(_exec.test_data, nullptr);
// }


// int main (int argc, char *argv[]) {

//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS(); 
// }  // End main

int main (int argc, char *argv[]) {

  if (argc < 1) {
    std::cout << "No file given";
    return 0;
  }
  else {
    for (int i = 0; i < argc; ++i)
          cout << argv[i] << "\n";

    Executive exec;
  }
  return 0;
}