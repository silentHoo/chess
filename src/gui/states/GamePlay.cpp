#include <iostream>
#include <SDL.h>

#include "gui/states/GamePlay.h"
#include "gui/Menu2DItem.h"
#include "gui/StateMachine.h"
#include "gui/GuiWindow.h"
#include "gui/AssimpHelper.h"
#include "gui/AnimationHelper.h"
#include "gui/ObjectHelper.h"

using namespace std;

GamePlay::GamePlay() : fsm(StateMachine::getInstance()) {
	m_nextState = States::KEEP_CURRENT;
}

void GamePlay::enter() {
	std::cout << "entered GamePlay" << std::endl;

	// ===== set background color =====
	glClearColor(0.0, 0.0, 0, 1);

	// ===== AnimationHelper =====
	animationHelper = make_shared<AnimationHelper>(1000);

	// ===== init OpenGL =====
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);									// activate depth testing with Z-buffer
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// specify implementation-specific hints
	glEnable(GL_COLOR_MATERIAL);

	// ===== config the lights =====
	glEnable(GL_LIGHTING);

	// Create light components.
	ambientLight[0] = 0.0f;
	ambientLight[1] = 0.0f;
	ambientLight[2] = 0.0f;
	ambientLight[3] = 1.0f;

	diffuseLight[0] = 1.0f;
	diffuseLight[1] = 1.0f;
	diffuseLight[2] = 1.0f;
	diffuseLight[3] = 1.0f;

	specularLight[0] = 0.0f;
	specularLight[1] = 0.0f;
	specularLight[2] = 0.0f;
	specularLight[3] = 1.0f;

	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	m_lightpos1[0] = 0.0f;
	m_lightpos1[1] = 120.0f;
	m_lightpos1[2] = 0.0f;
	m_lightpos1[3] = 1.0f;

	m_lightpos2[0] = 108.0f;
	m_lightpos2[1] = 100.0f;
	m_lightpos2[2] = 108.0f;
	m_lightpos2[3] = 1.0f;

	m_lightpos3[0] = -108.0f;
	m_lightpos3[1] = 100.0f;
	m_lightpos3[2] = -108.0f;
	m_lightpos3[3] = 1.0f;

	m_lightpos4[0] = -108.0f;
	m_lightpos4[1] = 100.0f;
	m_lightpos4[2] = 108.0f;
	m_lightpos4[3] = 1.0f;

	// moved light0 to draw

	glLightfv(GL_LIGHT1, GL_POSITION, m_lightpos2);
	glLightfv(GL_LIGHT2, GL_POSITION, m_lightpos3);
	glLightfv(GL_LIGHT3, GL_POSITION, m_lightpos4);

	// smoothing the light
	glShadeModel(GL_SMOOTH);

	// ===== create a whole ChessSet =====
	chessSet = make_shared<ChessSet>();

	// ===== create OGL lists =====
	m_cube1 = ObjectHelper::createCubeList(4, m_lightpos1[0], m_lightpos1[1], m_lightpos1[2]);
	m_cube2 = ObjectHelper::createCubeList(4, m_lightpos2[0], m_lightpos2[1], m_lightpos2[2]);
	m_cube3 = ObjectHelper::createCubeList(4, m_lightpos3[0], m_lightpos3[1], m_lightpos3[2]);
	m_cube4 = ObjectHelper::createCubeList(4, m_lightpos4[0], m_lightpos4[1], m_lightpos4[2]);

	moveCamera = false;
	m_rotateFrom = 0;
	m_rotateTo = 180;

	// debug
	debugText = "light 0 on";
	//cameraView = 0;
}

