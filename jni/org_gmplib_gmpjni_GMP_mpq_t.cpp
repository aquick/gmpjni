#include "org_gmplib_gmpjni_GMP_mpq_t.h"
#include "gmp.h"
#include "malloc.h"

/*
 * Class:     org_gmplib_gmpjni_GMP_mpq_t
 * Method:    init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024mpq_1t_init
  (JNIEnv *, jobject)
{
    mpq_t *ptr = 0;
    ptr = (mpq_t *)malloc(sizeof(mpq_t));
    if (ptr != NULL) {
	mpq_init(*ptr);
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_mpq_t
 * Method:    fini
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_00024mpq_1t_fini
  (JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass( "org/gmplib/gmpjni/GMP$mpq_t" );
    jfieldID field_id = env->GetFieldID( cls, "handle", "J" );
    jlong handle = env->GetLongField( obj, field_id );
    mpq_t *ptr = (mpq_t *)handle;
    if (ptr != NULL) {
	mpq_clear(*ptr);
	free(ptr);
	env->SetLongField(obj, field_id, (jlong)0);
    }
}
