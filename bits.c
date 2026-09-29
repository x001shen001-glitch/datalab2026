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
    int rst = 2;
    if(!x){
        rst = !y;
    } else if(!y){
        rst = !x;
    } else{
        int signx = x >> 31;
        int signy = y >> 31;
        rst = !(signx ^ signy);
    }

    return rst;
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
    int r = 0;
    int s;
    s = ((v >> 16) > 0) << 4;  r = r | s;  v = v >> s; //这里左移4位是把1转换为16，当做if来用
    s = ((v >> 8) > 0) << 3;  r = r | s;  v = v >> s; //这里v只剩后16位，再次分前8后8
    s = ((v >> 4) > 0) << 2;  r = r | s;  v = v >> s;
    s = ((v >> 2) > 0) << 1;  r = r | s;  v = v >> s;
    s = ((v >> 1) > 0);  r = r | s;
    return r;
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
    int nB = n << 3;
    int mB = m << 3;
    int d = ((x >> nB) ^ (x >> mB)) & 0xFF;
    return x ^ (d << nB) ^ (d << mB);
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
    unsigned int r = 0;
    for(int i = 0; i != 32; i++){
        r = (r << 1) | (v & 1);
        v = v >> 1;
    }
    return r;
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
    x = x >> n;
    int d = 0x80000000;
    d = ~(d >> n << 1);
    x = x & d;
    return x;
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
    int v = ~x;
    int s = 0;
    int r = 0;
    s = (v >> 16 != 0) << 4; r = r | s; v = v >> s; 
    s = (v >> 8 != 0) << 3; r = r | s; v = v >> s; 
    s = (v >> 4 != 0) << 2; r = r | s; v = v >> s; 
    s = (v >> 2 != 0) << 1; r = r | s; v = v >> s; 
    s = (v >> 1 != 0); r = r | s; v = v >> s; 
    return 32 + ~r + !v; // x = -1时会少一个，用!v来判断
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
    unsigned ux = x;
    unsigned sign = 0;
    int k = 0;
    unsigned t, frac, rest, half;

    if (!x) return 0;
    if (x < 0) { sign = 0x80000000u; ux = ~ux + 1; }

    t = ux;
    while (t > 1) { t = t >> 1; k = k + 1; }

    if (k < 24) {
        frac = ux << (23 - k);
    } else {
        t = k - 23;
        frac = ux >> t;
        half = 1 << (t - 1);
        rest = ux - (frac << t);
        frac = frac + ((rest > half) | ((rest == half) & (frac & 1)));
    }
    return sign | ((k + 127 + (frac >> 24)) << 23) | (frac & 0x7FFFFF);
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
    unsigned exp = (uf >> 23) & 0xFF;
    if (exp == 255) return uf;
    if (exp == 0)   return (uf & 0x80000000u) | (uf << 1); //(uf & 0x80000000u) | 是用来取首位符号位
    if (exp == 254)
        if (uf & 0x7FFFFF) return (uf & 0x80000000u) | 0x7F800000u;
    return uf + (1u << 23);
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
    unsigned sign = uf2 >> 31;
    unsigned exp = (uf2 >> 20) & 0x7FF;
    unsigned val = 0x80000000u | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);

    if (exp < 1023) return 0;
    if (exp > 1054) return 0x80000000;

    val = val >> (1054 - exp);

    if (sign) {
        if (val > 0x80000000u) return 0x80000000;
        return ~val + 1;
    }
    if (val > 0x7FFFFFFF) return 0x80000000;
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
    if (x >= 128)   return 0x7F800000;   /* +INF */
    if (x <= -150)  return 0;
    if (x >= -126)  return (x + 127) << 23;  /* 规格化：(x + 127) 挪到 bit23 起 */
    return 1 << (149 + x);                  /* 非规格化：x=-149→1, -148→2, -127→0x400000 即1左移位（149+x）*/
}
