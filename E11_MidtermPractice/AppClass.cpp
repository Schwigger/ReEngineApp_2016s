#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion
#pragma region FEEL FREE TO USE THIS CLOCK
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	static DWORD startTimeSystem = GetTickCount();	//Ask system's start up time
	DWORD timeApplication = GetTickCount() - startTimeSystem;	//Get current time and subtract the start time
	float timer = timeApplication / 1000.0f;	//time is in milliseconds need it in seconds
	float timerMapped;
	static float top = 1.0f;
	static float bottom = 0.0f;
	static float limit = 5.0f;
	vector3 v3Lerp;
	vector3 destination = vector3(0.0f, 5.0f, 0.0f);
	vector3 home;

	timerMapped = MapValue(timer, 0.0f, limit, bottom, top);

	if (timerMapped > 1.0f) {
		startTimeSystem = GetTickCount();

		float temp = top;
		top = bottom;
		bottom = temp;
	}
	
	v3Lerp = glm::lerp(v3Lerp, destination, timerMapped);

	m_m4Steve = glm::translate(v3Lerp);

#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	m_pMeshMngr->Print(std::to_string(top));
#pragma endregion
}
