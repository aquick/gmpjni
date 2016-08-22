package org.gmplib.gmpjni;

import android.util.Log;

public class GMP
{

    public static final long MAX_UINT = 0xFFFFFFFFL;
    public static final long UINT_MAX = 0xFFFFFFFFL;
    public static final long ULONG_MAX = 0xFFFFFFFFL;
    public static final int  LONG_MAX = 0x7FFFFFFF;

    // For tests
    public static native int GMP_LIMB_BITS();
    public static native int GMP_NAIL_BITS();
    public static native int GMP_NUMB_BITS();

    public static class GMPException extends Exception
    {
	private int code;

	public static final int INVALID_HANDLE = 1;
	public static final int PARAMETER_OUT_OF_RANGE = 2;
	public static final int OUT_OF_MEMORY = 3;
	public static final int BAD_FORMAT = 4;
	public static final int IO_ERROR = 5;

	public GMPException(int code, String msg)
	{
	    super(msg);
	    this.code = code;
	}

	public int getCode()
	{
	    return this.code;
	}
    }

    public static class mpz_t
    {
	public mpz_t() throws GMPException
	{
	    handle = init();
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public mpz_t(long n) throws GMPException
	{
	    checkUnsignedIntRange(n);
	    handle = init2(n);
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public void finalize()
	{
	    fini();
	    handle = 0;
	}

	protected long handle;

	private native long init();
	private native long init2(long n);

	private native void fini();
    }

    public static class mpq_t
    {
	public mpq_t() throws GMPException
	{
	    handle = init();
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public void finalize()
	{
	    fini();
	    handle = 0;
	}

	protected long handle;

	private native long init();

	private native void fini();
    }

    public static class mpf_t
    {
	public mpf_t() throws GMPException
	{
	    handle = init();
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public mpf_t(long precision) throws GMPException
	{
	    checkUnsignedIntRange(precision);
	    handle = init2(precision);
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public void finalize()
	{
	    fini();
	    handle = 0;
	}

	protected long handle;

	private native long init();
	private native long init2(long precision);

	private native void fini();
    }

    public static class randstate_t
    {
	public randstate_t(long seed) throws GMPException
	{
	    checkUnsignedIntRange(seed);
	    handle = init(seed);
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public randstate_t(mpz_t seed) throws GMPException
	{
	    handle = init2(seed.handle);
	    if (handle == 0) {
		throw new GMPException(GMPException.INVALID_HANDLE, "Invalid handle");
	    }
	}

	public void finalize()
	{
	    fini();
	    handle = 0;
	}

	protected long handle; // gmp_randstate_t

	private native long init(long seed);
	private native long init2(long hseed);

	private native void fini();
    }

    public static void init()
    {
	//System.loadLibrary("cygwin1");
	//System.loadLibrary("cyggcc_s-1");
	//System.loadLibrary("cyggmp-10");
	Log.d( "gmpjni", "loading native libs" );
	System.loadLibrary("gmp");
	System.loadLibrary("gmpjni");
    }

    private static void checkUnsignedIntRange(long y)
	throws GMPException
    {
	if (y < 0 || y > MAX_UINT) {
	    throw new GMPException(GMPException.PARAMETER_OUT_OF_RANGE, "Parameter out of range");
	}
    }

    public static class MutableInteger
    {
	public MutableInteger(int i) { value = i; }
	public int value;
    }

    /**********************************************************
     * String functions
     **********************************************************/
    private static native void native_mpz_set_str(long x, String str, int base);
    public static void mpz_set_str(mpz_t x, String str, int base)
	throws GMPException
    {
	native_mpz_set_str(x.handle, str, base);
    }

    private static native String native_mpz_get_str(long x, int base);
    public static String mpz_get_str(mpz_t x, int base)
	throws GMPException
    {
	return native_mpz_get_str(x.handle, base);
    }

    private static native void native_mpq_set_str(long x, String str, int base);
    public static void mpq_set_str(mpq_t x, String str, int base)
	throws GMPException
    {
	native_mpq_set_str(x.handle, str, base);
    }

    private static native String native_mpq_get_str(long x, int base);
    public static String mpq_get_str(mpq_t x, int base)
	throws GMPException
    {
	return native_mpq_get_str(x.handle, base);
    }

    private static native void native_mpf_set_str(long x, String str, int base);
    public static void mpf_set_str(mpf_t x, String str, int base)
	throws GMPException
    {
	native_mpf_set_str(x.handle, str, base);
    }

    private static native String native_gmp_version();
    public static String getVersion()
    {
	return native_gmp_version();
    }

    /**********************************************************
     * TODO
     **********************************************************/
    private static native double native_mpz_get_d_2exp(/*signed long int**/ MutableInteger exp, long op);
    public static double mpz_get_d_2exp(/*signed long int**/ MutableInteger exp, mpz_t op)
	throws GMPException
    {
	return native_mpz_get_d_2exp(exp, op.handle);
    }

    private static native double native_mpf_get_d_2exp(/*signed long int **/ MutableInteger exp, long op);
    public static double mpf_get_d_2exp(/*signed long int **/ MutableInteger exp, mpf_t op)
	throws GMPException
    {
	return native_mpf_get_d_2exp(exp, op.handle);
    }

    private static native String native_mpf_get_str(/*mp_exp_t **/ MutableInteger exp, int base, /*size_t*/ long n_digits, long op);
    public static String mpf_get_str(/*mp_exp_t **/ MutableInteger exp, int base, /*size_t*/ long n_digits, mpf_t op)
	throws GMPException
    {
	checkUnsignedIntRange(n_digits);
	return native_mpf_get_str(exp, base, n_digits, op.handle);
    }

    private static native long native_mpz_out_str(String filename, int base, long op);
    public static long mpz_out_str(String filename, int base, mpz_t op)
	throws GMPException
    {
	return native_mpz_out_str(filename, base, op.handle);
    }

    private static native long native_mpz_inp_str(long rop, String filename, int base);
    public static long mpz_inp_str(mpz_t rop, String filename, int base)
	throws GMPException
    {
	return native_mpz_inp_str(rop.handle, filename, base);
    }

    private static native long native_mpq_out_str(String filename, int base, long op);
    public static long mpq_out_str(String filename, int base, mpq_t op)
	throws GMPException
    {
	return native_mpq_out_str(filename, base, op.handle);
    }

    private static native long native_mpq_inp_str(long rop, String filename, int base);
    public static long mpq_inp_str(mpq_t rop, String filename, int base)
	throws GMPException
    {
	return native_mpq_inp_str(rop.handle, filename, base);
    }

    private static native long native_mpf_out_str(String filename, int base, long n_digits, long op);
    public static long mpf_out_str(String filename, int base, long n_digits, mpf_t op)
	throws GMPException
    {
	return native_mpf_out_str(filename, base, n_digits, op.handle);
    }

    private static native long native_mpf_inp_str(long rop, String filename, int base);
    public static long mpf_inp_str(mpf_t rop, String filename, int base)
	throws GMPException
    {
	return native_mpf_inp_str(rop.handle, filename, base);
    }

    private static native int native_refmpn_cmp(long x, long[] y, long size);
    public static int refmpn_cmp(mpz_t x, long[] y, long size)
	throws GMPException
    {
	checkUnsignedIntRange(size);
	return native_refmpn_cmp(x.handle, y, size);
    }

    public static int refmpn_cmp_allowzero(mpz_t x, long[] y, long size)
	throws GMPException
    {
	checkUnsignedIntRange(size);
	if (size == 0) {
	    return 0;
	} else {
	    return native_refmpn_cmp(x.handle, y, size);
	}
    }

    /**********************************************************
     * Auto-generated functions
     **********************************************************/

    private static native void native_mpz_set(long rop, long op);
    public static void mpz_set(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_set(rop.handle, op.handle);
    }

    private static native void native_mpz_set_ui(long rop, /*unsigned long int*/ long op);
    public static void mpz_set_ui(mpz_t rop, /*unsigned long int*/ long op)
	throws GMPException
    {
	checkUnsignedIntRange(op);
	native_mpz_set_ui(rop.handle, op);
    }

    private static native void native_mpz_set_si(long rop, /*signed long int*/ int op);
    public static void mpz_set_si(mpz_t rop, /*signed long int*/ int op)
	throws GMPException
    {
	native_mpz_set_si(rop.handle, op);
    }

    private static native void native_mpz_set_d(long rop, double op);
    public static void mpz_set_d(mpz_t rop, double op)
	throws GMPException
    {
	native_mpz_set_d(rop.handle, op);
    }

    private static native void native_mpz_set_q(long rop, long op);
    public static void mpz_set_q(mpz_t rop, mpq_t op)
	throws GMPException
    {
	native_mpz_set_q(rop.handle, op.handle);
    }

    private static native void native_mpz_set_f(long rop, long op);
    public static void mpz_set_f(mpz_t rop, mpf_t op)
	throws GMPException
    {
	native_mpz_set_f(rop.handle, op.handle);
    }

    private static native void native_mpz_swap(long rop1, long rop2);
    public static void mpz_swap(mpz_t rop1, mpz_t rop2)
	throws GMPException
    {
	native_mpz_swap(rop1.handle, rop2.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_get_ui(long op);
    public static /*unsigned long int*/ long mpz_get_ui(mpz_t op)
	throws GMPException
    {
	return native_mpz_get_ui(op.handle);
    }

    private static native /*signed long int*/ int native_mpz_get_si(long op);
    public static /*signed long int*/ int mpz_get_si(mpz_t op)
	throws GMPException
    {
	return native_mpz_get_si(op.handle);
    }

    private static native double native_mpz_get_d(long op);
    public static double mpz_get_d(mpz_t op)
	throws GMPException
    {
	return native_mpz_get_d(op.handle);
    }

    private static native void native_mpz_add(long rop, long op1, long op2);
    public static void mpz_add(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_add(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_add_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpz_add_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_add_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_sub(long rop, long op1, long op2);
    public static void mpz_sub(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_sub(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_sub_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpz_sub_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_sub_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_ui_sub(long rop, /*unsigned long int*/ long op1, long op2);
    public static void mpz_ui_sub(mpz_t rop, /*unsigned long int*/ long op1, mpz_t op2)
	throws GMPException
    {
	checkUnsignedIntRange(op1);
	native_mpz_ui_sub(rop.handle, op1, op2.handle);
    }

    private static native void native_mpz_mul(long rop, long op1, long op2);
    public static void mpz_mul(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_mul(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_mul_si(long rop, long op1, /*long int*/ int op2);
    public static void mpz_mul_si(mpz_t rop, mpz_t op1, /*long int*/ int op2)
	throws GMPException
    {
	native_mpz_mul_si(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_mul_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpz_mul_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_mul_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_addmul(long rop, long op1, long op2);
    public static void mpz_addmul(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_addmul(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_addmul_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpz_addmul_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_addmul_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_submul(long rop, long op1, long op2);
    public static void mpz_submul(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_submul(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_submul_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpz_submul_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_submul_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_mul_2exp(long rop, long op1, /*mp_bitcnt_t*/ long op2);
    public static void mpz_mul_2exp(mpz_t rop, mpz_t op1, /*mp_bitcnt_t*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_mul_2exp(rop.handle, op1.handle, op2);
    }

    private static native void native_mpz_neg(long rop, long op);
    public static void mpz_neg(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_neg(rop.handle, op.handle);
    }

    private static native void native_mpz_abs(long rop, long op);
    public static void mpz_abs(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_abs(rop.handle, op.handle);
    }

    private static native void native_mpz_cdiv_q(long q, long n, long d);
    public static void mpz_cdiv_q(mpz_t q, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_cdiv_q(q.handle, n.handle, d.handle);
    }

    private static native void native_mpz_cdiv_r(long r, long n, long d);
    public static void mpz_cdiv_r(mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_cdiv_r(r.handle, n.handle, d.handle);
    }

    private static native void native_mpz_cdiv_qr(long q, long r, long n, long d);
    public static void mpz_cdiv_qr(mpz_t q, mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_cdiv_qr(q.handle, r.handle, n.handle, d.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_cdiv_q_ui(long q, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_cdiv_q_ui(mpz_t q, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_cdiv_q_ui(q.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_cdiv_r_ui(long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_cdiv_r_ui(mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_cdiv_r_ui(r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_cdiv_qr_ui(long q, long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_cdiv_qr_ui(mpz_t q, mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_cdiv_qr_ui(q.handle, r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_cdiv_ui(long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_cdiv_ui(mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_cdiv_ui(n.handle, d);
    }

    private static native void native_mpz_cdiv_q_2exp(long q, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_cdiv_q_2exp(mpz_t q, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_cdiv_q_2exp(q.handle, n.handle, b);
    }

    private static native void native_mpz_cdiv_r_2exp(long r, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_cdiv_r_2exp(mpz_t r, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_cdiv_r_2exp(r.handle, n.handle, b);
    }

    private static native void native_mpz_fdiv_q(long q, long n, long d);
    public static void mpz_fdiv_q(mpz_t q, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_fdiv_q(q.handle, n.handle, d.handle);
    }

    private static native void native_mpz_fdiv_r(long r, long n, long d);
    public static void mpz_fdiv_r(mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_fdiv_r(r.handle, n.handle, d.handle);
    }

    private static native void native_mpz_fdiv_qr(long q, long r, long n, long d);
    public static void mpz_fdiv_qr(mpz_t q, mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_fdiv_qr(q.handle, r.handle, n.handle, d.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_fdiv_q_ui(long q, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_fdiv_q_ui(mpz_t q, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_fdiv_q_ui(q.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_fdiv_r_ui(long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_fdiv_r_ui(mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_fdiv_r_ui(r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_fdiv_qr_ui(long q, long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_fdiv_qr_ui(mpz_t q, mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_fdiv_qr_ui(q.handle, r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_fdiv_ui(long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_fdiv_ui(mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_fdiv_ui(n.handle, d);
    }

    private static native void native_mpz_fdiv_q_2exp(long q, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_fdiv_q_2exp(mpz_t q, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_fdiv_q_2exp(q.handle, n.handle, b);
    }

    private static native void native_mpz_fdiv_r_2exp(long r, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_fdiv_r_2exp(mpz_t r, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_fdiv_r_2exp(r.handle, n.handle, b);
    }

    private static native void native_mpz_tdiv_q(long q, long n, long d);
    public static void mpz_tdiv_q(mpz_t q, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_tdiv_q(q.handle, n.handle, d.handle);
    }

    private static native void native_mpz_tdiv_r(long r, long n, long d);
    public static void mpz_tdiv_r(mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_tdiv_r(r.handle, n.handle, d.handle);
    }

    private static native void native_mpz_tdiv_qr(long q, long r, long n, long d);
    public static void mpz_tdiv_qr(mpz_t q, mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_tdiv_qr(q.handle, r.handle, n.handle, d.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_tdiv_q_ui(long q, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_tdiv_q_ui(mpz_t q, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_tdiv_q_ui(q.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_tdiv_r_ui(long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_tdiv_r_ui(mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_tdiv_r_ui(r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_tdiv_qr_ui(long q, long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_tdiv_qr_ui(mpz_t q, mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_tdiv_qr_ui(q.handle, r.handle, n.handle, d);
    }

    private static native /*unsigned long int*/ long native_mpz_tdiv_ui(long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_tdiv_ui(mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_tdiv_ui(n.handle, d);
    }

    private static native void native_mpz_tdiv_q_2exp(long q, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_tdiv_q_2exp(mpz_t q, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_tdiv_q_2exp(q.handle, n.handle, b);
    }

    private static native void native_mpz_tdiv_r_2exp(long r, long n, /*mp_bitcnt_t*/ long b);
    public static void mpz_tdiv_r_2exp(mpz_t r, mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	native_mpz_tdiv_r_2exp(r.handle, n.handle, b);
    }

    private static native void native_mpz_mod(long r, long n, long d);
    public static void mpz_mod(mpz_t r, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_mod(r.handle, n.handle, d.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_mod_ui(long r, long n, /*unsigned long int*/ long d);
    public static /*unsigned long int*/ long mpz_mod_ui(mpz_t r, mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_mod_ui(r.handle, n.handle, d);
    }

    private static native void native_mpz_divexact(long q, long n, long d);
    public static void mpz_divexact(mpz_t q, mpz_t n, mpz_t d)
	throws GMPException
    {
	native_mpz_divexact(q.handle, n.handle, d.handle);
    }

    private static native void native_mpz_divexact_ui(long q, long n, /*unsigned long*/ long d);
    public static void mpz_divexact_ui(mpz_t q, mpz_t n, /*unsigned long*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	native_mpz_divexact_ui(q.handle, n.handle, d);
    }

    private static native int native_mpz_divisible_p(long n, long d);
    public static int mpz_divisible_p(mpz_t n, mpz_t d)
	throws GMPException
    {
	return native_mpz_divisible_p(n.handle, d.handle);
    }

    private static native int native_mpz_divisible_ui_p(long n, /*unsigned long int*/ long d);
    public static int mpz_divisible_ui_p(mpz_t n, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(d);
	return native_mpz_divisible_ui_p(n.handle, d);
    }

    private static native int native_mpz_divisible_2exp_p(long n, /*mp_bitcnt_t*/ long b);
    public static int mpz_divisible_2exp_p(mpz_t n, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	return native_mpz_divisible_2exp_p(n.handle, b);
    }

    private static native int native_mpz_congruent_p(long n, long c, long d);
    public static int mpz_congruent_p(mpz_t n, mpz_t c, mpz_t d)
	throws GMPException
    {
	return native_mpz_congruent_p(n.handle, c.handle, d.handle);
    }

    private static native int native_mpz_congruent_ui_p(long n, /*unsigned long int*/ long c, /*unsigned long int*/ long d);
    public static int mpz_congruent_ui_p(mpz_t n, /*unsigned long int*/ long c, /*unsigned long int*/ long d)
	throws GMPException
    {
	checkUnsignedIntRange(c);
	checkUnsignedIntRange(d);
	return native_mpz_congruent_ui_p(n.handle, c, d);
    }

    private static native int native_mpz_congruent_2exp_p(long n, long c, /*mp_bitcnt_t*/ long b);
    public static int mpz_congruent_2exp_p(mpz_t n, mpz_t c, /*mp_bitcnt_t*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	return native_mpz_congruent_2exp_p(n.handle, c.handle, b);
    }

    private static native void native_mpz_powm(long rop, long base, long exp, long mod);
    public static void mpz_powm(mpz_t rop, mpz_t base, mpz_t exp, mpz_t mod)
	throws GMPException
    {
	native_mpz_powm(rop.handle, base.handle, exp.handle, mod.handle);
    }

    private static native void native_mpz_powm_ui(long rop, long base, /*unsigned long int*/ long exp, long mod);
    public static void mpz_powm_ui(mpz_t rop, mpz_t base, /*unsigned long int*/ long exp, mpz_t mod)
	throws GMPException
    {
	checkUnsignedIntRange(exp);
	native_mpz_powm_ui(rop.handle, base.handle, exp, mod.handle);
    }

    private static native void native_mpz_powm_sec(long rop, long base, long exp, long mod);
    public static void mpz_powm_sec(mpz_t rop, mpz_t base, mpz_t exp, mpz_t mod)
	throws GMPException
    {
	native_mpz_powm_sec(rop.handle, base.handle, exp.handle, mod.handle);
    }

    private static native void native_mpz_pow_ui(long rop, long base, /*unsigned long int*/ long exp);
    public static void mpz_pow_ui(mpz_t rop, mpz_t base, /*unsigned long int*/ long exp)
	throws GMPException
    {
	checkUnsignedIntRange(exp);
	native_mpz_pow_ui(rop.handle, base.handle, exp);
    }

    private static native void native_mpz_ui_pow_ui(long rop, /*unsigned long int*/ long base, /*unsigned long int*/ long exp);
    public static void mpz_ui_pow_ui(mpz_t rop, /*unsigned long int*/ long base, /*unsigned long int*/ long exp)
	throws GMPException
    {
	checkUnsignedIntRange(base);
	checkUnsignedIntRange(exp);
	native_mpz_ui_pow_ui(rop.handle, base, exp);
    }

    private static native int native_mpz_root(long rop, long op, /*unsigned long int*/ long n);
    public static int mpz_root(mpz_t rop, mpz_t op, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	return native_mpz_root(rop.handle, op.handle, n);
    }

    private static native void native_mpz_rootrem(long root, long rem, long u, /*unsigned long int*/ long n);
    public static void mpz_rootrem(mpz_t root, mpz_t rem, mpz_t u, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_rootrem(root.handle, rem.handle, u.handle, n);
    }

    private static native void native_mpz_sqrt(long rop, long op);
    public static void mpz_sqrt(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_sqrt(rop.handle, op.handle);
    }

    private static native void native_mpz_sqrtrem(long rop1, long rop2, long op);
    public static void mpz_sqrtrem(mpz_t rop1, mpz_t rop2, mpz_t op)
	throws GMPException
    {
	native_mpz_sqrtrem(rop1.handle, rop2.handle, op.handle);
    }

    private static native int native_mpz_perfect_power_p(long op);
    public static int mpz_perfect_power_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_perfect_power_p(op.handle);
    }

    private static native int native_mpz_perfect_square_p(long op);
    public static int mpz_perfect_square_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_perfect_square_p(op.handle);
    }

    private static native int native_mpz_probab_prime_p(long n, int reps);
    public static int mpz_probab_prime_p(mpz_t n, int reps)
	throws GMPException
    {
	return native_mpz_probab_prime_p(n.handle, reps);
    }

    private static native void native_mpz_nextprime(long rop, long op);
    public static void mpz_nextprime(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_nextprime(rop.handle, op.handle);
    }

    private static native void native_mpz_gcd(long rop, long op1, long op2);
    public static void mpz_gcd(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_gcd(rop.handle, op1.handle, op2.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_gcd_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static /*unsigned long int*/ long mpz_gcd_ui(mpz_t rop, mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
        if (rop == null) {
	    return native_mpz_gcd_ui(0, op1.handle, op2);
        } else {
	    return native_mpz_gcd_ui(rop.handle, op1.handle, op2);
        }
    }

    private static native void native_mpz_gcdext(long g, long s, long t, long a, long b);
    public static void mpz_gcdext(mpz_t g, mpz_t s, mpz_t t, mpz_t a, mpz_t b)
	throws GMPException
    {
        if (t == null) {
	    native_mpz_gcdext(g.handle, s.handle, 0, a.handle, b.handle);
        } else {
	    native_mpz_gcdext(g.handle, s.handle, t.handle, a.handle, b.handle);
        }
    }

    private static native void native_mpz_lcm(long rop, long op1, long op2);
    public static void mpz_lcm(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_lcm(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_lcm_ui(long rop, long op1, /*unsigned long*/ long op2);
    public static void mpz_lcm_ui(mpz_t rop, mpz_t op1, /*unsigned long*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpz_lcm_ui(rop.handle, op1.handle, op2);
    }

    private static native int native_mpz_invert(long rop, long op1, long op2);
    public static int mpz_invert(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	return native_mpz_invert(rop.handle, op1.handle, op2.handle);
    }

    private static native int native_mpz_jacobi(long a, long b);
    public static int mpz_jacobi(mpz_t a, mpz_t b)
	throws GMPException
    {
	return native_mpz_jacobi(a.handle, b.handle);
    }

    private static native int native_mpz_legendre(long a, long p);
    public static int mpz_legendre(mpz_t a, mpz_t p)
	throws GMPException
    {
	return native_mpz_legendre(a.handle, p.handle);
    }

    private static native int native_mpz_kronecker(long a, long b);
    public static int mpz_kronecker(mpz_t a, mpz_t b)
	throws GMPException
    {
	return native_mpz_kronecker(a.handle, b.handle);
    }

    private static native int native_mpz_kronecker_si(long a, /*long*/ int b);
    public static int mpz_kronecker_si(mpz_t a, /*long*/ int b)
	throws GMPException
    {
	return native_mpz_kronecker_si(a.handle, b);
    }

    private static native int native_mpz_kronecker_ui(long a, /*unsigned long*/ long b);
    public static int mpz_kronecker_ui(mpz_t a, /*unsigned long*/ long b)
	throws GMPException
    {
	checkUnsignedIntRange(b);
	return native_mpz_kronecker_ui(a.handle, b);
    }

    private static native int native_mpz_si_kronecker(/*long*/ int a, long b);
    public static int mpz_si_kronecker(/*long*/ int a, mpz_t b)
	throws GMPException
    {
	return native_mpz_si_kronecker(a, b.handle);
    }

    private static native int native_mpz_ui_kronecker(/*unsigned long*/ long a, long b);
    public static int mpz_ui_kronecker(/*unsigned long*/ long a, mpz_t b)
	throws GMPException
    {
	checkUnsignedIntRange(a);
	return native_mpz_ui_kronecker(a, b.handle);
    }

    private static native /*mp_bitcnt_t*/ long native_mpz_remove(long rop, long op, long f);
    public static /*mp_bitcnt_t*/ long mpz_remove(mpz_t rop, mpz_t op, mpz_t f)
	throws GMPException
    {
	return native_mpz_remove(rop.handle, op.handle, f.handle);
    }

    private static native void native_mpz_fac_ui(long rop, /*unsigned long int*/ long n);
    public static void mpz_fac_ui(mpz_t rop, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_fac_ui(rop.handle, n);
    }

    private static native void native_mpz_2fac_ui(long rop, /*unsigned long int*/ long n);
    public static void mpz_2fac_ui(mpz_t rop, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_2fac_ui(rop.handle, n);
    }

    private static native void native_mpz_mfac_uiui(long rop, /*unsigned long int*/ long n, /*unsigned long int*/ long m);
    public static void mpz_mfac_uiui(mpz_t rop, /*unsigned long int*/ long n, /*unsigned long int*/ long m)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	checkUnsignedIntRange(m);
	native_mpz_mfac_uiui(rop.handle, n, m);
    }

    private static native void native_mpz_primorial_ui(long rop, /*unsigned long int*/ long n);
    public static void mpz_primorial_ui(mpz_t rop, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_primorial_ui(rop.handle, n);
    }

    private static native void native_mpz_bin_ui(long rop, long n, /*unsigned long int*/ long k);
    public static void mpz_bin_ui(mpz_t rop, mpz_t n, /*unsigned long int*/ long k)
	throws GMPException
    {
	checkUnsignedIntRange(k);
	native_mpz_bin_ui(rop.handle, n.handle, k);
    }

    private static native void native_mpz_bin_uiui(long rop, /*unsigned long int*/ long n, /*unsigned long int*/ long k);
    public static void mpz_bin_uiui(mpz_t rop, /*unsigned long int*/ long n, /*unsigned long int*/ long k)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	checkUnsignedIntRange(k);
	native_mpz_bin_uiui(rop.handle, n, k);
    }

    private static native void native_mpz_fib_ui(long fn, /*unsigned long int*/ long n);
    public static void mpz_fib_ui(mpz_t fn, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_fib_ui(fn.handle, n);
    }

    private static native void native_mpz_fib2_ui(long fn, long fnsub1, /*unsigned long int*/ long n);
    public static void mpz_fib2_ui(mpz_t fn, mpz_t fnsub1, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_fib2_ui(fn.handle, fnsub1.handle, n);
    }

    private static native void native_mpz_lucnum_ui(long ln, /*unsigned long int*/ long n);
    public static void mpz_lucnum_ui(mpz_t ln, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_lucnum_ui(ln.handle, n);
    }

    private static native void native_mpz_lucnum2_ui(long ln, long lnsub1, /*unsigned long int*/ long n);
    public static void mpz_lucnum2_ui(mpz_t ln, mpz_t lnsub1, /*unsigned long int*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_lucnum2_ui(ln.handle, lnsub1.handle, n);
    }

    private static native int native_mpz_cmp(long op1, long op2);
    public static int mpz_cmp(mpz_t op1, mpz_t op2)
	throws GMPException
    {
	return native_mpz_cmp(op1.handle, op2.handle);
    }

    private static native int native_mpz_cmp_d(long op1, double op2);
    public static int mpz_cmp_d(mpz_t op1, double op2)
	throws GMPException
    {
	return native_mpz_cmp_d(op1.handle, op2);
    }

    private static native int native_mpz_cmp_si(long op1, /*signed long int*/ int op2);
    public static int mpz_cmp_si(mpz_t op1, /*signed long int*/ int op2)
	throws GMPException
    {
	return native_mpz_cmp_si(op1.handle, op2);
    }

    private static native int native_mpz_cmp_ui(long op1, /*unsigned long int*/ long op2);
    public static int mpz_cmp_ui(mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	return native_mpz_cmp_ui(op1.handle, op2);
    }

    private static native int native_mpz_cmpabs(long op1, long op2);
    public static int mpz_cmpabs(mpz_t op1, mpz_t op2)
	throws GMPException
    {
	return native_mpz_cmpabs(op1.handle, op2.handle);
    }

    private static native int native_mpz_cmpabs_d(long op1, double op2);
    public static int mpz_cmpabs_d(mpz_t op1, double op2)
	throws GMPException
    {
	return native_mpz_cmpabs_d(op1.handle, op2);
    }

    private static native int native_mpz_cmpabs_ui(long op1, /*unsigned long int*/ long op2);
    public static int mpz_cmpabs_ui(mpz_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	return native_mpz_cmpabs_ui(op1.handle, op2);
    }

    private static native int native_mpz_sgn(long op);
    public static int mpz_sgn(mpz_t op)
	throws GMPException
    {
	return native_mpz_sgn(op.handle);
    }

    private static native void native_mpz_and(long rop, long op1, long op2);
    public static void mpz_and(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_and(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_ior(long rop, long op1, long op2);
    public static void mpz_ior(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_ior(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_xor(long rop, long op1, long op2);
    public static void mpz_xor(mpz_t rop, mpz_t op1, mpz_t op2)
	throws GMPException
    {
	native_mpz_xor(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpz_com(long rop, long op);
    public static void mpz_com(mpz_t rop, mpz_t op)
	throws GMPException
    {
	native_mpz_com(rop.handle, op.handle);
    }

    private static native /*mp_bitcnt_t*/ long native_mpz_popcount(long op);
    public static /*mp_bitcnt_t*/ long mpz_popcount(mpz_t op)
	throws GMPException
    {
	return native_mpz_popcount(op.handle);
    }

    private static native /*mp_bitcnt_t*/ long native_mpz_hamdist(long op1, long op2);
    public static /*mp_bitcnt_t*/ long mpz_hamdist(mpz_t op1, mpz_t op2)
	throws GMPException
    {
	return native_mpz_hamdist(op1.handle, op2.handle);
    }

    private static native /*mp_bitcnt_t*/ long native_mpz_scan0(long op, /*mp_bitcnt_t*/ long starting_bit);
    public static /*mp_bitcnt_t*/ long mpz_scan0(mpz_t op, /*mp_bitcnt_t*/ long starting_bit)
	throws GMPException
    {
	checkUnsignedIntRange(starting_bit);
	return native_mpz_scan0(op.handle, starting_bit);
    }

    private static native /*mp_bitcnt_t*/ long native_mpz_scan1(long op, /*mp_bitcnt_t*/ long starting_bit);
    public static /*mp_bitcnt_t*/ long mpz_scan1(mpz_t op, /*mp_bitcnt_t*/ long starting_bit)
	throws GMPException
    {
	checkUnsignedIntRange(starting_bit);
	return native_mpz_scan1(op.handle, starting_bit);
    }

    private static native void native_mpz_setbit(long rop, /*mp_bitcnt_t*/ long bit_index);
    public static void mpz_setbit(mpz_t rop, /*mp_bitcnt_t*/ long bit_index)
	throws GMPException
    {
	checkUnsignedIntRange(bit_index);
	native_mpz_setbit(rop.handle, bit_index);
    }

    private static native void native_mpz_clrbit(long rop, /*mp_bitcnt_t*/ long bit_index);
    public static void mpz_clrbit(mpz_t rop, /*mp_bitcnt_t*/ long bit_index)
	throws GMPException
    {
	checkUnsignedIntRange(bit_index);
	native_mpz_clrbit(rop.handle, bit_index);
    }

    private static native void native_mpz_combit(long rop, /*mp_bitcnt_t*/ long bit_index);
    public static void mpz_combit(mpz_t rop, /*mp_bitcnt_t*/ long bit_index)
	throws GMPException
    {
	checkUnsignedIntRange(bit_index);
	native_mpz_combit(rop.handle, bit_index);
    }

    private static native int native_mpz_tstbit(long op, /*mp_bitcnt_t*/ long bit_index);
    public static int mpz_tstbit(mpz_t op, /*mp_bitcnt_t*/ long bit_index)
	throws GMPException
    {
	checkUnsignedIntRange(bit_index);
	return native_mpz_tstbit(op.handle, bit_index);
    }

    private static native int native_mpz_fits_ulong_p(long op);
    public static int mpz_fits_ulong_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_ulong_p(op.handle);
    }

    private static native int native_mpz_fits_slong_p(long op);
    public static int mpz_fits_slong_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_slong_p(op.handle);
    }

    private static native int native_mpz_fits_uint_p(long op);
    public static int mpz_fits_uint_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_uint_p(op.handle);
    }

    private static native int native_mpz_fits_sint_p(long op);
    public static int mpz_fits_sint_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_sint_p(op.handle);
    }

    private static native int native_mpz_fits_ushort_p(long op);
    public static int mpz_fits_ushort_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_ushort_p(op.handle);
    }

    private static native int native_mpz_fits_sshort_p(long op);
    public static int mpz_fits_sshort_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_fits_sshort_p(op.handle);
    }

    private static native int native_mpz_odd_p(long op);
    public static int mpz_odd_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_odd_p(op.handle);
    }

    private static native int native_mpz_even_p(long op);
    public static int mpz_even_p(mpz_t op)
	throws GMPException
    {
	return native_mpz_even_p(op.handle);
    }

    private static native /*size_t*/ long native_mpz_sizeinbase(long op, int base);
    public static /*size_t*/ long mpz_sizeinbase(mpz_t op, int base)
	throws GMPException
    {
	return native_mpz_sizeinbase(op.handle, base);
    }

    private static native /*mp_limb_t*/ long native_mpz_getlimbn(long op, /*mp_size_t*/ int n);
    public static /*mp_limb_t*/ long mpz_getlimbn(mpz_t op, /*mp_size_t*/ int n)
	throws GMPException
    {
	return native_mpz_getlimbn(op.handle, n);
    }

    private static native /*size_t*/ long native_mpz_size(long op);
    public static /*size_t*/ long mpz_size(mpz_t op)
	throws GMPException
    {
	return native_mpz_size(op.handle);
    }

    private static native void native_mpq_canonicalize(long op);
    public static void mpq_canonicalize(mpq_t op)
	throws GMPException
    {
	native_mpq_canonicalize(op.handle);
    }

    private static native void native_mpq_set(long rop, long op);
    public static void mpq_set(mpq_t rop, mpq_t op)
	throws GMPException
    {
	native_mpq_set(rop.handle, op.handle);
    }

    private static native void native_mpq_set_z(long rop, long op);
    public static void mpq_set_z(mpq_t rop, mpz_t op)
	throws GMPException
    {
	native_mpq_set_z(rop.handle, op.handle);
    }

    private static native void native_mpq_set_ui(long rop, /*unsigned long int*/ long op1, /*unsigned long int*/ long op2);
    public static void mpq_set_ui(mpq_t rop, /*unsigned long int*/ long op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op1);
	checkUnsignedIntRange(op2);
	native_mpq_set_ui(rop.handle, op1, op2);
    }

    private static native void native_mpq_set_si(long rop, /*signed long int*/ int op1, /*unsigned long int*/ long op2);
    public static void mpq_set_si(mpq_t rop, /*signed long int*/ int op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpq_set_si(rop.handle, op1, op2);
    }

    private static native void native_mpq_swap(long rop1, long rop2);
    public static void mpq_swap(mpq_t rop1, mpq_t rop2)
	throws GMPException
    {
	native_mpq_swap(rop1.handle, rop2.handle);
    }

    private static native double native_mpq_get_d(long op);
    public static double mpq_get_d(mpq_t op)
	throws GMPException
    {
	return native_mpq_get_d(op.handle);
    }

    private static native void native_mpq_set_d(long rop, double op);
    public static void mpq_set_d(mpq_t rop, double op)
	throws GMPException
    {
	native_mpq_set_d(rop.handle, op);
    }

    private static native void native_mpq_set_f(long rop, long op);
    public static void mpq_set_f(mpq_t rop, mpf_t op)
	throws GMPException
    {
	native_mpq_set_f(rop.handle, op.handle);
    }

    private static native void native_mpq_add(long sum, long addend1, long addend2);
    public static void mpq_add(mpq_t sum, mpq_t addend1, mpq_t addend2)
	throws GMPException
    {
	native_mpq_add(sum.handle, addend1.handle, addend2.handle);
    }

    private static native void native_mpq_sub(long difference, long minuend, long subtrahend);
    public static void mpq_sub(mpq_t difference, mpq_t minuend, mpq_t subtrahend)
	throws GMPException
    {
	native_mpq_sub(difference.handle, minuend.handle, subtrahend.handle);
    }

    private static native void native_mpq_mul(long product, long multiplier, long multiplicand);
    public static void mpq_mul(mpq_t product, mpq_t multiplier, mpq_t multiplicand)
	throws GMPException
    {
	native_mpq_mul(product.handle, multiplier.handle, multiplicand.handle);
    }

    private static native void native_mpq_mul_2exp(long rop, long op1, /*mp_bitcnt_t*/ long op2);
    public static void mpq_mul_2exp(mpq_t rop, mpq_t op1, /*mp_bitcnt_t*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpq_mul_2exp(rop.handle, op1.handle, op2);
    }

    private static native void native_mpq_div(long quotient, long dividend, long divisor);
    public static void mpq_div(mpq_t quotient, mpq_t dividend, mpq_t divisor)
	throws GMPException
    {
	native_mpq_div(quotient.handle, dividend.handle, divisor.handle);
    }

    private static native void native_mpq_div_2exp(long rop, long op1, /*mp_bitcnt_t*/ long op2);
    public static void mpq_div_2exp(mpq_t rop, mpq_t op1, /*mp_bitcnt_t*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpq_div_2exp(rop.handle, op1.handle, op2);
    }

    private static native void native_mpq_neg(long negated_operand, long operand);
    public static void mpq_neg(mpq_t negated_operand, mpq_t operand)
	throws GMPException
    {
	native_mpq_neg(negated_operand.handle, operand.handle);
    }

    private static native void native_mpq_abs(long rop, long op);
    public static void mpq_abs(mpq_t rop, mpq_t op)
	throws GMPException
    {
	native_mpq_abs(rop.handle, op.handle);
    }

    private static native void native_mpq_inv(long inverted_number, long number);
    public static void mpq_inv(mpq_t inverted_number, mpq_t number)
	throws GMPException
    {
	native_mpq_inv(inverted_number.handle, number.handle);
    }

    private static native int native_mpq_cmp(long op1, long op2);
    public static int mpq_cmp(mpq_t op1, mpq_t op2)
	throws GMPException
    {
	return native_mpq_cmp(op1.handle, op2.handle);
    }

    private static native int native_mpq_cmp_ui(long op1, /*unsigned long int*/ long num2, /*unsigned long int*/ long den2);
    public static int mpq_cmp_ui(mpq_t op1, /*unsigned long int*/ long num2, /*unsigned long int*/ long den2)
	throws GMPException
    {
	checkUnsignedIntRange(num2);
	checkUnsignedIntRange(den2);
	return native_mpq_cmp_ui(op1.handle, num2, den2);
    }

    private static native int native_mpq_cmp_si(long op1, /*long int*/ int num2, /*unsigned long int*/ long den2);
    public static int mpq_cmp_si(mpq_t op1, /*long int*/ int num2, /*unsigned long int*/ long den2)
	throws GMPException
    {
	checkUnsignedIntRange(den2);
	return native_mpq_cmp_si(op1.handle, num2, den2);
    }

    private static native int native_mpq_cmp_z(long op1, long op2);
    public static int mpq_cmp_z(mpq_t op1, mpz_t op2)
	throws GMPException
    {
	return native_mpq_cmp_z(op1.handle, op2.handle);
    }

    private static native int native_mpq_sgn(long op);
    public static int mpq_sgn(mpq_t op)
	throws GMPException
    {
	return native_mpq_sgn(op.handle);
    }

    private static native int native_mpq_equal(long op1, long op2);
    public static int mpq_equal(mpq_t op1, mpq_t op2)
	throws GMPException
    {
	return native_mpq_equal(op1.handle, op2.handle);
    }

    private static native void native_mpq_get_num(long numerator, long rational);
    public static void mpq_get_num(mpz_t numerator, mpq_t rational)
	throws GMPException
    {
	native_mpq_get_num(numerator.handle, rational.handle);
    }

    private static native void native_mpq_get_den(long denominator, long rational);
    public static void mpq_get_den(mpz_t denominator, mpq_t rational)
	throws GMPException
    {
	native_mpq_get_den(denominator.handle, rational.handle);
    }

    private static native void native_mpq_set_num(long rational, long numerator);
    public static void mpq_set_num(mpq_t rational, mpz_t numerator)
	throws GMPException
    {
	native_mpq_set_num(rational.handle, numerator.handle);
    }

    private static native void native_mpq_set_den(long rational, long denominator);
    public static void mpq_set_den(mpq_t rational, mpz_t denominator)
	throws GMPException
    {
	native_mpq_set_den(rational.handle, denominator.handle);
    }

    private static native void native_mpf_set_default_prec(/*mp_bitcnt_t*/ long prec);
    public static void mpf_set_default_prec(/*mp_bitcnt_t*/ long prec)
	throws GMPException
    {
	checkUnsignedIntRange(prec);
	native_mpf_set_default_prec(prec);
    }

    private static native /*mp_bitcnt_t*/ long native_mpf_get_default_prec();
    public static /*mp_bitcnt_t*/ long mpf_get_default_prec()
	throws GMPException
    {
	return native_mpf_get_default_prec();
    }

    private static native /*mp_bitcnt_t*/ long native_mpf_get_prec(long op);
    public static /*mp_bitcnt_t*/ long mpf_get_prec(mpf_t op)
	throws GMPException
    {
	return native_mpf_get_prec(op.handle);
    }

    private static native void native_mpf_set_prec(long rop, /*mp_bitcnt_t*/ long prec);
    public static void mpf_set_prec(mpf_t rop, /*mp_bitcnt_t*/ long prec)
	throws GMPException
    {
	checkUnsignedIntRange(prec);
	native_mpf_set_prec(rop.handle, prec);
    }

    private static native void native_mpf_set_prec_raw(long rop, /*mp_bitcnt_t*/ long prec);
    public static void mpf_set_prec_raw(mpf_t rop, /*mp_bitcnt_t*/ long prec)
	throws GMPException
    {
	checkUnsignedIntRange(prec);
	native_mpf_set_prec_raw(rop.handle, prec);
    }

    private static native void native_mpf_set(long rop, long op);
    public static void mpf_set(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_set(rop.handle, op.handle);
    }

    private static native void native_mpf_set_ui(long rop, /*unsigned long int*/ long op);
    public static void mpf_set_ui(mpf_t rop, /*unsigned long int*/ long op)
	throws GMPException
    {
	checkUnsignedIntRange(op);
	native_mpf_set_ui(rop.handle, op);
    }

    private static native void native_mpf_set_si(long rop, /*signed long int*/ int op);
    public static void mpf_set_si(mpf_t rop, /*signed long int*/ int op)
	throws GMPException
    {
	native_mpf_set_si(rop.handle, op);
    }

    private static native void native_mpf_set_d(long rop, double op);
    public static void mpf_set_d(mpf_t rop, double op)
	throws GMPException
    {
	native_mpf_set_d(rop.handle, op);
    }

    private static native void native_mpf_set_z(long rop, long op);
    public static void mpf_set_z(mpf_t rop, mpz_t op)
	throws GMPException
    {
	native_mpf_set_z(rop.handle, op.handle);
    }

    private static native void native_mpf_set_q(long rop, long op);
    public static void mpf_set_q(mpf_t rop, mpq_t op)
	throws GMPException
    {
	native_mpf_set_q(rop.handle, op.handle);
    }

    private static native void native_mpf_swap(long rop1, long rop2);
    public static void mpf_swap(mpf_t rop1, mpf_t rop2)
	throws GMPException
    {
	native_mpf_swap(rop1.handle, rop2.handle);
    }

    private static native double native_mpf_get_d(long op);
    public static double mpf_get_d(mpf_t op)
	throws GMPException
    {
	return native_mpf_get_d(op.handle);
    }

    private static native /*long*/ int native_mpf_get_si(long op);
    public static /*long*/ int mpf_get_si(mpf_t op)
	throws GMPException
    {
	return native_mpf_get_si(op.handle);
    }

    private static native /*unsigned long*/ long native_mpf_get_ui(long op);
    public static /*unsigned long*/ long mpf_get_ui(mpf_t op)
	throws GMPException
    {
	return native_mpf_get_ui(op.handle);
    }

    private static native void native_mpf_add(long rop, long op1, long op2);
    public static void mpf_add(mpf_t rop, mpf_t op1, mpf_t op2)
	throws GMPException
    {
	native_mpf_add(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpf_add_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpf_add_ui(mpf_t rop, mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_add_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_sub(long rop, long op1, long op2);
    public static void mpf_sub(mpf_t rop, mpf_t op1, mpf_t op2)
	throws GMPException
    {
	native_mpf_sub(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpf_ui_sub(long rop, /*unsigned long int*/ long op1, long op2);
    public static void mpf_ui_sub(mpf_t rop, /*unsigned long int*/ long op1, mpf_t op2)
	throws GMPException
    {
	checkUnsignedIntRange(op1);
	native_mpf_ui_sub(rop.handle, op1, op2.handle);
    }

    private static native void native_mpf_sub_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpf_sub_ui(mpf_t rop, mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_sub_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_mul(long rop, long op1, long op2);
    public static void mpf_mul(mpf_t rop, mpf_t op1, mpf_t op2)
	throws GMPException
    {
	native_mpf_mul(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpf_mul_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpf_mul_ui(mpf_t rop, mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_mul_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_div(long rop, long op1, long op2);
    public static void mpf_div(mpf_t rop, mpf_t op1, mpf_t op2)
	throws GMPException
    {
	native_mpf_div(rop.handle, op1.handle, op2.handle);
    }

    private static native void native_mpf_ui_div(long rop, /*unsigned long int*/ long op1, long op2);
    public static void mpf_ui_div(mpf_t rop, /*unsigned long int*/ long op1, mpf_t op2)
	throws GMPException
    {
	checkUnsignedIntRange(op1);
	native_mpf_ui_div(rop.handle, op1, op2.handle);
    }

    private static native void native_mpf_div_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpf_div_ui(mpf_t rop, mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_div_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_sqrt(long rop, long op);
    public static void mpf_sqrt(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_sqrt(rop.handle, op.handle);
    }

    private static native void native_mpf_sqrt_ui(long rop, /*unsigned long int*/ long op);
    public static void mpf_sqrt_ui(mpf_t rop, /*unsigned long int*/ long op)
	throws GMPException
    {
	checkUnsignedIntRange(op);
	native_mpf_sqrt_ui(rop.handle, op);
    }

    private static native void native_mpf_pow_ui(long rop, long op1, /*unsigned long int*/ long op2);
    public static void mpf_pow_ui(mpf_t rop, mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_pow_ui(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_neg(long rop, long op);
    public static void mpf_neg(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_neg(rop.handle, op.handle);
    }

    private static native void native_mpf_abs(long rop, long op);
    public static void mpf_abs(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_abs(rop.handle, op.handle);
    }

    private static native void native_mpf_mul_2exp(long rop, long op1, /*mp_bitcnt_t*/ long op2);
    public static void mpf_mul_2exp(mpf_t rop, mpf_t op1, /*mp_bitcnt_t*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_mul_2exp(rop.handle, op1.handle, op2);
    }

    private static native void native_mpf_div_2exp(long rop, long op1, /*mp_bitcnt_t*/ long op2);
    public static void mpf_div_2exp(mpf_t rop, mpf_t op1, /*mp_bitcnt_t*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	native_mpf_div_2exp(rop.handle, op1.handle, op2);
    }

    private static native int native_mpf_cmp(long op1, long op2);
    public static int mpf_cmp(mpf_t op1, mpf_t op2)
	throws GMPException
    {
	return native_mpf_cmp(op1.handle, op2.handle);
    }

    private static native int native_mpf_cmp_d(long op1, double op2);
    public static int mpf_cmp_d(mpf_t op1, double op2)
	throws GMPException
    {
	return native_mpf_cmp_d(op1.handle, op2);
    }

    private static native int native_mpf_cmp_ui(long op1, /*unsigned long int*/ long op2);
    public static int mpf_cmp_ui(mpf_t op1, /*unsigned long int*/ long op2)
	throws GMPException
    {
	checkUnsignedIntRange(op2);
	return native_mpf_cmp_ui(op1.handle, op2);
    }

    private static native int native_mpf_cmp_si(long op1, /*signed long int*/ int op2);
    public static int mpf_cmp_si(mpf_t op1, /*signed long int*/ int op2)
	throws GMPException
    {
	return native_mpf_cmp_si(op1.handle, op2);
    }

    private static native int native_mpf_eq(long op1, long op2, /*mp_bitcnt_t*/ long op3);
    public static int mpf_eq(mpf_t op1, mpf_t op2, /*mp_bitcnt_t*/ long op3)
	throws GMPException
    {
	checkUnsignedIntRange(op3);
	return native_mpf_eq(op1.handle, op2.handle, op3);
    }

    private static native void native_mpf_reldiff(long rop, long op1, long op2);
    public static void mpf_reldiff(mpf_t rop, mpf_t op1, mpf_t op2)
	throws GMPException
    {
	native_mpf_reldiff(rop.handle, op1.handle, op2.handle);
    }

    private static native int native_mpf_sgn(long op);
    public static int mpf_sgn(mpf_t op)
	throws GMPException
    {
	return native_mpf_sgn(op.handle);
    }

    private static native void native_mpf_ceil(long rop, long op);
    public static void mpf_ceil(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_ceil(rop.handle, op.handle);
    }

    private static native void native_mpf_floor(long rop, long op);
    public static void mpf_floor(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_floor(rop.handle, op.handle);
    }

    private static native void native_mpf_trunc(long rop, long op);
    public static void mpf_trunc(mpf_t rop, mpf_t op)
	throws GMPException
    {
	native_mpf_trunc(rop.handle, op.handle);
    }

    private static native int native_mpf_integer_p(long op);
    public static int mpf_integer_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_integer_p(op.handle);
    }

    private static native int native_mpf_fits_ulong_p(long op);
    public static int mpf_fits_ulong_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_ulong_p(op.handle);
    }

    private static native int native_mpf_fits_slong_p(long op);
    public static int mpf_fits_slong_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_slong_p(op.handle);
    }

    private static native int native_mpf_fits_uint_p(long op);
    public static int mpf_fits_uint_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_uint_p(op.handle);
    }

    private static native int native_mpf_fits_sint_p(long op);
    public static int mpf_fits_sint_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_sint_p(op.handle);
    }

    private static native int native_mpf_fits_ushort_p(long op);
    public static int mpf_fits_ushort_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_ushort_p(op.handle);
    }

    private static native int native_mpf_fits_sshort_p(long op);
    public static int mpf_fits_sshort_p(mpf_t op)
	throws GMPException
    {
	return native_mpf_fits_sshort_p(op.handle);
    }

    private static native /*unsigned long*/ long native_gmp_urandomb_ui(long state, /*unsigned long*/ long n);
    public static /*unsigned long*/ long gmp_urandomb_ui(randstate_t state, /*unsigned long*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	return native_gmp_urandomb_ui(state.handle, n);
    }

    private static native /*unsigned long*/ long native_gmp_urandomm_ui(long state, /*unsigned long*/ long n);
    public static /*unsigned long*/ long gmp_urandomm_ui(randstate_t state, /*unsigned long*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	return native_gmp_urandomm_ui(state.handle, n);
    }

    private static native void native_mpz_urandomb(long rop, long state, /*mp_bitcnt_t*/ long n);
    public static void mpz_urandomb(mpz_t rop, randstate_t state, /*mp_bitcnt_t*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_urandomb(rop.handle, state.handle, n);
    }

    private static native void native_mpz_urandomm(long rop, long state, long n);
    public static void mpz_urandomm(mpz_t rop, randstate_t state, mpz_t n)
	throws GMPException
    {
	native_mpz_urandomm(rop.handle, state.handle, n.handle);
    }

    private static native void native_mpz_rrandomb(long rop, long state, /*mp_bitcnt_t*/ long n);
    public static void mpz_rrandomb(mpz_t rop, randstate_t state, /*mp_bitcnt_t*/ long n)
	throws GMPException
    {
	checkUnsignedIntRange(n);
	native_mpz_rrandomb(rop.handle, state.handle, n);
    }

    private static native int native_mpz_internal_SIZ(long z);
    public static int mpz_internal_SIZ(mpz_t z)
	throws GMPException
    {
	return native_mpz_internal_SIZ(z.handle);
    }

    private static native void native_mpz_internal_SETSIZ(long z, int size);
    public static void mpz_internal_SETSIZ(mpz_t z, int size)
	throws GMPException
    {
	native_mpz_internal_SETSIZ(z.handle, size);
    }

    private static native int native_mpz_internal_ABSIZ(long z);
    public static int mpz_internal_ABSIZ(mpz_t z)
	throws GMPException
    {
	return native_mpz_internal_ABSIZ(z.handle);
    }

    private static native int native_mpz_internal_ALLOC(long z);
    public static int mpz_internal_ALLOC(mpz_t z)
	throws GMPException
    {
	return native_mpz_internal_ALLOC(z.handle);
    }

    private static native void native_mpz_internal_REALLOC(long z, int amount);
    public static void mpz_internal_REALLOC(mpz_t z, int amount)
	throws GMPException
    {
	native_mpz_internal_REALLOC(z.handle, amount);
    }

    private static native void native_mpz_internal_CHECK_FORMAT(long z);
    public static void mpz_internal_CHECK_FORMAT(mpz_t z)
	throws GMPException
    {
	native_mpz_internal_CHECK_FORMAT(z.handle);
    }

    private static native void native_mpq_internal_CHECK_FORMAT(long z);
    public static void mpq_internal_CHECK_FORMAT(mpq_t z)
	throws GMPException
    {
	native_mpq_internal_CHECK_FORMAT(z.handle);
    }

    private static native /*unsigned long int*/ long native_mpz_internal_get_ulimb(long z, int index);
    public static /*unsigned long int*/ long mpz_internal_get_ulimb(mpz_t z, int index)
	throws GMPException
    {
	return native_mpz_internal_get_ulimb(z.handle, index);
    }

    private static native void native_mpz_internal_set_ulimb(long z, int index, /*unsigned long int*/ long value);
    public static void mpz_internal_set_ulimb(mpz_t z, int index, /*unsigned long int*/ long value)
	throws GMPException
    {
	checkUnsignedIntRange(value);
	native_mpz_internal_set_ulimb(z.handle, index, value);
    }

    /***
    public void main(String args[])
    {
	try {
	    System.out.println("start");
	    GMP.mpz_t z = new GMP.mpz_t();
	    GMP.mpz_t x = new GMP.mpz_t();
	    GMP.mpz_t y = new GMP.mpz_t();
	    System.out.println("mpz_t's allocated");
	    GMP.mpz_set_si(x, 3);
	    GMP.mpz_set_si(y, 11);
	    System.out.println("vars set");
	    GMP.mpz_add(z, x, y);
	    System.out.println("done");
	}
	catch (Exception e) {
	    System.out.println(e.toString());
	}
    }
    ***/
}
