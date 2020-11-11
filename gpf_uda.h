#ifndef SAMPLES_UDA_H
#define SAMPLES_UDA_H

#include <impala_udf/udf.h>

using namespace impala_udf;

void FirstInit(FunctionContext* context, StringVal* val);
void FirstUpdate(FunctionContext* context, const StringVal& input, StringVal* val);
void FirstMerge(FunctionContext* context, const StringVal& src, StringVal* dst);
StringVal FirstSerialize(FunctionContext* context, const StringVal& val);
StringVal FirstFinalize(FunctionContext* context, const StringVal& val);

void OrInit(FunctionContext* context, BooleanVal* val);
void OrUpdate(FunctionContext* context, const BooleanVal& input, BooleanVal* val);
void OrMerge(FunctionContext* context, const BooleanVal& src, BooleanVal* dst);
BooleanVal OrFinalize(FunctionContext* context, const BooleanVal& val);


void BitOrInit(FunctionContext* context, BigIntVal* val);
void BitOrUpdate(FunctionContext* context, const BigIntVal& input, BigIntVal* val);
void BitOrMerge(FunctionContext* context, const BigIntVal& src, BigIntVal* dst);
BigIntVal BitOrFinalize(FunctionContext* context, const BigIntVal& val);

void OrIntInit(FunctionContext* context, BooleanVal* val);
void OrIntUpdate(FunctionContext* context, const IntVal& input, BooleanVal* val);
void OrIntMerge(FunctionContext* context, const BooleanVal& src, BooleanVal* dst);
BooleanVal OrIntFinalize(FunctionContext* context, const BooleanVal& val);

#endif
