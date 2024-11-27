#include <stdlib.h>
#include <stdio.h>
#include <jni.h>
#include "tdoa.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jint JNICALL Java_com_xlmf_feature_location_calculation_service_impl_CalServiceImpl_tdoaCalc
        (JNIEnv *env, jobject obj, jobjectArray bsVec, jdoubleArray timeVec, jint numBs, jobject ms);

#ifdef __cplusplus
}
#endif
