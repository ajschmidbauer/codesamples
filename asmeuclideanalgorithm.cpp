#include <iostream>

using namespace std;

int main()
{
    long long int a,b,x,y,d;
    cin>>a>>b;

asm( " mov %%rax,%%r12      \n"  //move A into r12
     " xor %%r10,%%r10      \n"  //set xnext to 0
     " xor %%rdi,%%rdi      \n"  //set y to 0
     " xor %%rsi,%%rsi      \n"  //set x to 1
     " inc %%rsi            \n"
     " xor %%r11,%%r11      \n"   //set ynext to 1
     " inc %%r11            \n"

     " jmp 2f                \n" //go to condition check
     " 1:   mov %%r12,%%rax \n"
     " xor  %%rdx,%%rdx     \n"
     " div %%rbx            \n"
     " mov %%rax,%%r8       \n"
     " mov %%rdx,%%r9       \n"
     " mov %%r10,%%r13      \n"
     " mov %%r8,%%rax       \n"
     " mul %%r10            \n"
     " sub %%rax,%%rsi      \n"
     " mov %%rsi,%%r10      \n"
     " mov %%r13,%%rsi      \n"

     " mov %%r11,%%r13      \n"
     " mov %%r8,%%rax       \n"
     " mul %%r11            \n"
     " sub %%rax,%%rdi      \n"
     " mov %%rdi,%%r11      \n"
     " mov %%r13,%%rdi      \n"

     " mov %%rbx,%%r12      \n"
     " mov %%r9,%%rbx       \n"

     "2:    andq  %%rbx,%%rbx \n"
     " jnz  1b               \n"
     " mov %%rsi,%%rax      \n"
     " mov %%rdi,%%rbx      \n"
     " mov %%r12,%%rcx      \n"


    : "=a" (x), "=b" (y), "=c" (d)
    : "a" (a), "b" (b)  //input values
    :
    );
    cout<<x<<' '<<y<<' '<<d<<endl;
    return 0;
}
