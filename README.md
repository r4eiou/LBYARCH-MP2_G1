# LBYARCH-MP2_G1

S11\
Members:\
GARCIA, REINA ALTHEA CRUZ\
MONSERRAT, ANTONIO ENRIQUE MOJICA

**I. Comparative execution time and short analysis of the performance of the kernels**\
\
The comparison of execution time between the C program and the x86-64 assembly implementation of the dot product shows differences in their respective performance. The assembly implementation, which utilizes SIMD floating-point instructions and functional scalar SIMD registers, performs better than the C implementation, which uses a for loop. This is expected, as assembly language is mapped directly to machine language, which can be executed by the CPU.

We ran each kernel version 20 times for each vector size: 2^20, 2^24, and 2^28. The corresponding outputs are as follows:\
2^20
- Average Time for x86-64: 0.000600s
- Average Time for C: 0.002450s

2^24
- Average Time for x86-64: 0.015250s
- Average Time for C: 0.037050s

2^28
- Average Time for x86-64: 0.240400s
- Average Time for C: 0.606250s

From these results, we can conclude that the x86-64 assembly implementation runs much faster than the C implementation, and the difference in execution time grows larger as the vector size increases. The faster performance of assembly is clear for all tested vector sizes, showing the benefits of using SIMD optimizations and directly utilizing CPU instructions.

For C implementation:
- It uses a simple for loop to iterate through the vectors and accumulate the result. Execution time increases with the size of the vector, as each multiplication and addition is processed sequentially.

For Assembly Implementation:
- It uses SIMD instructions, which allow for parallel processing, enabling the processor to handle multiple data points simultaneously. This significantly reduces execution time for larger vectors.

**II-III. Screenshot of the program output with the correctness check (C) and (x86-64).**

_2^20:_

![image](https://github.com/user-attachments/assets/c5471f66-a549-4211-8a49-4b5c97f3f6a1)

_2^24:_

![image](https://github.com/user-attachments/assets/7ace1b4f-d5c0-4b21-b12f-a2e72c36d785)

_2^28:_

![image](https://github.com/user-attachments/assets/48db92a5-2e92-4bd3-be57-9cac2064ac12)

-----------------------------------------------------------------------------------------------------------------------------------

Use following commands to execute code:\
nasm -f win64 asmfile.asm\
gcc -c cfileTesting.c -o cfileTesting.obj -m64\
gcc cfileTesting.obj asmfile.obj -o cfileTesting.exe -m64\
cfileTesting.exe



