#include <iostream>
#include <math.h>

#include <impala_udf/uda-test-harness.h>
#include "gpf_uda.h"

using namespace impala;
using namespace impala_udf;

bool TestFirst() {
    UdaTestHarness<StringVal, StringVal, StringVal> test(
        FirstInit, FirstUpdate, FirstMerge, NULL, FirstFinalize
    );

    std::vector<StringVal> empty;
    if(!test.Execute(empty, StringVal::null())) {
        std::cerr << "First empty:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<StringVal> tenValues(10, StringVal("other"));
    tenValues[0] = StringVal("first");

    if(!test.Execute(tenValues, StringVal("first"))) {
        std::cerr << "Ten values:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    return true;
}

bool TestOr() {
    UdaTestHarness<BooleanVal, BooleanVal, BooleanVal> test(
        OrInit, OrUpdate, OrMerge, NULL, OrFinalize
    );

    std::vector<BooleanVal> empty;
    if(!test.Execute(empty, BooleanVal(false))) {
        std::cerr << "Or empty:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BooleanVal> sample1;
    sample1.push_back(BooleanVal(false));
    sample1.push_back(BooleanVal(true));
    sample1.push_back(BooleanVal(false));
    sample1.push_back(BooleanVal(true));
    if(!test.Execute(sample1, BooleanVal(true))) {
        std::cerr << "Or sample1:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BooleanVal> sample2;
    sample2.push_back(BooleanVal(true));
    sample2.push_back(BooleanVal(false));
    sample2.push_back(BooleanVal(true));
    sample2.push_back(BooleanVal(false));

    if(!test.Execute(sample2, BooleanVal(true))) {
        std::cerr << "Or sample2:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BooleanVal> allTrue(10, BooleanVal(true));
    if(!test.Execute(allTrue, BooleanVal(true))) {
        std::cerr << "Or all true:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BooleanVal> allFalse(10, BooleanVal(false));
    if(!test.Execute(allFalse, BooleanVal(false))) {
        std::cerr << "Or all false:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BooleanVal> allNull(10, BooleanVal::null());
    if(!test.Execute(allNull, BooleanVal(false))) {
        std::cerr << "Or all null:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    return true;
}

bool TestBitOr() {
    UdaTestHarness<BigIntVal, BigIntVal, BigIntVal> test(
        BitOrInit, BitOrUpdate, BitOrMerge, NULL, BitOrFinalize
    );

    std::vector<BigIntVal> empty;
    if(!test.Execute(empty, BigIntVal(false))) {
        std::cerr << "BitOr empty:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BigIntVal> sample1;
    sample1.push_back(BigIntVal(0));
    sample1.push_back(BigIntVal(1));
    sample1.push_back(BigIntVal(2));
    sample1.push_back(BigIntVal(4));
    if(!test.Execute(sample1, BigIntVal(7))) {
        std::cerr << "Or sample1:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BigIntVal> sample2;
    sample2.push_back(BigIntVal(0));
    sample2.push_back(BigIntVal(1));
    sample2.push_back(BigIntVal(0));
    sample2.push_back(BigIntVal(4));

    if(!test.Execute(sample2, BigIntVal(5))) {
        std::cerr << "BitOr sample2:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BigIntVal> sample3;
    sample3.push_back(BigIntVal(3));
    sample3.push_back(BigIntVal(1));
    sample3.push_back(BigIntVal(12));
    sample3.push_back(BigIntVal(0));

    if(!test.Execute(sample3, BigIntVal(15))) {
        std::cerr << "BitOr sample2:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    std::vector<BigIntVal> allNull(10, BigIntVal::null());
    if(!test.Execute(allNull, BigIntVal(0))) {
        std::cerr << "BitOr all null:" << test.GetErrorMsg() << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char** argv) {
  bool passed = true;
  passed &= TestFirst();
  passed &= TestOr();
  passed &= TestBitOr();
  std::cerr << (passed ? "Tests passed." : "Tests failed.") << std::endl;
  if(passed) {
      return 0;
  }
  else {
      return -1;
  }
}
