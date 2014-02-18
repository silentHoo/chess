#include "ChessSet.h"
#include "AnimationHelper.h"

#include <algorithm>
#include <iostream>
#include <SDL.h>

using namespace std;

ChessSet::ChessSet()
	: m_tileWidth(24) 
	, m_tileHeight(2)
	, m_turnMoveShowDuration(2000)
	, m_turnMoveShownSince(0)
	, m_lastTurnAvailable(false) {

	// all external resources to load
	m_extResources = {
		"resources/3dmodels/king.3DS",
		"resources/3dmodels/queen.3DS",
		"resources/3dmodels/bishop.3DS",
		"resources/3dmodels/knight.3DS",
		"resources/3dmodels/rook.3DS",
		"resources/3dmodels/pawn.3DS"
	};

	m_extCorrectionValues = { {
        { 61, 12, 0, 1, -90, 0, 0 },	// king
        { 40, 12, 0, 1, -90, 0, 0 },	// queen
        { 1, 21, 0, 1, -90, 0, 0 },		// bishop
        { 0, 0, 0, 0.4, -90, 0, 0 },	// knight
        { 20, 12, 0, 1, -90, 0, 0 },	// rook
        { 0, 12, 0, 1, -90, 0, 0 }		// pawn
    } };
}

ChessSet::~ChessSet() {
	m_loadCallback.disconnect_all_slots();
}

int ChessSet::getResourcesCount() {
	return static_cast<int>(m_extResources.size()) + 1;	// +1 for the board
}

void ChessSet::loadResources() {
	// load models
	int i = 0;
	for (auto &resName : m_extResources) {
		// propagate what is loaded
		m_loadCallback(resName);

		// create the model
		m_models[i] = make_shared<Model>(resName);

		// set the correction values for the model
		auto& cor = m_extCorrectionValues[i];
		m_models[i]->setCorrectionValues(
            cor.x, cor.y, cor.z,
            cor.scale,
            cor.rotX, cor.rotY, cor.rotZ
        );

		// cache the model in a display list

		// white models
		m_models[i]->setColor(Model::Color::WHITE);
		m_modelList[i] = glGenLists(1);

		glNewList(m_modelList[i], GL_COMPILE);
			m_models[i]->draw();
		glEndList();

		// black models
		m_models[i]->setColor(Model::Color::BLACK);
		m_modelList[i+6] = glGenLists(1);

		glNewList(m_modelList[i+6], GL_COMPILE);
			m_models[i]->draw();
		glEndList();

		++i;
	}

	// prepare board list for faster rendering
	m_loadCallback("Preparing chessboard and models ...");
	createChessBoardList();
}

// triggers the callback, when a new source has been loaded
void ChessSet::registerLoadCallback(const boost::function<void(std::string)>& slot) {
	m_loadCallback.connect(slot);
}

void ChessSet::setState(std::array<Piece, 64> state, PlayerColor lastPlayer, Turn lastTurn) {
	m_state = state;
	m_lastPlayer = lastPlayer;
	m_lastTurn = lastTurn;

	m_lastTurnAvailable = true;

	if (m_lastTurn.action == Turn::Action::Move) {
		m_turnMoveShownSince = SDL_GetTicks();
	}
}

void ChessSet::draw() {
	drawModels();
	drawBoard();
}

void ChessSet::drawModels() {
	// if a new turn is made, create a new model list without the turn dependent models
	if (m_lastTurnAvailable) {
		createModelsList(true);
		m_lastTurnAvailable = false;
	}

	// do not animate anything if time is up
	if (m_turnMoveShownSince < (SDL_GetTicks() - m_turnMoveShowDuration)) {
		animateModelTurn();
	} else {
		// if time is up -> create a model list with all models
		createModelsList(false);
	}
	
	glCallList(m_modelsList);
}

void ChessSet::drawBoard() {
	glCallList(m_boardList);
}

ChessSet::Coord3D ChessSet::calcCoordinatesForTileAt(Field which) {
	Coord3D coord;

	int col = static_cast<int>(which) % 8;
	int row = 7 - static_cast<int>(which) / 8;

	coord.x = ((col - 4) * m_tileWidth) + (m_tileWidth / 2);
	coord.y = 0;
	coord.z = ((row - 4) * m_tileWidth) + (m_tileWidth / 2);

	return coord;
}

void ChessSet::drawTileSelectorAt(Field which) {
	Coord3D coord = calcCoordinatesForTileAt(which);
	/*int col = static_cast<int>(which) % 8;
	int row = 7 - static_cast<int>(which) / 8;

	int x, z;
	int y = 0;
	x = ((col - 4) * m_tileWidth) + m_tileWidth / 2;
	z = ((row - 4) * m_tileWidth) + m_tileWidth / 2;*/

	drawTile(coord.x, coord.y, coord.z, false, TileStyle::SELECT);
}

void ChessSet::drawTileTurnOptionAt(Field which) {
	Coord3D coord = calcCoordinatesForTileAt(which);
	drawTile(coord.x, coord.y, coord.z, false, TileStyle::OPTION);
}

/* replace by translation
void ChessSet::moveModelToTile(ModelPtr model, int row, int col) {
	glTranslatef(((row - 4.f) * m_tileWidth) + (m_tileWidth / 2.f), static_cast<float>(m_tileHeight), ((col - 4.f) * m_tileWidth) + (m_tileWidth / 2.f));
}*/

