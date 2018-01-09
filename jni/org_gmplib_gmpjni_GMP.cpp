#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include "org_gmplib_gmpjni_GMP.h"
#include "org_gmplib_gmpjni_GMP_GMPException.h"
#include "gmp.h"

#define ABS(x) ((x) >= 0 ? (x) : -(x))

void throwGMPException
  ( JNIEnv * env, jint p0, jstring p1)
{
    jclass exception_class = env->FindClass("org/gmplib/gmpjni/GMP$GMPException");
    if (0 != exception_class) {
	jmethodID ctor_id = env->GetMethodID(exception_class, "<init>", "(ILjava/lang/String;)V");
	if (0 != ctor_id) {
	    jobject exception_object = env->NewObject(exception_class, ctor_id, p0, p1);
	    if (0 != exception_object) {
		if (0 != env->Throw( (jthrowable)exception_object)) {
		    env->DeleteLocalRef(exception_object);
		}
	    }
	}
	env->DeleteLocalRef(exception_class);
    }
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    GMP_LIMB_BITS
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_GMP_1LIMB_1BITS
  (JNIEnv *env, jclass cl)
{
    return GMP_LIMB_BITS;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    GMP_NAIL_BITS
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_GMP_1NAIL_1BITS
  (JNIEnv *env, jclass cl)
{
    return GMP_NAIL_BITS;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    GMP_NUMB_BITS
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_GMP_1NUMB_1BITS
  (JNIEnv *env, jclass cl)
{
    return GMP_NUMB_BITS;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_set_str
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1str
  (JNIEnv *env, jclass cl, jlong x, jstring str, jint base)
{
    jboolean is_copy;
    char const *str_chars = NULL;
    mpz_t *xptr = reinterpret_cast<mpz_t *>(x);

    str_chars = env->GetStringUTFChars(str, &is_copy);
    if (mpz_set_str(*xptr, str_chars, base) != 0) {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_BAD_FORMAT,
				env->NewStringUTF("bad format"));
    }
    env->ReleaseStringUTFChars( str, str_chars );
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_get_str
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1get_1str
  (JNIEnv *env, jclass cl, jlong x, jint base)
{
    jstring ret = 0;
    char *buffer;
    mpz_t *xptr = reinterpret_cast<mpz_t *>(x);

    buffer = (char *)malloc( (mpz_sizeinbase(*xptr, ABS(base)) + 2)*sizeof(char) );
    if (buffer != NULL) {
        mpz_get_str(buffer, base, *xptr);
        ret = env->NewStringUTF(buffer);
        free(buffer);
    } else {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OUT_OF_MEMORY,
				env->NewStringUTF("out of memory"));
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_get_d_2exp
 * Signature: (Lorg/gmplib/gmpjni/GMP/MutableInteger;J)D
 */
JNIEXPORT jdouble JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1get_1d_12exp
  (JNIEnv *env, jclass cl, jobject exp, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);
    signed long int e;
    jdouble r;
    jclass mic = env->FindClass("org/gmplib/gmpjni/GMP$MutableInteger");
    jfieldID fid = env->GetFieldID(mic, "value", "I");

    r = mpz_get_d_2exp(&e, *opptr);
    env->SetIntField(exp, fid, e);
    return r;
}


/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpq_set_str
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1str
  (JNIEnv *env, jclass cl, jlong x, jstring str, jint base)
{
    jboolean is_copy;
    char const *str_chars = NULL;
    mpq_t *xptr = reinterpret_cast<mpq_t *>(x);

    str_chars = env->GetStringUTFChars(str, &is_copy);
    if (mpq_set_str(*xptr, str_chars, base) != 0) {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_BAD_FORMAT,
				env->NewStringUTF("bad format"));
    }
    env->ReleaseStringUTFChars( str, str_chars );
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpf_set_str
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1str
  (JNIEnv *env, jclass cl, jlong x, jstring str, jint base)
{
    jboolean is_copy;
    char const *str_chars = NULL;
    mpf_t *xptr = reinterpret_cast<mpf_t *>(x);

    str_chars = env->GetStringUTFChars(str, &is_copy);
    if (mpf_set_str(*xptr, str_chars, base) != 0) {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_BAD_FORMAT,
				env->NewStringUTF("bad format"));
    }
    env->ReleaseStringUTFChars( str, str_chars );
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpq_get_str
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1get_1str
  (JNIEnv *env, jclass cl, jlong x, jint base)
{
    jstring ret = 0;
    char *buffer;
    mpq_t *xptr = reinterpret_cast<mpq_t *>(x);

    buffer = (char *)malloc( (mpz_sizeinbase (mpq_numref(*xptr), ABS(base))
                               + mpz_sizeinbase (mpq_denref(*xptr), ABS(base)) + 3)*sizeof(char) );
    if (buffer != NULL) {
        mpq_get_str(buffer, base, *xptr);
        ret = env->NewStringUTF(buffer);
        free(buffer);
    } else {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OUT_OF_MEMORY,
				env->NewStringUTF("out of memory"));
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpf_get_str
 * Signature: (Lorg/gmplib/gmpjni/GMP/MutableInteger;IJJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1str
  (JNIEnv *env, jclass cl, jobject exp, jint base, jlong n_digits, jlong op)
{
    jstring ret = 0;
    char *buffer;
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);
    mp_exp_t e;
    jclass mic = env->FindClass("org/gmplib/gmpjni/GMP$MutableInteger");
    jfieldID fid = env->GetFieldID(mic, "value", "I");

    buffer = (char *)malloc( (n_digits + 2)*sizeof(char) );
    if (buffer != NULL) {
        mpf_get_str(buffer, &e, base, n_digits, *opptr);
        ret = env->NewStringUTF(buffer);
        env->SetIntField(exp, fid, e);
        free(buffer);
    } else {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OUT_OF_MEMORY,
				env->NewStringUTF("out of memory"));
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_out_str
 * Signature: (Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1out_1str
  (JNIEnv *env, jclass cl, jstring filename, jint base, jlong op)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "w");
	if (file != NULL) {
	    ret = mpz_out_str(file, base, *opptr);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_inp_str
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1inp_1str
  (JNIEnv *env, jclass cl, jlong rop, jstring filename, jint base)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "r");
	if (file != NULL) {
	    ret = mpz_inp_str(*ropptr, file, base);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpq_out_str
 * Signature: (Ljava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1out_1str
  (JNIEnv *env, jclass cl, jstring filename, jint base, jlong op)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "w");
	if (file != NULL) {
	    ret = mpq_out_str(file, base, *opptr);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpq_inp_str
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1inp_1str
  (JNIEnv *env, jclass cl, jlong rop, jstring filename, jint base)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "r");
	if (file != NULL) {
	    ret = mpq_inp_str(*ropptr, file, base);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpf_out_str
 * Signature: (Ljava/lang/String;IJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1out_1str
  (JNIEnv *env, jclass cl, jstring filename, jint base, jlong n_digits, jlong op)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "w");
	if (file != NULL) {
	    ret = mpf_out_str(file, base, n_digits, *opptr);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpf_inp_str
 * Signature: (JLjava/lang/String;I)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1inp_1str
  (JNIEnv *env, jclass cl, jlong rop, jstring filename, jint base)
{
    size_t ret = 0;
    jboolean is_copy;
    char const *fn_chars = NULL;
    FILE *file = NULL;
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    char buffer[30];

    if (filename != 0) {
        fn_chars = env->GetStringUTFChars(filename, &is_copy);
	file = fopen(fn_chars, "r");
	if (file != NULL) {
	    ret = mpf_inp_str(*ropptr, file, base);
	    fclose(file);
	} else {
	    snprintf(buffer, sizeof(buffer), "I/O Error (%d)", errno);
	    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_IO_ERROR,
				env->NewStringUTF(buffer));
	}
        env->ReleaseStringUTFChars(filename, fn_chars);
    }
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_gmp_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_gmplib_gmpjni_GMP_native_1gmp_1version
  (JNIEnv *env, jclass cl)
{
    jstring ret = env->NewStringUTF(gmp_version);
    return ret;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpf_get_d_2exp
 * Signature: (Lorg/gmplib/gmpjni/GMP/MutableInteger;J)D
 */
JNIEXPORT jdouble JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1d_12exp
  (JNIEnv *env, jclass cl, jobject exp, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);
    signed long int e;
    jdouble r;
    jclass mic = env->FindClass("org/gmplib/gmpjni/GMP$MutableInteger");
    jfieldID fid = env->GetFieldID(mic, "value", "I");

    r = mpf_get_d_2exp(&e, *opptr);
    env->SetIntField(exp, fid, e);
    return r;
}

/* Field access macros.  */
#define SIZ(x) ((x)->_mp_size)
#define ABSIZ(x) ABS (SIZ (x))
#define PTR(x) ((x)->_mp_d)
#define ALLOC(x) ((x)->_mp_alloc)

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1SIZ
  (JNIEnv *env, jclass cl, jlong z)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    return SIZ(*zptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1SETSIZ
  (JNIEnv *env, jclass cl, jlong z, jint size)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    SIZ(*zptr) = size;
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1ABSIZ
  (JNIEnv *env, jclass cl, jlong z)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    return ABSIZ(*zptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1ALLOC
  (JNIEnv *env, jclass cl, jlong z)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    return ALLOC(*zptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1REALLOC
  (JNIEnv *env, jclass cl, jlong z, jint amount)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    mpz_realloc (*zptr, (mp_size_t) amount);
}

#define ASSERT_ALWAYS(env, cond) \
{ \
    if (!(cond)) { \
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_INTERNAL_ERROR, \
				env->NewStringUTF("assertion failed: " #cond)); \
    } \
}

/* Check that the nail parts are zero. */
#define ASSERT_ALWAYS_LIMB(env, limb)                    \
  do {                                  \
    mp_limb_t  __nail = (limb) & GMP_NAIL_MASK;             \
    ASSERT_ALWAYS (env, __nail == 0);                    \
  } while (0)

#define ASSERT_ALWAYS_MPN(env, ptr, size)                    \
  do {                                  \
    /* let whole loop go dead when no nails */              \
    if (GMP_NAIL_BITS != 0)                     \
      {                                 \
    mp_size_t  __i;                         \
    for (__i = 0; __i < (size); __i++)              \
      ASSERT_ALWAYS_LIMB (env, (ptr)[__i]);              \
      }                                 \
  } while (0)

/* For testing and debugging.  */
#define MPZ_CHECK_FORMAT(env, z)                     \
  do {                                  \
    ASSERT_ALWAYS (env, SIZ(z) == 0 || PTR(z)[ABSIZ(z) - 1] != 0);       \
    ASSERT_ALWAYS (env, ALLOC(z) >= ABSIZ(z));               \
    ASSERT_ALWAYS_MPN (env, PTR(z), ABSIZ(z));               \
  } while (0)

#define MPQ_CHECK_FORMAT(env, q)                     \
  do {                                  \
    MPZ_CHECK_FORMAT (env, mpq_numref (q));                  \
    MPZ_CHECK_FORMAT (env, mpq_denref (q));                  \
    ASSERT_ALWAYS (env, SIZ(mpq_denref(q)) >= 1);                \
                                    \
    if (SIZ(mpq_numref(q)) == 0)                    \
      {                                 \
    /* should have zero as 0/1 */                   \
    ASSERT_ALWAYS (env, SIZ(mpq_denref(q)) == 1              \
               && PTR(mpq_denref(q))[0] == 1);          \
      }                                 \
    else                                \
      {                                 \
    /* should have no common factors */             \
    mpz_t  g;                           \
    mpz_init (g);                           \
    mpz_gcd (g, mpq_numref(q), mpq_denref(q));          \
    ASSERT_ALWAYS (env, mpz_cmp_ui (g, 1) == 0);             \
    mpz_clear (g);                          \
      }                                 \
  } while (0)

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1CHECK_1FORMAT
  (JNIEnv *env, jclass cl, jlong z)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);

    MPZ_CHECK_FORMAT(env, *zptr);
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpq_internal_CHECK_FORMAT
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1internal_1CHECK_1FORMAT
  (JNIEnv *env, jclass cl, jlong q)
{
    mpq_t *qptr = reinterpret_cast<mpq_t *>(q);

    MPQ_CHECK_FORMAT(env, *qptr);
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_refmpn_cmp
 * Signature: (J[JJ)I
 */
JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1refmpn_1cmp
  (JNIEnv *env, jclass cl, jlong x, jlongArray y, jlong size)
{
    mpz_t *xptr = reinterpret_cast<mpz_t *>(x);
    mp_size_t  i;
    mp_srcptr xp = PTR(*xptr);
    mp_ptr yp = NULL;
    jlong *ya;
    jboolean is_copy;
    mp_size_t sz = (mp_size_t)size;
    jint ret = 0;

    yp = (mp_limb_t *)malloc(sz*sizeof(mp_limb_t));
    if (yp == NULL) {
	throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OUT_OF_MEMORY,
				env->NewStringUTF("out of memory"));
    }
    ya = env->GetLongArrayElements( y, &is_copy );
    for (i = sz-1; i >= 0; i--) {
	yp[i] = (mp_limb_t)(ya[i]);
    }
    env->ReleaseLongArrayElements( y, ya, JNI_ABORT );

    ASSERT_ALWAYS (env, sz >= 1);
    ASSERT_ALWAYS_MPN (env, xp, sz);
    ASSERT_ALWAYS_MPN (env, yp, sz);

    for (i = sz-1; i >= 0; i--) {
        if (xp[i] > yp[i]) {
	    ret = 1;
	    break;
	}
        if (xp[i] < yp[i]) {
	    ret= -1;
	    break;
	}
    }
    free(yp);
    return ret;
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1get_1ulimb
  (JNIEnv *env, jclass cl, jlong z, jint index)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);
    if (SIZ(*zptr) == 0) return 0;
    mp_limb_t rval = PTR(*zptr)[index];
    return (jlong)rval;
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1set_1ulimb
  (JNIEnv *env, jclass cl, jlong z, jint index, jlong value)
{
    mpz_t *zptr = reinterpret_cast<mpz_t *>(z);
    PTR(*zptr)[index] = static_cast<mp_limb_t>(value);
}

#include <time.h>

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_internal_mpn_mul_1
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1mpn_1mul_11
  (JNIEnv *env, jclass cl, jlong r, jlong x, jlong y)
{
    mpz_t *xptr = reinterpret_cast<mpz_t *>(x);
    mp_size_t  n = SIZ(*xptr);
    mp_srcptr xp = PTR(*xptr);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mp_ptr rp = PTR(*rptr);
    mp_limb_t yl = static_cast<mp_limb_t>(y);
    mp_limb_t c;
    timespec tb = {0, 0};
    timespec te = {0, 0};
    int rc;
    int64_t delta = -1;

    rc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tb);
    c = mpn_mul_1(rp, xp, n, yl);
    rc = rc | clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &te);

    if (c > 0) {
        ASSERT_ALWAYS(env, ALLOC(*rptr) > n);
	SIZ(*rptr) = n + 1;
        rp[n] = c;
    }
    if (rc == 0) {
	// assumes delta is less than 4 seconds
        delta = te.tv_nsec - tb.tv_nsec;
	if (delta < 0) {
	    ASSERT_ALWAYS(env, te.tv_sec - tb.tv_sec <= 4);
	    delta += 1000000000L;
	    delta += static_cast<int64_t>(te.tv_sec - tb.tv_sec - 1)*1000000000L;
	}
    }
    return delta;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_internal_mpn_addmul_1
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1mpn_1addmul_11
  (JNIEnv *env, jclass cl, jlong r, jlong x, jlong y)
{
    mpz_t *xptr = reinterpret_cast<mpz_t *>(x);
    mp_size_t  n = SIZ(*xptr);
    mp_srcptr xp = PTR(*xptr);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mp_ptr rp = PTR(*rptr);
    mp_limb_t yl = static_cast<mp_limb_t>(y);
    mp_limb_t c;
    timespec tb = {0, 0};
    timespec te = {0, 0};
    int rc;
    int64_t delta = -1;

    rc = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tb);
    c = mpn_addmul_1(rp, xp, n, yl);
    rc = rc | clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &te);

    if (c > 0) {
        ASSERT_ALWAYS(env, ALLOC(*rptr) > n);
	SIZ(*rptr) = n + 1;
        rp[n] = c;
    }
    if (rc == 0) {
	// assumes delta is less than 4 seconds
        delta = te.tv_nsec - tb.tv_nsec;
	if (delta < 0) {
	    ASSERT_ALWAYS(env, te.tv_sec - tb.tv_sec <= 4);
	    delta += 1000000000L;
	    delta += static_cast<int64_t>(te.tv_sec - tb.tv_sec - 1)*1000000000L;
	}
    }
    return delta;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_internal_mpn_mul_1_neon
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1mpn_1mul_11_1neon
  (JNIEnv *env, jclass cl, jlong r, jlong x, jlong y)
{
    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OPERATION_NOT_SUPPORTED, env->NewStringUTF("operation not supported"));
    return -1;
}

/*
 * Class:     org_gmplib_gmpjni_GMP
 * Method:    native_mpz_internal_mpn_addmul_1_neon
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1internal_1mpn_1addmul_11_1neon
  (JNIEnv *env, jclass cl, jlong r, jlong x, jlong y)
{
    throwGMPException(env, org_gmplib_gmpjni_GMP_GMPException_OPERATION_NOT_SUPPORTED, env->NewStringUTF("operation not supported"));
    return -1;
}

/************************************************************************
 * Auto-generated functions
 ***********************************************************************/
JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_set(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_set_ui(*ropptr, static_cast<unsigned long int>(op));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1si
  (JNIEnv *env, jclass cl, jlong rop, jint op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_set_si(*ropptr, op);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1d
  (JNIEnv *env, jclass cl, jlong rop, jdouble op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_set_d(*ropptr, op);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1q
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    mpz_set_q(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1set_1f
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpz_set_f(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1swap
  (JNIEnv *env, jclass cl, jlong rop1, jlong rop2)
{
    mpz_t *rop1ptr = reinterpret_cast<mpz_t *>(rop1);
    mpz_t *rop2ptr = reinterpret_cast<mpz_t *>(rop2);

    mpz_swap(*rop1ptr, *rop2ptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1get_1ui
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_get_ui(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1get_1si
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_get_si(*opptr);
}

JNIEXPORT jdouble JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1get_1d
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_get_d(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1add
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_add(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1add_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_add_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sub
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_sub(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sub_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_sub_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1ui_1sub
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_ui_sub(*ropptr, static_cast<unsigned long int>(op1), *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mul
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_mul(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mul_1si
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jint op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_mul_si(*ropptr, *op1ptr, op2);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mul_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_mul_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1addmul
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_addmul(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1addmul_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_addmul_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1submul
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_submul(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1submul_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_submul_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mul_12exp
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_mul_2exp(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1neg
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_neg(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1abs
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_abs(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1q
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_cdiv_q(*qptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1r
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_cdiv_r(*rptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1qr
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_cdiv_qr(*qptr, *rptr, *nptr, *dptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1q_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_cdiv_q_ui(*qptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1r_1ui
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_cdiv_r_ui(*rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1qr_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_cdiv_qr_ui(*qptr, *rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1ui
  (JNIEnv *env, jclass cl, jlong n, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_cdiv_ui(*nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1q_12exp
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong b)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_cdiv_q_2exp(*qptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cdiv_1r_12exp
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong b)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_cdiv_r_2exp(*rptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1q
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_fdiv_q(*qptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1r
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_fdiv_r(*rptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1qr
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_fdiv_qr(*qptr, *rptr, *nptr, *dptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1q_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_fdiv_q_ui(*qptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1r_1ui
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_fdiv_r_ui(*rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1qr_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_fdiv_qr_ui(*qptr, *rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1ui
  (JNIEnv *env, jclass cl, jlong n, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_fdiv_ui(*nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1q_12exp
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong b)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_fdiv_q_2exp(*qptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fdiv_1r_12exp
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong b)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_fdiv_r_2exp(*rptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1q
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_tdiv_q(*qptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1r
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_tdiv_r(*rptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1qr
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_tdiv_qr(*qptr, *rptr, *nptr, *dptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1q_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_tdiv_q_ui(*qptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1r_1ui
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_tdiv_r_ui(*rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1qr_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong r, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_tdiv_qr_ui(*qptr, *rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1ui
  (JNIEnv *env, jclass cl, jlong n, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_tdiv_ui(*nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1q_12exp
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong b)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_tdiv_q_2exp(*qptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tdiv_1r_12exp
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong b)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_tdiv_r_2exp(*rptr, *nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mod
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_mod(*rptr, *nptr, *dptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mod_1ui
  (JNIEnv *env, jclass cl, jlong r, jlong n, jlong d)
{
    mpz_t *rptr = reinterpret_cast<mpz_t *>(r);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_mod_ui(*rptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1divexact
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    mpz_divexact(*qptr, *nptr, *dptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1divexact_1ui
  (JNIEnv *env, jclass cl, jlong q, jlong n, jlong d)
{
    mpz_t *qptr = reinterpret_cast<mpz_t *>(q);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_divexact_ui(*qptr, *nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1divisible_1p
  (JNIEnv *env, jclass cl, jlong n, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    return mpz_divisible_p(*nptr, *dptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1divisible_1ui_1p
  (JNIEnv *env, jclass cl, jlong n, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_divisible_ui_p(*nptr, static_cast<unsigned long int>(d));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1divisible_12exp_1p
  (JNIEnv *env, jclass cl, jlong n, jlong b)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_divisible_2exp_p(*nptr, static_cast<unsigned long int>(b));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1congruent_1p
  (JNIEnv *env, jclass cl, jlong n, jlong c, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *cptr = reinterpret_cast<mpz_t *>(c);
    mpz_t *dptr = reinterpret_cast<mpz_t *>(d);

    return mpz_congruent_p(*nptr, *cptr, *dptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1congruent_1ui_1p
  (JNIEnv *env, jclass cl, jlong n, jlong c, jlong d)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_congruent_ui_p(*nptr, static_cast<unsigned long int>(c), static_cast<unsigned long int>(d));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1congruent_12exp_1p
  (JNIEnv *env, jclass cl, jlong n, jlong c, jlong b)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);
    mpz_t *cptr = reinterpret_cast<mpz_t *>(c);

    return mpz_congruent_2exp_p(*nptr, *cptr, static_cast<unsigned long int>(b));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1powm
  (JNIEnv *env, jclass cl, jlong rop, jlong base, jlong exp, jlong mod)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *baseptr = reinterpret_cast<mpz_t *>(base);
    mpz_t *expptr = reinterpret_cast<mpz_t *>(exp);
    mpz_t *modptr = reinterpret_cast<mpz_t *>(mod);

    mpz_powm(*ropptr, *baseptr, *expptr, *modptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1powm_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong base, jlong exp, jlong mod)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *baseptr = reinterpret_cast<mpz_t *>(base);
    mpz_t *modptr = reinterpret_cast<mpz_t *>(mod);

    mpz_powm_ui(*ropptr, *baseptr, static_cast<unsigned long int>(exp), *modptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1powm_1sec
  (JNIEnv *env, jclass cl, jlong rop, jlong base, jlong exp, jlong mod)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *baseptr = reinterpret_cast<mpz_t *>(base);
    mpz_t *expptr = reinterpret_cast<mpz_t *>(exp);
    mpz_t *modptr = reinterpret_cast<mpz_t *>(mod);

    mpz_powm_sec(*ropptr, *baseptr, *expptr, *modptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1pow_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong base, jlong exp)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *baseptr = reinterpret_cast<mpz_t *>(base);

    mpz_pow_ui(*ropptr, *baseptr, static_cast<unsigned long int>(exp));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1ui_1pow_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong base, jlong exp)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_ui_pow_ui(*ropptr, static_cast<unsigned long int>(base), static_cast<unsigned long int>(exp));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1root
  (JNIEnv *env, jclass cl, jlong rop, jlong op, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_root(*ropptr, *opptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1rootrem
  (JNIEnv *env, jclass cl, jlong root, jlong rem, jlong u, jlong n)
{
    mpz_t *rootptr = reinterpret_cast<mpz_t *>(root);
    mpz_t *remptr = reinterpret_cast<mpz_t *>(rem);
    mpz_t *uptr = reinterpret_cast<mpz_t *>(u);

    mpz_rootrem(*rootptr, *remptr, *uptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sqrt
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_sqrt(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sqrtrem
  (JNIEnv *env, jclass cl, jlong rop1, jlong rop2, jlong op)
{
    mpz_t *rop1ptr = reinterpret_cast<mpz_t *>(rop1);
    mpz_t *rop2ptr = reinterpret_cast<mpz_t *>(rop2);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_sqrtrem(*rop1ptr, *rop2ptr, *opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1perfect_1power_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_perfect_power_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1perfect_1square_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_perfect_square_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1probab_1prime_1p
  (JNIEnv *env, jclass cl, jlong n, jint reps)
{
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    return mpz_probab_prime_p(*nptr, reps);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1nextprime
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_nextprime(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1gcd
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_gcd(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1gcd_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_gcd_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1gcdext
  (JNIEnv *env, jclass cl, jlong g, jlong s, jlong t, jlong a, jlong b)
{
    mpz_t *gptr = reinterpret_cast<mpz_t *>(g);
    mpz_t *sptr = reinterpret_cast<mpz_t *>(s);
    mpz_t *tptr = reinterpret_cast<mpz_t *>(t);
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);
    mpz_t *bptr = reinterpret_cast<mpz_t *>(b);

    mpz_gcdext(*gptr, *sptr, *tptr, *aptr, *bptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1lcm
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_lcm(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1lcm_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    mpz_lcm_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1invert
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    return mpz_invert(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1jacobi
  (JNIEnv *env, jclass cl, jlong a, jlong b)
{
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);
    mpz_t *bptr = reinterpret_cast<mpz_t *>(b);

    return mpz_jacobi(*aptr, *bptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1legendre
  (JNIEnv *env, jclass cl, jlong a, jlong p)
{
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);
    mpz_t *pptr = reinterpret_cast<mpz_t *>(p);

    return mpz_legendre(*aptr, *pptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1kronecker
  (JNIEnv *env, jclass cl, jlong a, jlong b)
{
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);
    mpz_t *bptr = reinterpret_cast<mpz_t *>(b);

    return mpz_kronecker(*aptr, *bptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1kronecker_1si
  (JNIEnv *env, jclass cl, jlong a, jint b)
{
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);

    return mpz_kronecker_si(*aptr, b);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1kronecker_1ui
  (JNIEnv *env, jclass cl, jlong a, jlong b)
{
    mpz_t *aptr = reinterpret_cast<mpz_t *>(a);

    return mpz_kronecker_ui(*aptr, static_cast<unsigned long int>(b));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1si_1kronecker
  (JNIEnv *env, jclass cl, jint a, jlong b)
{
    mpz_t *bptr = reinterpret_cast<mpz_t *>(b);

    return mpz_si_kronecker(a, *bptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1ui_1kronecker
  (JNIEnv *env, jclass cl, jlong a, jlong b)
{
    mpz_t *bptr = reinterpret_cast<mpz_t *>(b);

    return mpz_ui_kronecker(static_cast<unsigned long int>(a), *bptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1remove
  (JNIEnv *env, jclass cl, jlong rop, jlong op, jlong f)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);
    mpz_t *fptr = reinterpret_cast<mpz_t *>(f);

    return mpz_remove(*ropptr, *opptr, *fptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fac_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_fac_ui(*ropptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_12fac_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_2fac_ui(*ropptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1mfac_1uiui
  (JNIEnv *env, jclass cl, jlong rop, jlong n, jlong m)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_mfac_uiui(*ropptr, static_cast<unsigned long int>(n), static_cast<unsigned long int>(m));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1primorial_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_primorial_ui(*ropptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1bin_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong n, jlong k)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_bin_ui(*ropptr, *nptr, static_cast<unsigned long int>(k));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1bin_1uiui
  (JNIEnv *env, jclass cl, jlong rop, jlong n, jlong k)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_bin_uiui(*ropptr, static_cast<unsigned long int>(n), static_cast<unsigned long int>(k));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fib_1ui
  (JNIEnv *env, jclass cl, jlong fn, jlong n)
{
    mpz_t *fnptr = reinterpret_cast<mpz_t *>(fn);

    mpz_fib_ui(*fnptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fib2_1ui
  (JNIEnv *env, jclass cl, jlong fn, jlong fnsub1, jlong n)
{
    mpz_t *fnptr = reinterpret_cast<mpz_t *>(fn);
    mpz_t *fnsub1ptr = reinterpret_cast<mpz_t *>(fnsub1);

    mpz_fib2_ui(*fnptr, *fnsub1ptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1lucnum_1ui
  (JNIEnv *env, jclass cl, jlong ln, jlong n)
{
    mpz_t *lnptr = reinterpret_cast<mpz_t *>(ln);

    mpz_lucnum_ui(*lnptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1lucnum2_1ui
  (JNIEnv *env, jclass cl, jlong ln, jlong lnsub1, jlong n)
{
    mpz_t *lnptr = reinterpret_cast<mpz_t *>(ln);
    mpz_t *lnsub1ptr = reinterpret_cast<mpz_t *>(lnsub1);

    mpz_lucnum2_ui(*lnptr, *lnsub1ptr, static_cast<unsigned long int>(n));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmp
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    return mpz_cmp(*op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmp_1d
  (JNIEnv *env, jclass cl, jlong op1, jdouble op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_cmp_d(*op1ptr, op2);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmp_1si
  (JNIEnv *env, jclass cl, jlong op1, jint op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_cmp_si(*op1ptr, op2);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmp_1ui
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_cmp_ui(*op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmpabs
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    return mpz_cmpabs(*op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmpabs_1d
  (JNIEnv *env, jclass cl, jlong op1, jdouble op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_cmpabs_d(*op1ptr, op2);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1cmpabs_1ui
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);

    return mpz_cmpabs_ui(*op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sgn
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_sgn(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1and
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_and(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1ior
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_ior(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1xor
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    mpz_xor(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1com
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpz_com(*ropptr, *opptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1popcount
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_popcount(*opptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1hamdist
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpz_t *op1ptr = reinterpret_cast<mpz_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    return mpz_hamdist(*op1ptr, *op2ptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1scan0
  (JNIEnv *env, jclass cl, jlong op, jlong starting_bit)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_scan0(*opptr, static_cast<unsigned long int>(starting_bit));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1scan1
  (JNIEnv *env, jclass cl, jlong op, jlong starting_bit)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_scan1(*opptr, static_cast<unsigned long int>(starting_bit));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1setbit
  (JNIEnv *env, jclass cl, jlong rop, jlong bit_index)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_setbit(*ropptr, static_cast<unsigned long int>(bit_index));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1clrbit
  (JNIEnv *env, jclass cl, jlong rop, jlong bit_index)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_clrbit(*ropptr, static_cast<unsigned long int>(bit_index));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1combit
  (JNIEnv *env, jclass cl, jlong rop, jlong bit_index)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);

    mpz_combit(*ropptr, static_cast<unsigned long int>(bit_index));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1tstbit
  (JNIEnv *env, jclass cl, jlong op, jlong bit_index)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_tstbit(*opptr, static_cast<unsigned long int>(bit_index));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1ulong_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_ulong_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1slong_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_slong_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1uint_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_uint_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1sint_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_sint_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1ushort_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_ushort_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1fits_1sshort_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_fits_sshort_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1odd_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_odd_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1even_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_even_p(*opptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1sizeinbase
  (JNIEnv *env, jclass cl, jlong op, jint base)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_sizeinbase(*opptr, base);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1getlimbn
  (JNIEnv *env, jclass cl, jlong op, jint n)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_getlimbn(*opptr, n);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1size
  (JNIEnv *env, jclass cl, jlong op)
{
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    return mpz_size(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1canonicalize
  (JNIEnv *env, jclass cl, jlong op)
{
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    mpq_canonicalize(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    mpq_set(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1z
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpq_set_z(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);

    mpq_set_ui(*ropptr, static_cast<unsigned long int>(op1), static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1si
  (JNIEnv *env, jclass cl, jlong rop, jint op1, jlong op2)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);

    mpq_set_si(*ropptr, op1, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1swap
  (JNIEnv *env, jclass cl, jlong rop1, jlong rop2)
{
    mpq_t *rop1ptr = reinterpret_cast<mpq_t *>(rop1);
    mpq_t *rop2ptr = reinterpret_cast<mpq_t *>(rop2);

    mpq_swap(*rop1ptr, *rop2ptr);
}

JNIEXPORT jdouble JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1get_1d
  (JNIEnv *env, jclass cl, jlong op)
{
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    return mpq_get_d(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1d
  (JNIEnv *env, jclass cl, jlong rop, jdouble op)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);

    mpq_set_d(*ropptr, op);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1f
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpq_set_f(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1add
  (JNIEnv *env, jclass cl, jlong sum, jlong addend1, jlong addend2)
{
    mpq_t *sumptr = reinterpret_cast<mpq_t *>(sum);
    mpq_t *addend1ptr = reinterpret_cast<mpq_t *>(addend1);
    mpq_t *addend2ptr = reinterpret_cast<mpq_t *>(addend2);

    mpq_add(*sumptr, *addend1ptr, *addend2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1sub
  (JNIEnv *env, jclass cl, jlong difference, jlong minuend, jlong subtrahend)
{
    mpq_t *differenceptr = reinterpret_cast<mpq_t *>(difference);
    mpq_t *minuendptr = reinterpret_cast<mpq_t *>(minuend);
    mpq_t *subtrahendptr = reinterpret_cast<mpq_t *>(subtrahend);

    mpq_sub(*differenceptr, *minuendptr, *subtrahendptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1mul
  (JNIEnv *env, jclass cl, jlong product, jlong multiplier, jlong multiplicand)
{
    mpq_t *productptr = reinterpret_cast<mpq_t *>(product);
    mpq_t *multiplierptr = reinterpret_cast<mpq_t *>(multiplier);
    mpq_t *multiplicandptr = reinterpret_cast<mpq_t *>(multiplicand);

    mpq_mul(*productptr, *multiplierptr, *multiplicandptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1mul_12exp
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);

    mpq_mul_2exp(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1div
  (JNIEnv *env, jclass cl, jlong quotient, jlong dividend, jlong divisor)
{
    mpq_t *quotientptr = reinterpret_cast<mpq_t *>(quotient);
    mpq_t *dividendptr = reinterpret_cast<mpq_t *>(dividend);
    mpq_t *divisorptr = reinterpret_cast<mpq_t *>(divisor);

    mpq_div(*quotientptr, *dividendptr, *divisorptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1div_12exp
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);

    mpq_div_2exp(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1neg
  (JNIEnv *env, jclass cl, jlong negated_operand, jlong operand)
{
    mpq_t *negated_operandptr = reinterpret_cast<mpq_t *>(negated_operand);
    mpq_t *operandptr = reinterpret_cast<mpq_t *>(operand);

    mpq_neg(*negated_operandptr, *operandptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1abs
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpq_t *ropptr = reinterpret_cast<mpq_t *>(rop);
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    mpq_abs(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1inv
  (JNIEnv *env, jclass cl, jlong inverted_number, jlong number)
{
    mpq_t *inverted_numberptr = reinterpret_cast<mpq_t *>(inverted_number);
    mpq_t *numberptr = reinterpret_cast<mpq_t *>(number);

    mpq_inv(*inverted_numberptr, *numberptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1cmp
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);
    mpq_t *op2ptr = reinterpret_cast<mpq_t *>(op2);

    return mpq_cmp(*op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1cmp_1ui
  (JNIEnv *env, jclass cl, jlong op1, jlong num2, jlong den2)
{
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);

    return mpq_cmp_ui(*op1ptr, static_cast<unsigned long int>(num2), static_cast<unsigned long int>(den2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1cmp_1si
  (JNIEnv *env, jclass cl, jlong op1, jint num2, jlong den2)
{
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);

    return mpq_cmp_si(*op1ptr, num2, static_cast<unsigned long int>(den2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1cmp_1z
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);
    mpz_t *op2ptr = reinterpret_cast<mpz_t *>(op2);

    return mpq_cmp_z(*op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1sgn
  (JNIEnv *env, jclass cl, jlong op)
{
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    return mpq_sgn(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1equal
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpq_t *op1ptr = reinterpret_cast<mpq_t *>(op1);
    mpq_t *op2ptr = reinterpret_cast<mpq_t *>(op2);

    return mpq_equal(*op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1get_1num
  (JNIEnv *env, jclass cl, jlong numerator, jlong rational)
{
    mpz_t *numeratorptr = reinterpret_cast<mpz_t *>(numerator);
    mpq_t *rationalptr = reinterpret_cast<mpq_t *>(rational);

    mpq_get_num(*numeratorptr, *rationalptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1get_1den
  (JNIEnv *env, jclass cl, jlong denominator, jlong rational)
{
    mpz_t *denominatorptr = reinterpret_cast<mpz_t *>(denominator);
    mpq_t *rationalptr = reinterpret_cast<mpq_t *>(rational);

    mpq_get_den(*denominatorptr, *rationalptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1num
  (JNIEnv *env, jclass cl, jlong rational, jlong numerator)
{
    mpq_t *rationalptr = reinterpret_cast<mpq_t *>(rational);
    mpz_t *numeratorptr = reinterpret_cast<mpz_t *>(numerator);

    mpq_set_num(*rationalptr, *numeratorptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpq_1set_1den
  (JNIEnv *env, jclass cl, jlong rational, jlong denominator)
{
    mpq_t *rationalptr = reinterpret_cast<mpq_t *>(rational);
    mpz_t *denominatorptr = reinterpret_cast<mpz_t *>(denominator);

    mpq_set_den(*rationalptr, *denominatorptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1default_1prec
  (JNIEnv *env, jclass cl, jlong prec)
{

    mpf_set_default_prec(static_cast<unsigned long int>(prec));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1default_1prec
  (JNIEnv *env, jclass cl )
{

    return mpf_get_default_prec();
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1prec
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_get_prec(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1prec
  (JNIEnv *env, jclass cl, jlong rop, jlong prec)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_set_prec(*ropptr, static_cast<unsigned long int>(prec));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1prec_1raw
  (JNIEnv *env, jclass cl, jlong rop, jlong prec)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_set_prec_raw(*ropptr, static_cast<unsigned long int>(prec));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_set(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_set_ui(*ropptr, static_cast<unsigned long int>(op));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1si
  (JNIEnv *env, jclass cl, jlong rop, jint op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_set_si(*ropptr, op);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1d
  (JNIEnv *env, jclass cl, jlong rop, jdouble op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_set_d(*ropptr, op);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1z
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpz_t *opptr = reinterpret_cast<mpz_t *>(op);

    mpf_set_z(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1set_1q
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpq_t *opptr = reinterpret_cast<mpq_t *>(op);

    mpf_set_q(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1swap
  (JNIEnv *env, jclass cl, jlong rop1, jlong rop2)
{
    mpf_t *rop1ptr = reinterpret_cast<mpf_t *>(rop1);
    mpf_t *rop2ptr = reinterpret_cast<mpf_t *>(rop2);

    mpf_swap(*rop1ptr, *rop2ptr);
}

JNIEXPORT jdouble JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1d
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_get_d(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1si
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_get_si(*opptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1get_1ui
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_get_ui(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1add
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_add(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1add_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_add_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1sub
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_sub(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1ui_1sub
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_ui_sub(*ropptr, static_cast<unsigned long int>(op1), *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1sub_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_sub_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1mul
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_mul(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1mul_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_mul_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1div
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_div(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1ui_1div
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_ui_div(*ropptr, static_cast<unsigned long int>(op1), *op2ptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1div_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_div_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1sqrt
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_sqrt(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1sqrt_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);

    mpf_sqrt_ui(*ropptr, static_cast<unsigned long int>(op));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1pow_1ui
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_pow_ui(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1neg
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_neg(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1abs
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_abs(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1mul_12exp
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_mul_2exp(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1div_12exp
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    mpf_div_2exp(*ropptr, *op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1cmp
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    return mpf_cmp(*op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1cmp_1d
  (JNIEnv *env, jclass cl, jlong op1, jdouble op2)
{
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    return mpf_cmp_d(*op1ptr, op2);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1cmp_1ui
  (JNIEnv *env, jclass cl, jlong op1, jlong op2)
{
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    return mpf_cmp_ui(*op1ptr, static_cast<unsigned long int>(op2));
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1cmp_1si
  (JNIEnv *env, jclass cl, jlong op1, jint op2)
{
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);

    return mpf_cmp_si(*op1ptr, op2);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1eq
  (JNIEnv *env, jclass cl, jlong op1, jlong op2, jlong op3)
{
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    return mpf_eq(*op1ptr, *op2ptr, static_cast<unsigned long int>(op3));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1reldiff
  (JNIEnv *env, jclass cl, jlong rop, jlong op1, jlong op2)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *op1ptr = reinterpret_cast<mpf_t *>(op1);
    mpf_t *op2ptr = reinterpret_cast<mpf_t *>(op2);

    mpf_reldiff(*ropptr, *op1ptr, *op2ptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1sgn
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_sgn(*opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1ceil
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_ceil(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1floor
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_floor(*ropptr, *opptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1trunc
  (JNIEnv *env, jclass cl, jlong rop, jlong op)
{
    mpf_t *ropptr = reinterpret_cast<mpf_t *>(rop);
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    mpf_trunc(*ropptr, *opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1integer_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_integer_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1ulong_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_ulong_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1slong_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_slong_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1uint_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_uint_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1sint_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_sint_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1ushort_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_ushort_p(*opptr);
}

JNIEXPORT jint JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpf_1fits_1sshort_1p
  (JNIEnv *env, jclass cl, jlong op)
{
    mpf_t *opptr = reinterpret_cast<mpf_t *>(op);

    return mpf_fits_sshort_p(*opptr);
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1gmp_1urandomb_1ui
  (JNIEnv *env, jclass cl, jlong state, jlong n)
{
    gmp_randstate_t *stateptr = reinterpret_cast<gmp_randstate_t *>(state);

    return gmp_urandomb_ui(*stateptr, static_cast<unsigned long int>(n));
}

JNIEXPORT jlong JNICALL Java_org_gmplib_gmpjni_GMP_native_1gmp_1urandomm_1ui
  (JNIEnv *env, jclass cl, jlong state, jlong n)
{
    gmp_randstate_t *stateptr = reinterpret_cast<gmp_randstate_t *>(state);

    return gmp_urandomm_ui(*stateptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1urandomb
  (JNIEnv *env, jclass cl, jlong rop, jlong state, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    gmp_randstate_t *stateptr = reinterpret_cast<gmp_randstate_t *>(state);

    mpz_urandomb(*ropptr, *stateptr, static_cast<unsigned long int>(n));
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1urandomm
  (JNIEnv *env, jclass cl, jlong rop, jlong state, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    gmp_randstate_t *stateptr = reinterpret_cast<gmp_randstate_t *>(state);
    mpz_t *nptr = reinterpret_cast<mpz_t *>(n);

    mpz_urandomm(*ropptr, *stateptr, *nptr);
}

JNIEXPORT void JNICALL Java_org_gmplib_gmpjni_GMP_native_1mpz_1rrandomb
  (JNIEnv *env, jclass cl, jlong rop, jlong state, jlong n)
{
    mpz_t *ropptr = reinterpret_cast<mpz_t *>(rop);
    gmp_randstate_t *stateptr = reinterpret_cast<gmp_randstate_t *>(state);

    mpz_rrandomb(*ropptr, *stateptr, static_cast<unsigned long int>(n));
}
