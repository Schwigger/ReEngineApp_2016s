#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08_CameraClass - Schweigardt"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(RESOLUTIONS::C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
}

void AppClass::InitVariables(void)
{
	m_MyCamera = new MyCamera(vector3(0.0f, 2.5f, 15.0f), vector3(0.0f, 2.5f, 14.0f), REAXISY);

	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 1.0f, 10, RERED);
	m_m4Cone = glm::translate(IDENTITY_M4, vector3(1.0f, 3.0f, 0.0f));

	m_pCube = new PrimitiveClass();
	m_pCube->GenerateCube(1.0f, REBLUE);
	m_m4Cube = IDENTITY_M4;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);


}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid
	m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY);

	m_pCone->Render(m_MyCamera->GetProjection(false), m_MyCamera->GetView(), m_m4Cone);
	m_pCube->Render(m_MyCamera->GetProjection(false), m_MyCamera->GetView(), m_m4Cube);

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	//Release the memory of the member fields
	SafeDelete(m_pCone);
	SafeDelete(m_pCube);

	super::Release(); //release the memory of the inherited fields
}