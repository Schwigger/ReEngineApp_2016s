#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP Schweigardt"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan;
#pragma endregion

#pragma region Your Code goes here
	matrix4 m4WallEye = IDENTITY_M4;
	static int point = 0;
	vector3 v3Lerp;
	matrix4 m4Shere1;

	std::vector<vector3> positions = {
		vector3(-4.0f,-2.0f, 5.0f),
		vector3(1.0f,-2.0f, 5.0f),
		vector3(-3.0f,-1.0f, 3.0f),
		vector3(2.0f,-1.0f, 3.0f),
		vector3(-2.0f, 0.0f, 0.0f),
		vector3(3.0f, 0.0f, 0.0f),
		vector3(-1.0f, 1.0f,-3.0f),
		vector3(4.0f, 1.0f,-3.0f),
		vector3(0.0f, 2.0f,-5.0f),
		vector3(5.0f, 2.0f,-5.0f),
		vector3(1.0f, 3.0f,-5.0f)
	};

	//Use the Clock
	static DWORD startTimeSystem = GetTickCount();	//Ask system's start up time
	DWORD timeApplication = GetTickCount() - startTimeSystem;	//Get current time and subtract the start time
	float timer = timeApplication / 1000.0f;	//time is in milliseconds need it in seconds
	float timerMapped;

	//Make a matrix & add sphere(s)
	for (int i = 0; i < 11; ++i) {
		m4Shere1 = glm::translate(positions[i]) * glm::scale(vector3(0.1f));
		m_pMeshMngr->AddSphereToRenderList(m4Shere1, RERED, WIRE | SOLID);
	}

	if (point < 11)
	{
		timerMapped = MapValue(timer, 0.0f, 5.0f, 0.0f, 1.0f);

		if (timerMapped > 1.0f) {
			++point;
			timerMapped = 0.0f;
		}
		if (point == 10) {
			v3Lerp = glm::lerp(positions[10], positions[0], timerMapped);
			point = 0;
			timerMapped = 0.0f;
		}

		v3Lerp = glm::lerp(positions[point], positions[point + 1], timerMapped);
	}

	m4WallEye = glm::translate(v3Lerp);
	m_pMeshMngr->SetModelMatrix(m4WallEye, "WallEye");
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Time is : " + std::to_string(timer));	//Print the time
	//Print the FPS
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}