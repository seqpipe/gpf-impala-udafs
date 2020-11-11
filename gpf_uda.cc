#include "gpf_uda.h"
#include <assert.h>
#include <sstream>

using namespace impala_udf;

// ---------------------------------------------------------------------------
// FIRST function. Simply returns the first value found.
// ---------------------------------------------------------------------------
void FirstInit(FunctionContext* context, StringVal* val) {
    val->is_null = true;
}

void FirstUpdate(FunctionContext* context, const StringVal& str, StringVal* result) {
    if (str.is_null) return;
    if (result->is_null) {
        uint8_t *copy = context->Allocate(str.len);
        memcpy(copy, str.ptr, str.len);
        *result = StringVal(copy, str.len);
    }
}

void FirstMerge(FunctionContext* context, const StringVal& src, StringVal* dst) {
    if(!dst->is_null || src.is_null) {
        return;
    }
    uint8_t *copy = context->Allocate(src.len);
    memcpy(copy, src.ptr, src.len);
    *dst = StringVal(copy, src.len);
}

StringVal FirstFinalize(FunctionContext* context, const StringVal& val) {
    if(val.is_null) {
        return StringVal::null();
    }
    StringVal result = StringVal::CopyFrom(context, val.ptr, val.len);
    context->Free(val.ptr);
    return result;
}


// ---------------------------------------------------------------------------
// OR function. Applies OR to aggregated BOOLEAN columns
// ---------------------------------------------------------------------------
void OrInit(FunctionContext* context, BooleanVal* val) {
    val->is_null = false;
    val->val = false;
}

void OrUpdate(FunctionContext* context, const BooleanVal& input, BooleanVal* val) {
    if(input.is_null) {
        return;
    }

    val->val = val->val || input.val;
}

void OrMerge(FunctionContext* context, const BooleanVal& src, BooleanVal* dst) {
    if(src.is_null) {
        return;
    }
    dst->val = dst->val || src.val;
}

BooleanVal OrFinalize(FunctionContext* context, const BooleanVal& val) {
    return val;
}


// ---------------------------------------------------------------------------
// BITOR function. Applies bitwise OR to aggregated integer columns
// ---------------------------------------------------------------------------

void BitOrInit(FunctionContext* context, BigIntVal* val) {
    val->is_null = false;
    val->val = 0;
}

void BitOrUpdate(FunctionContext* context, const BigIntVal& input, BigIntVal* val) {
    if(input.is_null) {
        return;
    }

    val->val = val->val | input.val;
}

void BitOrMerge(FunctionContext* context, const BigIntVal& src, BigIntVal* dst) {
    if(src.is_null) {
        return;
    }

    dst->val = dst->val | src.val;

}

BigIntVal BitOrFinalize(FunctionContext* context, const BigIntVal& val) {
    return val;
}

// ---------------------------------------------------------------------------
// OR function. Applies OR to aggregated integer columns
// ---------------------------------------------------------------------------
//
void OrIntInit(FunctionContext* context, BooleanVal* val) {
    val->is_null = false;
    val->val = false;
}

void OrIntUpdate(FunctionContext* context, const IntVal& input, BooleanVal* val) {
    if (input.is_null) {
        return;
    }

    val->val = val->val || input.val;
}

void OrIntMerge(FunctionContext* context, const BooleanVal& src, BooleanVal* dst) {
    if(src.is_null) {
        return;
    }

    dst->val = dst->val || src.val;
}

BooleanVal OrIntFinalize(FunctionContext* context, const BooleanVal& val) {
    return val;
}
