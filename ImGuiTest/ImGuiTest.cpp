#include <iostream>
#include "./ImGui/imgui.h"
#include "./ImGui/imgui_impl_win32.h"


int main()
{
    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("Window");
    ImGui::Text("innit bruv");
    ImGui::End();
}