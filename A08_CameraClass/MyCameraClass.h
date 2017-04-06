#pragma once
#include "RE\ReEng.h"

class MyCamera {
private:
	quaternion qOrientation;

	matrix4 m4View = IDENTITY_M4;
	matrix4 m4Projection = IDENTITY_M4;
	
	vector3 v3CameraPosition = vector3(1.0f);
	vector3 v3CameraTarget = vector3(1.0f);
	vector3 v3CameraUp = vector3(1.0f);

	vector3 v3OriginPosition = vector3(1.0f);
	vector3 v3OriginTarget = vector3(1.0f);
public:
	MyCamera();

	//Constructor with parameters
	MyCamera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

	//Destructor
	~MyCamera();

	//Get the View Matrix
	matrix4 GetView(void);
	/*
		Get the Projection Matrix
		Arguments:
			bOrthographic - choose between a Perspective or Orthographic projection
	*/
	matrix4 GetProjection(bool bOrthographic);

	//Set the Position of the Camera
	void SetPosition(vector3 v3Position);

	//Set the Target of the Camera
	void SetTarget(vector3 v3Target);

	//Set the Up vector of the camera
	void SetUp(vector3 v3Up);

	//Reset the camera to its original position
	void ResetPosition();

	//Reset the camera to it's original orientation
	void ResetOrientation();

	//Move the camera forward or backwards, depending on the "view vector"
	void MoveForward(float fIncrement);

	//Move the camera based on the "right" vector, depending on the "view vector"
	void MoveSideways(float fIncrement);

	//Move the camera up or down, depending on the "up vector"
	void MoveVertical(float fIncrement);

	//Orient the camera by changing its angle in x
	void ChangePitch(float fIncrement);

	//Orient the camera by changing its angle in y
	void ChangeRoll(float fIncrement);

	//Orient the camera by changing its angle in z
	void ChangeYaw(float fIncrement);
};