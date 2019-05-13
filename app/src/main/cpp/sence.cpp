#include "sence.h"
#include "utils.h"

GLuint vbo;
GLuint program;
GLint projectLocation, viewLocation, modelLocation, positionLocation, colorLocation;
glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
const char *vsCode = "attribute vec4 a_Position;\n"
                     "uniform mat4 M;"
                     "uniform mat4 V;"
                     "uniform mat4 P;"
                     "void main() \n"
                     "{\n"
                     "gl_Position=P*V*M*a_Position;\n"
                     "}\n";

const char *fsCode = "uniform vec4 u_Color;\n"
                     "void main()\n"
                     "{\n"
                     "gl_FragColor=u_Color;"
                     "}\n";
float color[] = {1.0f, 0.75f, 0.145f, 1.0f};

void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    float data[] = {
            -0.2f, -0.2f, -1.0f, 1.0f,
            0.2f, -0.2f, -1.0f, 1.0f,
            0.0f, 0.2f, -1.0f, 1.0f
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vsShader = compileShader(GL_VERTEX_SHADER, vsCode);
    GLuint fsShader = compileShader(GL_FRAGMENT_SHADER, fsCode);

    program = createProgram(vsShader, fsShader);

    colorLocation = glGetUniformLocation(program, "u_Color");
    positionLocation = glGetAttribLocation(program, "a_Position");
    modelLocation = glGetUniformLocation(program, "M");
    viewLocation = glGetUniformLocation(program, "V");
    projectLocation = glGetUniformLocation(program, "P");
}

void changeViewPort(float width, float height) {
    glViewport(0, 0, width, height);

    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1000.0f);

}

void drawOneFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glUniform4f(colorLocation,1.0f, 0.75f, 0.145f, 1.0f);//     glUniform4fv(colorLocation, 1, color);

    glEnableVertexAttribArray(positionLocation);

    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    glDisableVertexAttribArray(positionLocation);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
}