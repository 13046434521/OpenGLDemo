#pragma once

#include "ggl.h"

GLuint compileShader(GLenum shaderType, const char *fsShader);

GLuint createProgram(GLuint vsShader,GLuint fsShader);

void checkGLError();