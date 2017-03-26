#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - mxs9629"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;

	//Earth Orbit
	float fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//Matrices for transformations
	matrix4 m_m4Sun = IDENTITY_M4;
	matrix4 m_m4Earth = IDENTITY_M4;
	matrix4 m_m4Moon = IDENTITY_M4;

	//Matrices to hold relative translations
	matrix4 distEarth = glm::translate(11.0f, 0.0f, 0.0f);
	matrix4 distMoon = glm::translate(2.0f, 0.0f, 0.0f);

	//Matrices to hold relative scales
	matrix4 scaleEarth = glm::scale(vector3(0.524f));
	matrix4 scaleMoon = glm::scale(vector3(0.27f)) * scaleEarth;
	matrix4 scaleSun = glm::scale(vector3(5.936f));

	//Quaternions for rotation
	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
	glm::quat q2 = glm::angleAxis(359.0f, vector3(0.0f, 1.0f, 0.0f));

	glm::quat revEarth;
	glm::quat orbEarth;
	glm::quat revMoon;
	glm::quat orbMoon;

	//Calculate the percentage of rotation for each orbit or revolution
	//Earth's revolution around it's axis
	float fPercentEarthRev = MapValue((float)fRunTime, 0.0f, 2 * fEarthHalfRevTime, 0.0f, 1.0f);
	revEarth = glm::mix(q1, q2, fPercentEarthRev);

	//Earth's orbit around the Sun
	float fPercentEarthOrb = MapValue((float)fRunTime, 0.0f, 2 * fEarthHalfOrbTime, 0.0f, 1.0f);
	orbEarth = glm::mix(q1, q2, fPercentEarthOrb);

	//The Moon's orbit around the Earth
	float fPercentMoonOrb = MapValue((float)fRunTime, 0.0f, 2 * fMoonHalfOrbTime, 0.0f, 1.0f);
	orbMoon = glm::mix(q1, q2, fPercentMoonOrb);

	//Translate, rotate, and scale the Earth around the Sun
	m_m4Earth = m_m4Sun * ToMatrix4(orbEarth) * distEarth * scaleEarth;

	//Translate, rotate, and scale the Moon around the Earth
	m_m4Moon = m_m4Earth * ToMatrix4(orbMoon) * distMoon * scaleMoon;

	//Rotate the Earth along it's own axis
	m_m4Earth = m_m4Earth * ToMatrix4(revEarth);

	//Scale the Sun
	m_m4Sun = m_m4Sun * scaleSun;

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	//Use the fPercents rounded down as Number of orbits/revolutions
	nEarthOrbits = floor(fPercentEarthOrb);
	nEarthRevolutions = floor(fPercentEarthRev);
	nMoonOrbits = floor(fPercentMoonOrb);
	
	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); // Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}