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
    return ~(~x & ~y) & ~(x & y);
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
    if ((x^y)>>31) return 0;
    if (!x) return !y;
    if (!y) return 0;
    return 1;
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
    int ans = 0;
    int shift = 0;

    shift = ((v >> 16) > 0) << 4; //16
    v = v >> shift;
    ans = ans | shift;

    shift = ((v >> 8) > 0) << 3; //8
    v = v >> shift;
    ans = ans | shift;


    shift = ((v >> 4) > 0) << 2; //4
    v = v >> shift;
    ans = ans | shift;

    shift = ((v>>2)>0) << 1; //2
    v = v >> shift;
    ans = ans | shift;

    shift = ((v >> 1) > 0); //1
    ans = ans | shift;

    return ans;
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
    int shift_n = n << 3;
    int shift_m = m << 3;

    int mask = (0xFF << shift_n) | (0xFF << shift_m);

    int byte_n = (x >> shift_n) & 0xFF;
    int byte_m = (x >> shift_m) & 0xFF;

    int cleared = x & (~mask);

    return (cleared | (byte_m << shift_n) | (byte_n << shift_m));
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
     v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
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
    int mask = ~(((1<<31)>>n)<<1);
    return (x >> n) & mask;
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
    int y = ~x;
    int m;
    int count = 0;

    m = !(y >> 16); // y是否前16位都是0
    count = m << 4;
    y = y << (m << 4);

    m = !(y >> 24); // 当前前8位是否都是0
    count += m << 3;
    y = y << (m << 3);

    m = !(y >> 28); // 当前前4位
    count += m << 2;
    y = y << (m << 2);

    m = !(y >> 30); // 当前前2位
    count += m << 1;
    y = y << (m << 1);

    m = !(y >> 31); // 当前最高位
    count += m;
    y = y << m;

    count += !y;    // 全部32位都是1的情况
    return count;
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
    unsigned sign = x & 0x80000000;   // 直接取符号位（放在bit31）
    int e = 31;                       // 要找出最高的1的位置，用e标注
    int shift;
    unsigned frac, rem, half;

    if (x == 0) return 0;
    if (x == 0x80000000) return 0xCF000000; 

    if (sign) x = ~x + 1;             // 取绝对值

    while (!(x >> e)) e = e - 1;

    shift = e - 23;
    if (shift > 0) {
        // 需要舍入：rem是被移掉的低位，half是"一半"的边界
        rem = x & ((1 << shift) - 1);
        half = 1 << (shift - 1);
        frac = (x >> shift) & 0x7FFFFF;
        // round-half-even：rem > half 进位；rem == half 且frac为奇数也进位
        // 等价写法：rem + (frac & 1) > half，避免使用 || 和 &&
        frac = frac + (rem + (frac & 1) > half);
    } else {
        frac = (x << (23 - e)) & 0x7FFFFF; // 左移补齐，去掉最高位的1
    }

    // frac若因进位变成0x800000，加法会自然进位到exp上
    return sign | (((e + 127) << 23) + frac);
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
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF) return uf;          // NaN 或 Inf

    if (exp == 0) {                      // 非规格化数或 0
        if (frac == 0) return uf;        // 0
        frac <<= 1;
        if (frac & 0x800000) {           // 进位到指数
            exp = 1;
            frac &= 0x7FFFFF;
        }
        return sign | (exp << 23) | frac;
    } else {                             // 规格化数
        exp++;
        if (exp == 0xFF) {               // 溢出为 Inf
            return sign | 0x7F800000;
        }
        return sign | (exp << 23) | frac;
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
    unsigned sign = uf2 >> 31;
    unsigned exp  = (uf2 >> 20) & 0x7FF;
    unsigned high = uf2 & 0xFFFFF;
    unsigned low  = uf1;

    if (!exp) return 0;                // 0 或非规格化
    if (exp >= 0x7FF) return 0x80000000; // Inf / NaN

    int e = exp - 1023;
    if (e < 0) return 0;
    if (e >= 31) return 0x80000000;

    unsigned frac_shift;
    int shift = 52 - e;
    if (shift >= 32) {
        frac_shift = high >> (shift - 32);
    } else {
        frac_shift = (high << (32 - shift)) | (low >> shift);
    }

    unsigned mag = (1 << e) | frac_shift;

    if (sign) return -mag;
    else      return mag;
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
    if (x > 127) {
        return 0x7F800000;               // +Inf
    }
    if (x >= -126) {
        unsigned exp = x + 127;
        return exp << 23;                // 规格化数
    }
    if (x >= -149) {
        return 1 << (x + 149);           // 非规格化数
    }
    return 0; 
}
