#include "graphics.hpp"

using namespace genv;

int main()
{
    gout.open(800,600);
    gout << font("LiberationSans-Regular.ttf",20);
    gout << text("hello world");
    gout << refresh;
    event ev;
    while(gin >> ev)
    {
    }
    return 0;
}
