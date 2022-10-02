Problem: Given two positive integers num1 and num2, find the integer x such that:

x has the same number of set bits as num2, and
The value x XOR num1 is minimal.
Note that XOR is the bitwise XOR operation.

Return the integer x. The test cases are generated such that x is uniquely determined.

The number of set bits of an integer is the number of 1's in its binary representation.

Prerequisites:
how to check if bit is set at ith position :
(1 << i) & 1

Property of XOR = 0^0 = 0 , 1^1 = 0  , 0 ^ 1 = 1, 1^0 = 1;


Algorithm:
1. Make an array of size 33 [ since Int can be 32 bit long]
2. set all the bit position for numb1.
3. count no of set bits in num2.

4. there can be 3 condition.
    a. no of set bits in num1 == no of set bits in num2 
        -> set all bits in resulting num as set in num1 => this would fetch the minimum XORED valued, since the resultant would be 0
    b. no of set bits in num1 > # bits in num2
        -> start setting the bit in num2 from left side.
            eg. num1 = 15(1111) num2 = 6 (110)[no of set bit = 2 ]
            now to minimze the XOR, left most set bit of 15 should be matched. In order to set the 4th bit in an number we should do  num = [0 ^( 1 << 4)]
        -> move left to right to set bit and continue to decrease count of bits to be set in resultant number.

    c. no of set bits in num1 < # bits in num2.
        -> do similar to (b)
        -> for the bits that are still to be set. since the minimized XOR value is required check for the smallest position where the bit is 0 in the answer.
            eg. num1 = 8 ( 1000) num2 = 19(10011) [ no of set bit = 3]
            after step (b) -> we would get ans = 1000 ( which would get us XOR = 0 but the bits used are 1)
            so we want to set 2 more bits.
            we iterate from right. for pos = 0 we check if the bit is set or not. ( 1 << pos )&1
            if it is not set. Set this bit and reduce count of bits to be set in solution. now ans becomes (1001)
            do this till count of bits > 0 

Solution:

class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int bits[33] = {0};
        int pos = 0;
        while(num1){
            if(num1&1)  bits[pos]= 1;
            num1>>=1;
            pos+=1;
        }
        int countBits = 0;
        while(num2){
            if(num2&1) countBits +=1;
            num2>>=1;
        }
        int num = 0;
        for(int i = 32; i >= 0 ; i--){
            if ( bits[i] == 1 and countBits > 0 ){ num += (1 << i ); countBits -=1;}
            if(countBits <= 0 ) return num;
        }
        int right = 0 ;
        while(countBits > 0){
            if(((1 << right)& num ) == 0)
            {
    
                num ^= ( 1 << right); countBits -=1;
            }
            right +=1;
        }
        return num;
    }
};