AbstractState* GamePlay::run() {
	// on demand event handling
	if (fsm.eventmap.keyUp) {
		glDisable(GL_LIGHT0);
	}

	if (fsm.eventmap.keyRight) {
		
	}

	if (fsm.eventmap.keyDown) {
		glEnable(GL_LIGHT0);
	}

	if (fsm.eventmap.keyLeft) {
		// avoid multiple triggering
		if (!moveCamera) {
			animationHelper->reset();
			moveCamera = true;
		}
	}

	if (fsm.eventmap.mouseMoved) {
		
	}

	if (fsm.eventmap.mouseDown) {
		
	}

	if (fsm.eventmap.mouseUp) {
		if (debugText == "light 0 on") {
			glDisable(GL_LIGHT0);
			debugText = "light 0 off";
		}
		else {
			glEnable(GL_LIGHT0);
			debugText = "light 0 on";
		}
		/*
		if (debugText == "ambientLight") {
			debugText = "diffuseLight";

			ambientLight[0] = 0.0f;
			ambientLight[1] = 0.0f;
			ambientLight[2] = 0.0f;
			ambientLight[3] = 1.0f;

			diffuseLight[0] = 1.0f;
			diffuseLight[1] = 1.0f;
			diffuseLight[2] = 1.0f;
			diffuseLight[3] = 1.0f;

			specularLight[0] = 0.0f;
			specularLight[1] = 0.0f;
			specularLight[2] = 0.0f;
			specularLight[3] = 1.0f;
		}
		else if (debugText == "diffuseLight") {
			debugText = "specularLight";

			ambientLight[0] = 0.0f;
			ambientLight[1] = 0.0f;
			ambientLight[2] = 0.0f;
			ambientLight[3] = 0.0f;

			diffuseLight[0] = 0.0f;
			diffuseLight[1] = 0.0f;
			diffuseLight[2] = 0.0f;
			diffuseLight[3] = 1.0f;

			specularLight[0] = 1.0f;
			specularLight[1] = 1.0f;
			specularLight[2] = 1.0f;
			specularLight[3] = 1.0f;
		}
		else if (debugText == "specularLight") {
			debugText = "ambientLight";

			ambientLight[0] = 1.0f;
			ambientLight[1] = 1.0f;
			ambientLight[2] = 1.0f;
			ambientLight[3] = 1.0f;

			diffuseLight[0] = 0.0f;
			diffuseLight[1] = 0.0f;
			diffuseLight[2] = 0.0f;
			diffuseLight[3] = 1.0f;

			specularLight[0] = 0.0f;
			specularLight[1] = 0.0f;
			specularLight[2] = 0.0f;
			specularLight[3] = 1.0f;
		}

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);

		glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight);

		glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight);
		*/

		/* switch camera view
		switch (cameraView) {
		case 0:
			// frontal
			debugText = "front view";
			fsm.window->m_cameraAngleY = 0;
			fsm.window->m_cameraAngleX = 0;
			fsm.window->m_cX = 0;
			fsm.window->m_cY = 0;
			fsm.window->m_cZ = 100;
			break;
		case 1:
			// right
			debugText = "right view";
			fsm.window->m_cameraAngleY = -90;
			fsm.window->m_cameraAngleX = 0;
			fsm.window->m_cX = 100;
			fsm.window->m_cY = 0;
			fsm.window->m_cZ = 0;
			break;
		case 2:
			// top
			debugText = "top view";
			fsm.window->m_cameraAngleY = 0;
			fsm.window->m_cameraAngleX = 90;
			fsm.window->m_cX = 0;
			fsm.window->m_cY = 100;
			fsm.window->m_cZ = 0;
			break;
		default:
			break;
		}

		cameraView = ++cameraView % 3;*/
	}

	if (fsm.eventmap.keyEscape) {
		onBackToMenu();
	}

	this->draw();

	AbstractState* nextState;
	switch (m_nextState) {
	case States::BACK_TO_MENU:
		nextState = new MenuMain();
		break;
	case States::KEEP_CURRENT:
		nextState = this;
		break;
	default:
		nextState = this;
		break;
	}

	return nextState;
}

void GamePlay::draw() {
	// 2D
	fsm.window->set2DMode();
	fsm.window->printText(10, fsm.window->getHeight() - 30, 1.0, 1.0, 1.0, "Game has been started ...");

	// 3D
	fsm.window->set3DMode();

	// skybox: @todo

	// chessboard and models
	chessSet->draw();

	// draw coordinate system
	//drawCoordinateSystem();

	// rotate camera
	if (moveCamera) {
		rotateCamera();
	}

	// visualize light position
	glCallList(m_cube1);
	glCallList(m_cube2);
	glCallList(m_cube3);
	glCallList(m_cube4);

	// lights
	GLfloat lightDir0[] = { 0.0, -1.0, 0.0 };
	GLfloat exponent[] = { 0.0 };
	GLfloat angle[] = { 180.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, m_lightpos1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir0);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, exponent);
	glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, angle);

	// debug info
	fsm.window->printText(100, 100, 1, 0, 0, debugText);
}

void GamePlay::drawCoordinateSystem() {
	glPushMatrix();
		glLineWidth(5.0f);
		glBegin(GL_LINES);
			// x
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(-30.0f, 0.0f, 0.0f);
			glVertex3f(30.0f, 0.0f, 0.0f);

			// y
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, -30.0f, 0.0f);
			glVertex3f(0.0f, 30.0f, 0.0f);

			// z
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, -30.0f);
			glVertex3f(0.0f, 0.0f, 30.0f);
		glEnd();
	glPopMatrix();
}

void GamePlay::rotateCamera() {
	animationHelper->setStartNowOrKeepIt();

	if (animationHelper->hasStopped()) {
		moveCamera = false;

		m_rotateFrom = (m_rotateFrom + 180) % 360;
		m_rotateTo = (m_rotateFrom + 180) % 360;
		return;
	}

	float angleDegree = animationHelper->easeOutSine(m_rotateFrom, m_rotateTo);
	float angleRadian = angleDegree * (M_PI / 180.0);

	std::cout << m_rotateFrom << " -> " << m_rotateTo << " @ " << angleDegree << std::endl;

	float newCameraX = sinf(angleRadian) * fsm.window->getCameraDistanceToOrigin();
	float newCameraZ = cosf(angleRadian) * fsm.window->getCameraDistanceToOrigin();
	float rotationY = (atan2(newCameraX, -newCameraZ) * 180 / M_PI) - 180;

	fsm.window->m_cameraAngleY = rotationY;
	fsm.window->m_cX = newCameraX;
	fsm.window->m_cZ = newCameraZ;
}

void GamePlay::onBackToMenu() {
	std::cout << "go back to menu" << std::endl;
	
	m_nextState = States::BACK_TO_MENU;
}

void GamePlay::exit() {
	std::cout << "left GamePlay!" << std::endl;
}