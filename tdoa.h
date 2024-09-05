#include <stdlib.h>
#include <stdio.h>
#include <jni.h>

#define LIGHT_SPEED 299792458.0 /* meter per second */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tdoa_pos_s {
    union {
        struct {
            double x;
            double y;
            double z;
        };
        double xyz[3];
    };
} tdoa_pos_t;

typedef double tdoa_time_t; /* second */

JNIEXPORT jint JNICALL Java_com_xlmf_feature_location_calculation_service_impl_CalServiceImpl_tdoaCalc
        (JNIEnv *env, jobject obj, jobjectArray bsVec, jdoubleArray timeVec, jint numBs, jobject ms);

int tdoa_calc_1(tdoa_pos_t *bs_vec, tdoa_time_t *time_vec, int num_bs, tdoa_pos_t *ms);
int tdoa_calc(tdoa_pos_t *bs_vec, tdoa_time_t *time_vec, int num_bs, JNIEnv *env, jobject ms);

#ifdef __cplusplus
}
#endif
