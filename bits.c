/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {

    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x){
        return !y;
    }
    else if (!y){
        return !x;
    }
    else{
        return !((x >> 31) ^ (y >> 31));
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int res=0;
    int s;
    s = (v >> 16 > 0) <<4;
    res = res | s;
    v = v >> s;
    s = (v >> 8 > 0) <<3;
    res = res | s;
    v = v >> s;
    s = (v >> 4 > 0) <<2;
    res = res | s;
    v = v >> s;
    s = (v >> 2 > 0) <<1;
    res = res | s;
    v = v >> s;
    s = (v >> 1 > 0);
    res = res | s;
    return res;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int shift1 = n << 3;
    int shift2 = m << 3;
    int dif = ((x >> shift1) ^ (x >> shift2)) & 0xFF;
    /* Unsigned shift intermediates allow a byte to reach bit 31 safely. */
    return x ^ ((dif & 0xFFu) << shift1) ^ ((dif & 0xFFu) << shift2);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned num1 = 0x55555555u;
    unsigned num2 = 0x33333333u;
    unsigned num3 = 0x0F0F0F0Fu;
    unsigned num4 = 0x00FF00FFu;
    v = (v & num1)<<1 | (v>>1 & num1);
    v = (v & num2)<<2 | (v>>2 & num2);
    v = (v & num3)<<4 | (v>>4 & num3);
    v = (v & num4)<<8 | (v>>8 & num4);
    v = (v << 16) | (v >> 16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    /* n - !!n is zero for n == 0, otherwise n - 1. */
    int nonzero = !!n;
    int isZero = !n;
    int shift = n + ~nonzero + 1;
    int mask = 0x7FFFFFFF >> shift;
    int zeroMask = ~isZero + 1;
    return ((x >> n) & mask) | (x & zeroMask);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    /* Locate the highest 1 in ~x using right shifts only. */
    int v = ~x;
    int isZero = !v;
    int sum = 0;
    int shift;

    shift = !!(v >> 16) << 4;
    sum = sum + shift;
    v = v >> shift;
    shift = !!(v >> 8) << 3;
    sum = sum + shift;
    v = v >> shift;
    shift = !!(v >> 4) << 2;
    sum = sum + shift;
    v = v >> shift;
    shift = !!(v >> 2) << 1;
    sum = sum + shift;
    v = v >> shift;
    sum = sum + !!(v >> 1);

    /* 31 - sum, with one extra bit when x is all ones. */
    return 32 + ~sum + isZero;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned exp, frac,sign,abs_x;
    int shift,drop,num1,num2,num3;
    if (x == ~0x7FFFFFFF){
        return 0xCF000000;
    }
    if (x==0){
        return 0;
    }
    if (x > 0){
        abs_x=x;
        sign=0;
    }
    else {
        abs_x=-x;
        sign=0x80000000;
    }
    shift = 0;
    while (abs_x >> shift >1){
        shift = shift + 1;
    }
    exp = (shift+127)<<23;
    if (shift < 24){
        frac = abs_x<<(23-shift) & 0x7FFFFF;
    }
    else {
        drop= shift - 23;
        frac = abs_x >> drop & 0x7FFFFF;
        num1 = (abs_x >> (drop - 1)) & 1;
        num2 = abs_x & ((1 << (drop-1)) -1);
        num3 = frac & 1;
        /* Guard bit plus sticky/retained-low-bit implements ties-to-even. */
        if (num1){
            if (num2 | num3){
                frac = frac+1;
            }
        }
    }
    return sign + exp + frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign= uf & 0x80000000u;
    unsigned exp = uf >> 23 & 0xFF;
    if (exp == 0xFF){
        return uf;
    }
    if (exp == 0){
        return (sign | (uf << 1));
    }
    exp = exp+1;
    if (exp == 0xFF){
        return (sign | 0xFF << 23);
    }
    else{
        return (sign | exp << 23 | (uf & 0x7FFFFF));
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    int exp,E,val;
    sign = uf2>>31 & 1;
    exp = uf2 >> 20 & 0x7FF;
    E = exp-1023;
    if (E < 0) return 0;
    else if (E > 30) return ~0x7FFFFFFF;
    val=(1<<20) | (uf2 & 0xFFFFF);
    if (E <= 20){
        val = val>>(20 - E);
    }
    else val = (val<<(E-20)) | (uf1 >> (52-E));
    if (sign) return -val;
    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;
    if (x < -126) return 1 << (x + 149);
    if (x <= 127) return (x + 127) << 23;
    return 0xFF << 23;
}
