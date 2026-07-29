#include <iostream>
void fun(int i , int n)
{
    if(i>n)
    {
        return;
    }
    std::cout << "Harsh" << std::endl;
    fun(i+1,n);
}

int main()
{
    int n;
    std::cin >> n;
    fun(1,n);
    return 0;
}