/*
    Copyright (c) 2013-2014, Patrick Hillert <silent@gmx.biz>

    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MODEL_H
#define MODEL_H

#include "gui/AssimpHelper.h"

/**
 * @brief Representing a chess figure (e.g. King, Queen, ...).
 */
class Model {
public:
    //! Possible model colors.
    enum Color {
        BLACK,
        WHITE
    };

    /**
     * @brief Loads the model from the filesystem.
     * @param file The filename with directory relative to the game's executable file.
     */
    Model(std::string file);

    /**
     * @brief Imports the model from filesystem.
     */
    void loadScene();

    /**
     * @brief Corrects the model positioning if the model (in the given file) is not proper
     * located at 0/0/0 local space coordinates, the rotation or the scaling factor is wrong.
     * @note This should only be used if there's no proper model file available.
     * @param localX Sets the local x coordinate.
     * @param localY Sets the local y coordinate.
     * @param localZ Sets the local z coordinate.
     * @param scaleFactor The scaling factor to shrink or enlarge.
     * @param rotateX The rotation in degree along the x axis.
     * @param rotateY The rotation in degree along the y axis.
     * @param rotateZ The rotation in degree along the z axis.
     */
    void setCorrectionValues(int localX, int localY, int localZ, float scaleFactor, int rotateX, int rotateY, int rotateZ);

    /**
     * @brief Sets the models color.
     * @param color The color of the model.
     */
    void setColor(Color color);

    /**
     * @brief Sets a new global position (world coordinates) for the model.
     * @param globalX The global x coordinate.
     * @param globalY The global y coordinate.
     * @param globalZ The global z coordinate.
     */
    void setPosition(int globalX, int globalY, int globalZ);

    /**
     * @brief Draws the model at configured world coordinates.
     */
    void draw();

private:
    //! Filename (an path) relative to the executable, which contains the meshes.
    std::string m_file;

    //! Color of the model.
    Color m_color;

    //! Structure for the model's world coordinates.
    struct Position {
        int x;
        int y;
        int z;
    };

    //! The model's position in world coordinates.
    Position m_position;

    //! Scaling factor of the model.
    float m_correctScaling;

    //! The local correction values for correcting unproper model coordinates.
    Position m_correctPosition;

    //! The local correction values for correcting unproper model rotation.
    Position m_correctRotation;

    //! Pointer to the AssimpHelper, which holds the meshes.
    AssimpHelperPtr model;
};

using ModelPtr = std::shared_ptr<Model>; // Shared pointer for better garbage handling.

#endif // MODEL_H
