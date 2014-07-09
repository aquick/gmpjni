#include "org_gmplib_gmpjni_GMP_mpf_t.h"
#include "gmp.h"
#include "malloc.h"

/*
 * Class:     org_gmplib_gmpjni_GMP_mpf_t
 * Method:    init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024mpf_1t_init
  (JNIEnv *, jobject)
{
    mpf_t *ptr = 0;
    ptr = (mpf_t *)malloc(sizeof(mpf_t));
    if (ptr != NULL) {
	mpf_init(*ptr);
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_mpf_t
 * Method:    init2
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024mpf_1t_init2
  (JNIEnv *, jobject, jlong precision)
{
    mpf_t *ptr = 0;
    ptr = (mpf_t *)malloc(sizeof(mpf_t));
    if (ptr != NULL) {
	mpf_init2(*ptr, static_cast<mp_bitcnt_t>(precision));
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_mpf_t
 * Method:    fini
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_00024mpf_1t_fini
  (JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass( "org/gmplib/gmpjni/GMP$mpf_t" );
    jfieldID field_id = env->GetFieldID( cls, "handle", "J" );
    jlong handle = env->GetLongField( obj, field_id );
    mpf_t *ptr = (mpf_t *)handle;
    if (ptr != NULL) {
	mpf_clear(*ptr);
	free(ptr);
	env->SetLongField(obj, field_id, (jlong)0);
    }
}
