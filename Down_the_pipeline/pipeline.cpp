
#pragma once
#include "WindowManager.h"
#include <cmath>
#include <chrono>
#include <thread>


int main()
{
    WindowManagement::WindowManager window = WindowManagement::WindowManager();
    window.InitializeOffsetTriangle();
    double smallSteps = 0.;
    while (window.EndWindow()) {

        window.ListenProgramEnd();
        window.RenderMovingTriangle(smallSteps);
        window.ProcessEvents();

        smallSteps += 5.e-4;
        if (smallSteps > _HUGE_ENUF)
            smallSteps = 0.0;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}