// create the list only the first time
// to update single model positions
void ChessSet::createModelsList(bool withoutTurnDependentModels) {
	// draw all models without the model on position .from and .to
	// these models will be drawn in a separate method with animation
	// -> fade out .to model
	// -> move animation .from model
	m_modelsList = glGenLists(1);
	glNewList(m_modelsList, GL_COMPILE);
		int field = 0;
		for (auto &p : m_state) {
			if (p.type != PieceType::NoType) {
				Coord3D coord = calcCoordinatesForTileAt(static_cast<Field>(field));
				//int col = field % 8;
				//int row = 7 - field / 8;
				
				glPushMatrix();
					
//					if (withoutTurnDependentModels || (field != m_lastTurn.from && field != m_lastTurn.to)) {
						// move model to tile
						//float x = ((col - 4.f) * m_tileWidth) + (m_tileWidth / 2.f);
						//float z = ((row - 4.f) * m_tileWidth) + (m_tileWidth / 2.f);
						glTranslatef(static_cast<float>(coord.x), static_cast<float>(coord.y), static_cast<float>(coord.z));

						// draw model via list index
						int listIndex = p.type + (p.player == PlayerColor::Black ? 6 : 0);
						glCallList(m_modelList[listIndex]);
//					}
					
				glPopMatrix();
			}
			++field;
		}
	glEndList();
}

void ChessSet::animateModelTurn() {
	

}

void ChessSet::createChessBoardList() {
	m_boardList = glGenLists(1);

	glNewList(m_boardList, GL_COMPILE);
		int x = 0;
		int y = 0;
		int z = 0;

		bool oddToggler = false;
		for (int i = -4; i < 4; i++) {
			z = i * m_tileWidth + m_tileWidth / 2;

			for (int j = -4; j < 4; j++) {
				x = j * m_tileWidth + m_tileWidth / 2;
			
				drawTile(x, y, z, oddToggler, TileStyle::NORMAL);
				oddToggler = !oddToggler;
			}

			oddToggler = !oddToggler;
		}
	glEndList();
}

void ChessSet::drawTile(int x, int y, int z, bool odd, TileStyle style) {
	int halfWidth = m_tileWidth / 2;
	int halfHeight = m_tileHeight / 2;

	glPushMatrix();
    glTranslatef(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		
		glBegin(GL_QUADS);
			GLfloat emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };		// example: glowing clock hand (Uhrzeiger) of an alarm clock at night -> we dont need this here
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
			
			GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 0.5f };			// example: this light scattered so often, that it comes from no particular direction but 
																	//          is uniformly distributed in the environment. If you specify no lighting in OpenGL,
																	//          the result is the same as if you define only ambient light.

			switch (style) {
				case NORMAL:
					if (!odd) {
						ambient[0] = 1.0f;
						ambient[1] = 1.0f;
						ambient[2] = 1.0f;
					} else {
						ambient[0] = 0.14f;
						ambient[1] = 0.07f;
						ambient[2] = 0.0f;
					}
					break;
				case SELECT:
					ambient[0] = 0.8f;
					ambient[1] = 0.0f;
					ambient[2] = 0.0f;
					break;
				case OPTION:
					ambient[0] = 0.8f;
					ambient[1] = 0.6f;
					ambient[2] = 0.0f;
					break;
				default:
					break;
			}

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

			GLfloat diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };			// example: this light comes from a certain direction but is reflected homogenously from each point of the surface.
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

			GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };		// example: highlight point
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

			GLfloat shininess[] = { 100 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

			// front face
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3i(halfWidth, halfHeight, halfWidth);	// top right
			glVertex3i(-halfWidth, halfHeight, halfWidth);	// top left
			glVertex3i(-halfWidth, -halfHeight, halfWidth);	// bottom left
			glVertex3i(halfWidth, -halfHeight, halfWidth);	// bottom right

			// left face
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3i(-halfWidth, halfHeight, halfWidth);
			glVertex3i(-halfWidth, halfHeight, -halfWidth);
			glVertex3i(-halfWidth, -halfHeight, -halfWidth);
			glVertex3i(-halfWidth, -halfHeight, halfWidth);

			// back face
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3i(halfWidth, halfHeight, -halfWidth);
			glVertex3i(-halfWidth, halfHeight, -halfWidth);
			glVertex3i(-halfWidth, -halfHeight, -halfWidth);
			glVertex3i(halfWidth, -halfHeight, -halfWidth);

			// right face
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3i(halfWidth, halfHeight, -halfWidth);
			glVertex3i(halfWidth, halfHeight, halfWidth);
			glVertex3i(halfWidth, -halfHeight, halfWidth);
			glVertex3i(halfWidth, -halfHeight, -halfWidth);

			// bottom face
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3i(halfWidth, -halfHeight, halfWidth);
			glVertex3i(-halfWidth, -halfHeight, halfWidth);
			glVertex3i(-halfWidth, -halfHeight, -halfWidth);
			glVertex3i(halfWidth, -halfHeight, -halfWidth);

			// top face
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3i(halfWidth, halfHeight, halfWidth);
			glVertex3i(-halfWidth, halfHeight, halfWidth);
			glVertex3i(-halfWidth, halfHeight, -halfWidth);
			glVertex3i(halfWidth, halfHeight, -halfWidth);
		glEnd();
	glPopMatrix();
}