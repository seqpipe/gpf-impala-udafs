#include "gpf_uda.h"
#include <assert.h>
#include <sstream>

using namespace impala_udf;
using namespace std;

// ---------------------------------------------------------------------------
// FIRST function. Simply returns the first value found.
// ---------------------------------------------------------------------------
void FirstInit(FunctionContext* context, StringVal* val) {
    val->is_null = true;
}

void FirstUpdate(FunctionContext* context, const StringVal& str, StringVal* result) {
    if (str.is_null) return;
    if (result->is_null) {
        *result = StringVal::CopyFrom(context, str.ptr, str.len);
    }
}

void FirstMerge(FunctionContext* context, const StringVal& src, StringVal* dst) {
    if(!dst->is_null || src.is_null) {
        return;
    }
    *dst = StringVal::CopyFrom(context, src.ptr, src.len);
}

StringVal FirstFinalize(FunctionContext* context, const StringVal& val) {
    if(val.is_null) {
        return StringVal::null();
    }
    StringVal result = StringVal::CopyFrom(context, val.ptr, val.len);
    return result;
}

