#include "org_gmplib_gmpjni_GMP_mpz_t.h"
#include "gmp.h"
#include "malloc.h"

/*
 * Class:     org_gmplib_gmpjni_GMP_mpz_t
 * Method:    init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024mpz_1t_init
  (JNIEnv *, jobject)
{
    mpz_t *ptr = 0;
    ptr = (mpz_t *)malloc(sizeof(mpz_t));
    if (ptr != NULL) {
	mpz_init(*ptr);
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_mpz_t
 * Method:    init2
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024mpz_1t_init2
  (JNIEnv *, jobject, jlong n)
{
    mpz_t *ptr = 0;
    ptr = (mpz_t *)malloc(sizeof(mpz_t));
    if (ptr != NULL) {
	mpz_init2(*ptr, static_cast<mp_bitcnt_t>(n));
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_mpz_t
 * Method:    fini
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_00024mpz_1t_fini
  (JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass( "org/gmplib/gmpjni/GMP$mpz_t" );
    jfieldID field_id = env->GetFieldID( cls, "handle", "J" );
    jlong handle = env->GetLongField( obj, field_id );
    mpz_t *ptr = (mpz_t *)handle;
    if (ptr != NULL) {
	mpz_clear(*ptr);
	free(ptr);
	env->SetLongField(obj, field_id, (jlong)0);
    }
}
