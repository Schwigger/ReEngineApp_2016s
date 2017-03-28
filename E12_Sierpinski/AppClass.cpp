#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("E12 - Instance Rendering : mxs9629");
	m_v4ClearColor = vector4(REBLACK, 1.0f);
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	//Variable to store the number of layers
	//2 layers fulfills homework requirements of 9 triangles
	int nLayers = 2;

	//Start points for drawing
	vector3 left = vector3(0.0f, 4.0f, 0.0f);
	vector3 right = vector3(-4.0f, -4.0f, 0.0f);
	vector3 top = vector3(4.0f, -4.0f, 0.0f);

	//Call the method and draw ALL THE TRIANGLES!!!!!
	DivTriangles(left, right, top, nLayers);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName() + " : mxs9629", REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	ClearScreen();

	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObject(s)											   //clear the screen

	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}

void AppClass::DivTriangles(vector3 bLeft, vector3 bRight, vector3 top, int layers) {
	if (layers > 0) {
		//Find the mid point of the three sides
		vector3 v0 = (bLeft + bRight) / 2.0f;
		vector3 v1 = (bLeft + top) / 2.0f;
		vector3 v2 = (bRight + top) / 2.0f;
		//Recursion time
		DivTriangles(bLeft, v0, v1, layers - 1);
		DivTriangles(top, v1, v2, layers - 1);
		DivTriangles(bRight, v2, v0, layers - 1);
	}
	else {
		//Create Triangle from points
		m_pMesh->AddVertexPosition(bLeft);	//bottom left
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(bRight);	//bottom right
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(top);		//top
		m_pMesh->AddVertexColor(REBLUE);
	}

}


