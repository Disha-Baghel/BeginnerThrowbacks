#include "Application.h"
#include "Page.h"
#include "Home.h"

Application* Application::Instance = nullptr;

Application::Application(){
    CreateCanvas(800,500,"My App");
    Background({240,240,240});

    Home();
}

void Application::Draw(){
    GetActivePage()->Show();
}
