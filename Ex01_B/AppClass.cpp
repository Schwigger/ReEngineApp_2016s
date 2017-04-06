#include "AppClass.h"
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
	static float fTimer = 0.0f;//creates a timer
	static uint uClock = m_pSystem->GenClock();//ask the system for a new clock id
	float fDeltaTime = m_pSystem->LapClock(uClock);//lap the selected clock
	fTimer += fDeltaTime;//add the delta time to the current clock
#pragma endregion

#pragma region YOUR CODE GOES HERE
	modelMatrix = IDENTITY_M4;
	
	matrix4 m4Translate = glm::translate(vector3(0.0f, 3.0f, 0.0f));

	float totalTime = 2.5f;
	float fPercentRot = MapValue(fTimer, 0.0f, totalTime, 0.0f, 1.0f);
	
	quaternion q1 = glm::angleAxis(0.0f, REAXISZ);
	quaternion q2 = glm::angleAxis(180.0f, REAXISZ);

	quaternion q3 = glm::mix(q2, q1, 2.0f * fPercentRot);
	quaternion q4 = glm::mix(q1, q2, 2.0f * fPercentRot);

	modelMatrix *= (ToMatrix4(q3) * m4Translate * glm::transpose(ToMatrix4(q3)));

	if (fPercentRot > 1.0f) {
		fTimer = 0.0f;
	}
#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

