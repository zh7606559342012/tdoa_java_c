#include "javatoc.h"
#include <jni.h>
#include "tdoa.h"

JNIEXPORT jint

JNICALL Java_com_xlmf_feature_location_calculation_service_impl_CalServiceImpl_tdoaCalc
        (JNIEnv *env, jobject obj, jobjectArray bsVec, jdoubleArray timeVec, jint numBs, jobject ms)
{
    FILE *logFile = fopen("/home/zhenghao/test_xlmf/zh_xlmf.log", "a");
    if (logFile == NULL) {
        fprintf(stderr, "Error opening log file!\n");
        return -1; // 返回错误
    }

    tdoa_pos_t *bs_array = (tdoa_pos_t *) malloc(numBs * sizeof(tdoa_pos_t));
    tdoa_time_t *time_array = (tdoa_time_t *) malloc(numBs * sizeof(tdoa_time_t));

    for (int i = 0; i < numBs; i++) {
        jobject bs = env->GetObjectArrayElement(bsVec, i);
        jclass cls = env->GetObjectClass(bs);
        jfieldID xField = env->GetFieldID(cls, "x", "D");
        jfieldID yField = env->GetFieldID(cls, "y", "D");
        jfieldID zField = env->GetFieldID(cls, "z", "D");

        bs_array[i].x = env->GetDoubleField(bs, xField);
        bs_array[i].y = env->GetDoubleField(bs, yField);
        bs_array[i].z = env->GetDoubleField(bs, zField);
    }

    env->GetDoubleArrayRegion(timeVec, 0, numBs, time_array);

    jclass msClass = env->GetObjectClass(ms);
    jfieldID fxField = env->GetFieldID(msClass, "x", "D");
    jfieldID fyField = env->GetFieldID(msClass, "y", "D");
    jfieldID fzField = env->GetFieldID(msClass, "z", "D");

    tdoa_pos_t tmp;
    jint result = VelPos::tdoa_calc_1(bs_array, time_array, numBs, &tmp);


    env->SetDoubleField(ms, fxField, tmp.x);
    env->SetDoubleField(ms, fyField, tmp.y);
    env->SetDoubleField(ms, fzField, tmp.z);
    fprintf(logFile, "cal result is: tmp.x=%f, y=%f, z=%f\n", tmp.x, tmp.y, tmp.z);

    free(bs_array);
    free(time_array);
    fclose(logFile);

    return result;
}