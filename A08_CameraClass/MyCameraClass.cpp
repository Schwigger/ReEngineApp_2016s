#include "MyCameraClass.h"

MyCamera::MyCamera() {
	m4View = IDENTITY_M4;
	m4Projection = IDENTITY_M4;

	SetPosition(vector3(0.0f));
	SetTarget(vector3(0.0f));
	SetUp(vector3(0.0f));
}

MyCamera::MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Up) {
	m4View = IDENTITY_M4;
	m4Projection = IDENTITY_M4;

	SetPosition(a_v3Position);
	SetTarget(a_v3Target);
	SetUp(a_v3Up);
}

MyCamera::~MyCamera() {}

matrix4 MyCamera::GetView(void) {
	
	vector3 direction = glm::normalize(v3CameraPosition - v3CameraTarget);
	vector3 right = glm::normalize(glm::cross(vector3(0.0f, 1.0f, 0.0f), direction));
	vector3 up = glm::cross(direction, right);
	SetUp(up);

	return m4View = ToMatrix4(qOrientation) * glm::lookAt(v3CameraPosition, v3CameraTarget, v3CameraUp);
}

matrix4 MyCamera::GetProjection(bool bOrthographic) {
	if (bOrthographic) {
		m4Projection = glm::ortho(-10.80f, 10.80f, -7.68f, 7.68f, 0.01f, 1000.0f);
	}
	else {
		m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
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

void MyCamera::MoveForward(float fIncrement) {
	vector3 translate = vector3(0.0f, 0.0f, -fIncrement);
	SetPosition(v3CameraPosition + translate);
	SetTarget(v3CameraTarget + translate);
}

void MyCamera::MoveSideways(float fIncrement) {
	vector3 translate = vector3(fIncrement, 0.0f, 0.0f);
	SetPosition(v3CameraPosition + translate);
	SetTarget(v3CameraTarget + translate);
}

void MyCamera::MoveVertical(float fIncrement) {
	vector3 translate = vector3(0.0f, fIncrement, 0.0f);
	SetPosition(v3CameraPosition + translate);
	SetTarget(v3CameraTarget + translate);
}

void MyCamera::ChangePitch(float fIncrement) {
	quaternion qPitch = glm::angleAxis(-fIncrement, vector3(1.0f, 0.0f, 0.0f));
	qOrientation = qOrientation * qPitch;
}

void MyCamera::ChangeRoll(float fIncrement) {
	quaternion qRoll = glm::angleAxis(-fIncrement, vector3(0.0f, 0.0f, 1.0f));
	qOrientation = qOrientation * qRoll;
}

void MyCamera::ChangeYaw(float fIncrement) {
	quaternion qYaw = glm::angleAxis(-fIncrement, v3CameraUp);
	qOrientation = qOrientation * qYaw;
}