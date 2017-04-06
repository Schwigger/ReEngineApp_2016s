#include "MyCameraClass.h"

MyCamera::MyCamera() {
	//Set matices = the Identity matrix
	m4View = IDENTITY_M4;
	m4Projection = IDENTITY_M4;

	//Set the vectors = vector3(1.0f, 1.0f, 1.0f)
	SetPosition(vector3(1.0f));
	SetTarget(vector3(1.0f));
	SetUp(vector3(1.0f));
}

MyCamera::MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Up) {
	//Set matices = the Identity matrix
	m4View = IDENTITY_M4;
	m4Projection = IDENTITY_M4;

	//Set the vectors = argument vectors
	SetPosition(a_v3Position);	
	SetTarget(a_v3Target);
	SetUp(a_v3Up);

	//Store these positions for later
	v3OriginPosition = a_v3Position;
	v3OriginTarget = a_v3Target;
}

MyCamera::~MyCamera() {}

matrix4 MyCamera::GetView(void) {

	//Calculate the Camera's up vector
	vector3 direction = glm::normalize(v3CameraPosition - v3CameraTarget);
	vector3 right = glm::normalize(glm::cross(vector3(0.0f, 1.0f, 0.0f), direction));
	vector3 up = glm::cross(direction, right);
	SetUp(up);

	//Put the stored position vector3 into the camera's orientation
	vector3 v3LocalPosition = vector3(ToMatrix4(qOrientation) * vector4(v3CameraPosition, 1.0f));
	vector3 v3LocalTarget = vector3(ToMatrix4(qOrientation) * vector4(v3CameraTarget, 1.0f));
	vector3 v3LocalUp = vector3(ToMatrix4(qOrientation) * vector4(v3CameraUp, 1.0f));

	//Calculate the transpose of the orietation
	matrix4 m4Transpose = glm::transpose(ToMatrix4(qOrientation));

	//Return the View matrix
	return m4View = m4Transpose * glm::lookAt(v3LocalPosition, v3LocalTarget, v3LocalUp);

}

matrix4 MyCamera::GetProjection(bool bOrthographic) {
	if (bOrthographic) {	//if true use orthographic view
		m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	}
	else {					//if false use perspective view
		m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
	//Return the Projection matrix
	return m4Projection;
}

void MyCamera::SetPosition(vector3 v3Position) {
	v3CameraPosition = v3Position;
}

void MyCamera::SetTarget(vector3 v3Target) {
	v3CameraTarget = v3Target;
}

void MyCamera::SetUp(vector3 v3Up) {
	v3CameraUp = v3Up;
}

void MyCamera::ResetPosition() {
	//Set position and target back to the first values
	SetPosition(v3OriginPosition);
	SetTarget(v3OriginTarget);
}

void MyCamera::ResetOrientation() {
	//Set orientation = blank quaternion
	qOrientation = quaternion();
}

void MyCamera::MoveForward(float fIncrement) {
	//Make a translateion vector3 in the camera's orientation along the z-axis
	vector3 v3Translate = vector3(ToMatrix4(qOrientation) * vector4(0.0f, 0.0f, -fIncrement,1.0f));

	//Modify the position and target
	SetPosition(v3CameraPosition + v3Translate);
	SetTarget(v3CameraTarget + v3Translate);
}

void MyCamera::MoveSideways(float fIncrement) {
	//Make a translateion vector3 in the camera's orientation along the x-axis
	vector3 v3Translate = vector3(ToMatrix4(qOrientation) * vector4(fIncrement, 0.0f, 0.0f,1.0f));

	//Modify the position and target
	SetPosition(v3CameraPosition + v3Translate);
	SetTarget(v3CameraTarget + v3Translate);
}

void MyCamera::MoveVertical(float fIncrement) {
	//Make a translateion vector3 in the camera's orientation along the y-axis
	vector3 v3Translate = vector3(ToMatrix4(qOrientation) * vector4(0.0f, fIncrement, 0.0f, 1.0f));

	//Modify the position and target
	SetPosition(v3CameraPosition + v3Translate);
	SetTarget(v3CameraTarget + v3Translate);
}

void MyCamera::ChangePitch(float fIncrement) {
	//Create a rotation quaternion about the x-axis
	quaternion qPitch = glm::angleAxis(fIncrement, REAXISX);
	//Modify the orientation
	qOrientation = qOrientation * qPitch;
}

void MyCamera::ChangeRoll(float fIncrement) {
	//Create a rotation quaternion about the z-axis
	quaternion qRoll = glm::angleAxis(fIncrement, REAXISZ);
	//Modify the orientation
	qOrientation = qOrientation * qRoll;
}

void MyCamera::ChangeYaw(float fIncrement) {
	//Create a rotation quaternion about the y-axis
	quaternion qYaw = glm::angleAxis(fIncrement, REAXISY);
	//Modify the orientation
	qOrientation = qOrientation * qYaw;
}