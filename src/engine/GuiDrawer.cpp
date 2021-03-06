#include "GuiDrawer.h"

//bool GuiDrawer::show_demo_window = true;
//bool GuiDrawer::show_another_window = false;
//ImVec4 GuiDrawer::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

ImVec4 GuiDrawer::particlePosition = ImVec4(0.0f, 0.0f, -1.0f, 0.0f);
ImVec4 GuiDrawer::particleColorBirth = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
ImVec4 GuiDrawer::particleColorDeath = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
ImVec4 GuiDrawer::particleSpeed = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
float GuiDrawer::particleScaleBirth = 0.5f;
float GuiDrawer::particleScaleDeath = 0.0f;
float GuiDrawer::particleLifeTime = 1.0f;

void GuiDrawer::Init(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    //(void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
}

void GuiDrawer::End()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GuiDrawer::Draw()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    /*if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);*/

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    //{
    //    static float f = 0.0f;
    //    static int counter = 0;

    //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //    ImGui::Checkbox("Another Window", &show_another_window);

    //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    //        counter++;
    //    ImGui::SameLine();
    //    ImGui::Text("counter = %d", counter);

    //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //    ImGui::End();
    //}

    // 3. Show another simple window.
    //if (show_another_window)
    //{
    //    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    //    ImGui::Text("Hello from another window!");
    //    if (ImGui::Button("Close Me"))
    //        show_another_window = false;
    //    ImGui::End();
    //}

    // Particle System window
    ImGui::Begin("Particle System Manager"); // Create window

    ImGui::SliderFloat3("Starting Position", (float*)&particlePosition, -1000.0f, 1000.0f); // Edit 3 floats using a slider
    ImGui::ColorEdit3("Birth Color", (float*)&particleColorBirth); // Edit 3 floats representing a color
    ImGui::ColorEdit3("Death Color", (float*)&particleColorDeath); // Edit 3 floats representing a color
    ImGui::SliderFloat3("Starting Speed", (float*)&particleSpeed, -10.0f, 10.0f); // Edit 3 floats representing a vec3
    ImGui::SliderFloat("Birth Scale", &particleScaleBirth, 0.0f, 10.0f); // Edit 1 float using a slider
    ImGui::SliderFloat("Death Scale", &particleScaleDeath, 0.0f, 10.0f); // Edit 1 float using a slider
    ImGui::SliderFloat("Life Time", &particleLifeTime, 0.1f, 10.0f); // Edit 1 float using a slider

    ImGui::End(); // Destroy window

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}