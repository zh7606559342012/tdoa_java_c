#include "tdoa.h"
#include <jni.h>
#include <itpp/itbase.h>
#include <itpp/comm/multilateration.h>

using namespace itpp;

JNIEXPORT jint

JNICALL Java_com_xlmf_feature_location_calculation_service_impl_CalServiceImpl_tdoaCalc
        (JNIEnv *env, jobject obj, jobjectArray bsVec, jdoubleArray timeVec, jint numBs, jobject ms)
{
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
/*
    jclass msClass = env->GetObjectClass(ms);
    jfieldID fxField = env->GetFieldID(msClass, "x", "D");
    jfieldID fyField = env->GetFieldID(msClass, "y", "D");
    jfieldID fzField = env->GetFieldID(msClass, "z", "D");
*/
    jint result = tdoa_calc(bs_array, time_array, numBs, env, ms);

/*
    env->SetDoubleField(ms, fxField, 1.0);
    env->SetDoubleField(ms, fyField, 2.0);
    env->SetDoubleField(ms, fzField, 3.0);
*/
    free(bs_array);
    free(time_array);

    return result;
}

int tdoa_calc(tdoa_pos_t *bs_vec, tdoa_time_t *time_vec, int num_bs, JNIEnv *env, jobject ms)
{
    int i, j;
    bool ret;

    if (num_bs < 4 || num_bs > 10) {
        return -1;
    }

    Multilateration multi;
    bvec method(num_bs - 1);
    method.ones();

    mat bs_pos(3, num_bs);
    vec measures(num_bs);

    for (i = 0; i < num_bs; i++) {
        measures[i] = time_vec[i] * LIGHT_SPEED;
        for (j = 0; j < 3; j++) {
            bs_pos(i, j) = bs_vec[i].xyz[j];
        }
    }
    multi.setup(method, bs_pos);

    vec ms_pos;
    ret = multi.get_pos(ms_pos, measures);
    if (!ret) {
        return -1;
    }
/*
    ms->x = ms_pos.get(0);
    ms->y = ms_pos.get(1);
    ms->z = ms_pos.get(2);
*/
    jclass msClass = env->GetObjectClass(ms);
    jfieldID fxField = env->GetFieldID(msClass, "x", "D");
    jfieldID fyField = env->GetFieldID(msClass, "y", "D");
    jfieldID fzField = env->GetFieldID(msClass, "z", "D");
    env->SetDoubleField(ms, fxField, ms_pos.get(0));
    env->SetDoubleField(ms, fyField, ms_pos.get(1));
    env->SetDoubleField(ms, fzField, ms_pos.get(2));
/*
    ms->x = 1.0;
    ms->y = 2.0;
    ms->z = 3.0;
*/
    return 0;
}
