#include <iostream>
#include "CApplication.h"

int main()
{
    auto app = CApplication(nullptr);
    app.BuildTree();
    app.ExecApp();
    return 0;
}
