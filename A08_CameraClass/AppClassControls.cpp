#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;

#pragma region ON_KEY_PRESS_RELEASE
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
		bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
		bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if (bModifier)
		fSpeed *= 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_MyCamera->MoveForward(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_MyCamera->MoveForward(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_MyCamera->MoveSideways(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_MyCamera->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_MyCamera->MoveVertical(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		m_MyCamera->ResetOrientation();
		m_MyCamera->ResetPosition();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_MyCamera->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		m_MyCamera->ChangePitch(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		m_MyCamera->ChangePitch(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		m_MyCamera->ChangeYaw(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		m_MyCamera->ChangeYaw(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		m_MyCamera->ChangeRoll(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		m_MyCamera->ChangeRoll(fSpeed);
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));

	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));
#pragma endregion
}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
		if (bLeft)
		{
			//Get the Position and direction of the click on the screen
			std::pair<vector3, vector3> pair =
				m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			float fDistance = 0;//Stores the distance to the first colliding object
			m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);
		}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
