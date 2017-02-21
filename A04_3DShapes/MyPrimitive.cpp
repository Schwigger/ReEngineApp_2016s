#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}

	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop) {
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}

void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f * a_fHeight;
	//Variable that is the tip of the cone
	vector3 topPoint(0.0f, a_fHeight, 0.0f);
	std::vector<vector3> points;

	//Add center of the base to make life a little easier
	points.push_back(vector3(0.0f, -fValue, 0.0f));

	float theta = 0.0f;
	float steps = (2 * PI) / static_cast<float>(a_nSubdivisions);

	//Loop through and add in the points that make up the base
	for (int i = 0; i < a_nSubdivisions; i++) {
		points.push_back(vector3(glm::cos(theta) * a_fRadius, -fValue, glm::sin(theta) * a_fRadius));
		theta += steps;
	}

	//Loop through and connect the faces
	for (int i = 1; i < a_nSubdivisions; ++i) {
		AddTri(points[0], points[i], points[i + 1]);
		AddTri(topPoint, points[i + 1], points[i]);
	}

	//Left over faces that the loop cannot handle
	AddTri(points[a_nSubdivisions], points[1], points[0]);
	AddTri(topPoint, points[1], points[a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f * a_fHeight;
	//2 vectors of points as we need a top and base
	std::vector<vector3> topPoints;
	std::vector<vector3> basePoints;

	//Add both center points
	topPoints.push_back(vector3(0.0f, fValue, 0.0f));
	basePoints.push_back(vector3(0.0f, -fValue, 0.0f));

	float theta = 0.0f;
	float steps = (2 * PI) / static_cast<float>(a_nSubdivisions);

	//Loop through and add the points of the bases
	for (int i = 0; i < a_nSubdivisions; i++) {
		topPoints.push_back(vector3(glm::cos(theta) * a_fRadius, fValue, glm::sin(theta) * a_fRadius));
		basePoints.push_back(vector3(glm::cos(theta) * a_fRadius, -fValue, glm::sin(theta) * a_fRadius));
		theta += steps;
	}

	//Connect the faces
	for (int i = 1; i < a_nSubdivisions; ++i) {
		AddTri(topPoints[0], topPoints[i + 1], topPoints[i]);
		AddTri(basePoints[0], basePoints[i], basePoints[i + 1]);
		AddQuad(basePoints[i + 1], basePoints[i], topPoints[i + 1], topPoints[i]);
	}

	//Extra faces the loop cannot handle
	AddTri(topPoints[a_nSubdivisions], topPoints[0], topPoints[1]);
	AddTri(basePoints[a_nSubdivisions], basePoints[1], basePoints[0]);
	AddQuad(basePoints[1], basePoints[a_nSubdivisions], topPoints[1], topPoints[a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f * a_fHeight;
	//4 vectors of points because we need inner and outer rings
	std::vector<vector3> topPointsInner;
	std::vector<vector3> basePointsInner;
	std::vector<vector3> topPointsOuter;
	std::vector<vector3> basePointsOuter;

	//I don't know why I used the centers, but it breaks if I don't
	topPointsInner.push_back(vector3(0.0f, fValue, 0.0f));
	basePointsInner.push_back(vector3(0.0f, -fValue, 0.0f));
	topPointsOuter.push_back(vector3(0.0f, fValue, 0.0f));
	basePointsOuter.push_back(vector3(0.0f, -fValue, 0.0f));

	float theta = 0.0f;
	float steps = (2 * PI) / static_cast<float>(a_nSubdivisions);

	//Loop through and add the points of the inner and outer circles of the top and base
	for (int i = 0; i < a_nSubdivisions; i++) {
		topPointsInner.push_back(vector3(glm::cos(theta) * a_fInnerRadius, fValue, glm::sin(theta) * a_fInnerRadius));
		basePointsInner.push_back(vector3(glm::cos(theta) * a_fInnerRadius, -fValue, glm::sin(theta) * a_fInnerRadius));
		topPointsOuter.push_back(vector3(glm::cos(theta) * a_fOuterRadius, fValue, glm::sin(theta) * a_fOuterRadius));
		basePointsOuter.push_back(vector3(glm::cos(theta) * a_fOuterRadius, -fValue, glm::sin(theta) * a_fOuterRadius));
		theta += steps;
	}

	//Loop through and connect the faces
	//Similar to GenerateCylinder(), but with an inner, reversed set of sides
	for (int i = 1; i < a_nSubdivisions; ++i) {
		AddQuad(basePointsInner[i], basePointsInner[i + 1], topPointsInner[i], topPointsInner[i + 1]);
		AddQuad(basePointsOuter[i + 1], basePointsOuter[i], topPointsOuter[i + 1], topPointsOuter[i]);
		AddQuad(topPointsOuter[i + 1], topPointsOuter[i], topPointsInner[i + 1], topPointsInner[i]);
		AddQuad(basePointsOuter[i], basePointsOuter[i + 1], basePointsInner[i], basePointsInner[i + 1]);
	}

	//Last faces that the loop cannot handle
	AddQuad(basePointsInner[a_nSubdivisions], basePointsInner[1], topPointsInner[a_nSubdivisions], topPointsInner[1]);
	AddQuad(basePointsOuter[1], basePointsOuter[a_nSubdivisions], topPointsOuter[1], topPointsOuter[a_nSubdivisions]);
	AddQuad(topPointsOuter[1], topPointsOuter[a_nSubdivisions], topPointsInner[1], topPointsInner[a_nSubdivisions]);
	AddQuad(basePointsOuter[a_nSubdivisions], basePointsOuter[1], basePointsInner[a_nSubdivisions], basePointsInner[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	float fValue = 1.0f;
	vector3 pointA(-fValue, -fValue, fValue); //0
	vector3 pointB(fValue, -fValue, fValue); //1
	vector3 pointC(-fValue, fValue, fValue); //2

											 //left to right List of vector3
	std::vector<vector3> vectorAB;
	vectorAB.push_back(pointA);
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp(pointB - pointA);
		temp /= a_nSubdivisions + 1;
		temp *= (i + 1);
		vectorAB.push_back(temp + pointA);
	}
	vectorAB.push_back(pointB);

	//height increments
	float fHeight = pointC.y - pointA.y;
	fHeight /= a_nSubdivisions + 1;

	//List of Lists
	std::vector<std::vector<vector3>> list;
	list.push_back(vectorAB);
	for (int j = 0; j < a_nSubdivisions + 1; j++)
	{
		std::vector<vector3> temp = list[0];
		float increment = fHeight * (j + 1);
		for (int i = 0; i < a_nSubdivisions + 2; i++)
		{
			temp[i].y += increment;
		}
		list.push_back(temp);
	}

	//Creating the patch of quads
	for (int j = 0; j < a_nSubdivisions + 1; j++)
	{
		for (int i = 0; i < a_nSubdivisions + 1; i++)
		{
			AddQuad(list[j][i], list[j][i + 1], list[j + 1][i], list[j + 1][i + 1]);
		}
	}

	//normalizing the vectors to make them round
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		m_lVertexPos[i] = glm::normalize(m_lVertexPos[i]);
		m_lVertexPos[i] *= a_fRadius;
	}

	//RightSideFace
	int nVert = m_uVertexCount;
	std::vector<vector3> right;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(0.0f, 1.0f, 0.0f));
		right.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}


	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(right[i]);
	}

	//LeftSideFace
	std::vector<vector3> left;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(0.0f, 1.0f, 0.0f));
		left.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(left[i]);
	}

	//BackSideFace
	std::vector<vector3> back;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 180.0f, vector3(0.0f, 1.0f, 0.0f));
		back.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(back[i]);
	}

	//TopSideFace
	std::vector<vector3> top;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(1.0f, 0.0f, 0.0f));
		top.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(top[i]);
	}

	//BottomSideFace
	std::vector<vector3> bottom;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(1.0f, 0.0f, 0.0f));
		bottom.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(bottom[i]);
	}
	//Your code ends here
	CompileObject(a_v3Color);
}