#include "org_gmplib_gmpjni_GMP_randstate_t.h"
#include "gmp.h"
#include "malloc.h"

/*
 * Class:     org_gmplib_gmpjni_GMP_randstate_t
 * Method:    init
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024randstate_1t_init
  (JNIEnv *, jobject, jlong seed)
{
    gmp_randstate_t *ptr = 0;
    ptr = (gmp_randstate_t *)malloc(sizeof(gmp_randstate_t));
    if (ptr != NULL) {
	gmp_randinit_mt(*ptr);
	gmp_randseed_ui(*ptr, static_cast<unsigned long int>(seed));
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_randstate_t
 * Method:    init2
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_00024randstate_1t_init2
  (JNIEnv *, jobject, jlong seedptr)
{
    mpz_t *seed = reinterpret_cast<mpz_t *>(seedptr);
    gmp_randstate_t *ptr = 0;
    ptr = (gmp_randstate_t *)malloc(sizeof(gmp_randstate_t));
    if (ptr != NULL) {
	gmp_randinit_mt(*ptr);
	gmp_randseed(*ptr, *seed);
    }
    return (jlong)ptr;
}

/*
 * Class:     org_gmplib_gmpjni_GMP_randstate_t
 * Method:    fini
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_00024randstate_1t_fini
  (JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass( "org/gmplib/gmpjni/GMP$randstate_t" );
    jfieldID field_id = env->GetFieldID( cls, "handle", "J" );
    jlong handle = env->GetLongField( obj, field_id );
    gmp_randstate_t *ptr = reinterpret_cast<gmp_randstate_t *>(handle);
    if (ptr != NULL) {
	gmp_randclear(*ptr);
	free(ptr);
	env->SetLongField(obj, field_id, (jlong)0);
    }
}
