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

	static vector3 v3Start = vector3(0.0f);
	static vector3 v3End = vector3(0.0f, 3.0f, 0.0f);

	float fTotalTime = 2.0f;
	float fPercentage = MapValue(fTimer, 0.0f, fTotalTime, 0.0f, 1.0f);

	//Translateion part
	vector3 v3Current = glm::lerp(v3Start, v3End, fPercentage);
	matrix4 m4Translate = glm::translate(v3Current);

	//Rotation part
	quaternion q1 = glm::angleAxis(0.0f, REAXISZ);
	quaternion q2 = glm::angleAxis(180.0f, REAXISZ);


	quaternion q3 = glm::mix(q1, q2, 2.0f * fPercentage);

	modelMatrix *= (m4Translate * ToMatrix4(q3));

	if (fPercentage > 1.0f) {
		fTimer = 0.0f;

		std::swap(v3Start, v3End);
	}
#pragma endregion

#pragma region DOES NOT NEED CHANGES
	m_pMeshMngr->SetModelMatrix(modelMatrix, 0);//Set the model matrix to the model

	m_pMeshMngr->AddSkyboxToRenderList();//Adds a skybox to the renderlist
	m_pMeshMngr->AddInstanceToRenderList("ALL"); //Adds all loaded instances to the render list

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
<<<<<<< HEAD
<<<<<<< HEAD
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName() + " - Schweigardt (mxs9629)", REYELLOW);
=======
	m_pMeshMngr->PrintLine("");//Add a line on top
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
>>>>>>> 3a599dd642348e48a93f58a5cdd8a50114af0a2c
=======
	m_pMeshMngr->PrintLine("\n" + m_pSystem->GetAppName(), REYELLOW);
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265
	m_pMeshMngr->PrintLine("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REGREEN);

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

