#include "GUIManager.h"
#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"
#include <iostream>

ImVec4 clear_color = ImColor(114, 144, 154);
bool show_another_window = false;
bool show_test_window = false;
GUIManager* GUIManager::s_pInstance = 0;
string message1 = " ";
string pMessage = " ";
int data;
bool test;
void GUIManager::renderUI(){

	ImGui_ImplSdlGL3_NewFrame();
	static float f = 0.0f;
	ImGui::Text("Hello, world!");
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::ColorEdit3("clear color", (float*)&clear_color);
	if (ImGui::Button("Another Window")) show_another_window ^= 1;


		
	ImGui::Text(message1.c_str());
	ImGui::Text(pMessage.c_str());
	ImGui::Render();

}

void GUIManager::displayText(char* mess, int value){

	string abc = mess + std::to_string(value);
	message1 = abc;
}

void GUIManager::displayText2(char* mess, int value){

	string abc = mess + std::to_string(value);
	pMessage = abc;
}
