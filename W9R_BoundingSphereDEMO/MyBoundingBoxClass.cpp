#include "MyBoundingBoxClass.h"

MyBoundingBoxClass::MyBoundingBoxClass(std::vector<vector3> vertexList)
{
	m_bColliding = false;
	m_fRadius = 0.0f;
	m_v3CenterGlobal = vector3(0.0f);
<<<<<<< HEAD
	m_v3Size = vector3(0.0f);
=======
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265

	if (vertexList.size() < 1)
		return;

<<<<<<< HEAD
	m_v3Max = vertexList[0];
	m_v3Min = vertexList[0];

	
=======
	m_v3Min = vertexList[0];
	m_v3Max = vertexList[0];
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265

	for (int i = 1; i < vertexList.size(); i++)
	{
		if (m_v3Min.x > vertexList[i].x)
		{
			m_v3Min.x = vertexList[i].x;
		}
		else if (m_v3Max.x < vertexList[i].x)
		{
			m_v3Max.x = vertexList[i].x;
		}

		if (m_v3Min.y > vertexList[i].y)
		{
			m_v3Min.y = vertexList[i].y;
		}
		else if (m_v3Max.y < vertexList[i].y)
		{
			m_v3Max.y = vertexList[i].y;
		}

		if (m_v3Min.z > vertexList[i].z)
		{
			m_v3Min.z = vertexList[i].z;
		}
		else if (m_v3Max.z < vertexList[i].z)
		{
			m_v3Max.z = vertexList[i].z;
		}
	}

<<<<<<< HEAD
	m_v3MaxGlobal = m_v3Max;
	m_v3MinGlobal = m_v3Min;

	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);

	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyBoundingBoxClass::Render()
=======
	m_v3CenterLocal = m_v3CenterGlobal = (m_v3Max + m_v3Min) / 2.0f;
	m_fRadius = glm::distance(m_v3CenterGlobal, m_v3Max);
	m_pMeshMngr = MeshManagerSingleton::GetInstance();
	m_v3Size = m_v3Max - m_v3Min;

	m_v3MinG = m_v3Min;
	m_v3MaxG = m_v3Max;
	
	//m_v3Size.x = glm::distance(vector3(m_v3Min.x, 0.0, 0.0), vector3(m_v3Max.x, 0.0, 0.0));
	//m_v3Size.y = glm::distance(vector3(0.0, m_v3Min.y, 0.0), vector3(0.0, m_v3Max.y, 0.0));
	//m_v3Size.z = glm::distance(vector3(0.0, 0.0, m_v3Min.z), vector3(0.0, 0.0, m_v3Max.z));
}

void MyBoundingBoxClass::RenderSphere()
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265
{
	vector3 v3Color = REGREEN;
	if (true == m_bColliding)
		v3Color = RERED;

	m_pMeshMngr->AddCubeToRenderList(
<<<<<<< HEAD
		m_m4ToWorld * 
=======
		m_m4ToWorld *
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265
		glm::translate(m_v3CenterLocal) *
		glm::scale(m_v3Size),
		v3Color, WIRE);
}
void MyBoundingBoxClass::SetModelMatrix(matrix4 a_m4ToWorld)
{
	if (m_m4ToWorld == a_m4ToWorld)
		return;

	m_m4ToWorld = a_m4ToWorld;
	m_v3CenterGlobal = vector3(m_m4ToWorld * vector4(m_v3CenterLocal, 1.0f));
<<<<<<< HEAD
	m_v3MaxGlobal = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
	m_v3MinGlobal = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
=======
	m_v3MinG = vector3(m_m4ToWorld * vector4(m_v3Min, 1.0f));
	m_v3MaxG = vector3(m_m4ToWorld * vector4(m_v3Max, 1.0f));
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265
}

bool MyBoundingBoxClass::IsColliding(MyBoundingBoxClass* a_other)
{
<<<<<<< HEAD
	if (this->m_v3MaxGlobal.x < a_other->m_v3MinGlobal.x)
		return false;
	if (this->m_v3MinGlobal.x > a_other->m_v3MaxGlobal.x)
		return false;

	if (this->m_v3MaxGlobal.y < a_other->m_v3MinGlobal.y)
		return false;
	if (this->m_v3MinGlobal.y > a_other->m_v3MaxGlobal.y)
		return false;

	if (this->m_v3MaxGlobal.z < a_other->m_v3MinGlobal.z)
		return false;
	if (this->m_v3MinGlobal.z > a_other->m_v3MaxGlobal.z)
=======
	if (this->m_v3MaxG.x < a_other->m_v3MinG.x)
		return false;
	if (this->m_v3MinG.x > a_other->m_v3MaxG.x)
		return false;

	if (this->m_v3MaxG.y < a_other->m_v3MinG.y)
		return false;
	if (this->m_v3MinG.y > a_other->m_v3MaxG.y)
		return false;

	if (this->m_v3MaxG.z < a_other->m_v3MinG.z)
		return false;
	if (this->m_v3MinG.z > a_other->m_v3MaxG.z)
>>>>>>> be672c5fdf7e2c04214839dfeb33e067698a7265
		return false;

	return true;
}

void MyBoundingBoxClass::SetColliding(bool input) { m_bColliding = input; }
void MyBoundingBoxClass::SetCenterLocal(vector3 input) { m_v3CenterLocal = input; }
void MyBoundingBoxClass::SetCenterGlobal(vector3 input) { m_v3CenterGlobal = input; }
void MyBoundingBoxClass::SetRadius(float input) { m_fRadius = input; }
bool MyBoundingBoxClass::GetColliding(void) { return m_bColliding; }
vector3 MyBoundingBoxClass::GetCenterLocal(void) { return m_v3CenterLocal; }
vector3 MyBoundingBoxClass::GetCenterGlobal(void) { return m_v3CenterGlobal; }
float MyBoundingBoxClass::GetRadius(void) { return m_fRadius; }
matrix4 MyBoundingBoxClass::GetModelMatrix(void) { return m_m4ToWorld; }