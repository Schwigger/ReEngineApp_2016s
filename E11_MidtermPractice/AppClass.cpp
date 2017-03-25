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
	static float dTotalTime = 0.0f; //Total time of the simulation
	float dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 
#pragma endregion
#pragma region YOUR CODE GOES HERE
	m_m4Steve = glm::mat4(1.0f); // same as m_m4Steve = IDENTITY_M4; setting the identity to steve

	float timerMapped;
	static float rotation = 0.0f;
	static float top = 1.0;
	static float bottom = 0.0;
	static float limit = 5.0f;
	vector3 v3Lerp;
	vector3 away = vector3(0.0f, 5.0f, 0.0f);

	timerMapped = MapValue(dTotalTime, 0.0f, limit, bottom, top);

	if (timerMapped > 1.0f || timerMapped < 0.0f) {
		dTotalTime = 0.0;

		float temp = top;
		top = bottom;
		bottom = temp;
	}


	v3Lerp = glm::lerp(v3Lerp, away, timerMapped);

	m_m4Steve = glm::rotate(IDENTITY_M4, glm::degrees(rotation), vector3(0.0f, 0.0f, 1.0f)) * glm::translate(v3Lerp);
	rotation += dDeltaTime * 2.5f;
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName() + " - Schweigardt", REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
