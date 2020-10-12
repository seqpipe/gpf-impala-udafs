#ifndef SAMPLES_UDA_H
#define SAMPLES_UDA_H

#include <impala_udf/udf.h>

using namespace impala_udf;

void FirstInit(FunctionContext* context, StringVal* val);
void FirstUpdate(FunctionContext* context, const StringVal& input, StringVal* val);
void FirstMerge(FunctionContext* context, const StringVal& src, StringVal* dst);
StringVal FirstFinalize(FunctionContext* context, const StringVal& val);


#endif
