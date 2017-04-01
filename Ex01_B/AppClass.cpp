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

	float fPercentTrans;
	float fPercentRot;
	static float fTop = 1.0;
	static float fBottom = 0.0f;

	matrix4 m4Translate;
	vector3 v3Lerp;

	quaternion q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q2 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q3;

	fPercentTrans = MapValue(fTimer, 0.0f, 2.5f, fBottom, fTop);
	fPercentRot = MapValue(fTimer, 0.0f, 2.5f, 0.0f, 1.0f);

	if (fPercentTrans > 1.0f || fPercentTrans < 0.0f) {
		fTimer = 0.0f;

		float fTemp = fTop;
		fTop = fBottom;
		fBottom = fTemp;
	}

	q3 = glm::mix(q1, q2, fPercentRot);

	v3Lerp = glm::lerp(v3Lerp, vector3(0.0f,3.0f,0.0f), fPercentTrans);
	m4Translate = glm::translate(v3Lerp);

	modelMatrix *= (ToMatrix4(q3) * m4Translate);
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

