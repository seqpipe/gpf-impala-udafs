#include <iostream>
#include <math.h>

#include <impala_udf/uda-test-harness.h>
#include "gpf_uda.h"

using namespace impala;
using namespace impala_udf;
using namespace std;

bool TestFirst() {
    UdaTestHarness<StringVal, StringVal, StringVal> test(
        FirstInit, FirstUpdate, FirstMerge, NULL, FirstFinalize
    );

    vector<StringVal> empty;
    if(!test.Execute(empty, StringVal::null())) {
        cerr << "First empty:" << test.GetErrorMsg() << endl;
        return false;
    }

    vector<StringVal> tenValues(10, StringVal("other"));
    tenValues[0] = StringVal("first");

    if(!test.Execute(tenValues, StringVal("first"))) {
        cerr << "Ten values:" << test.GetErrorMsg() << endl;
        return false;
    }

    return true;
}

int main(int argc, char** argv) {
  bool passed = true;
  passed &= TestFirst();
  cerr << (passed ? "Tests passed." : "Tests failed.") << endl;
  return 0;
}
