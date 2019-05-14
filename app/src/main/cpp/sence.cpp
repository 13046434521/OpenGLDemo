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
    //创建VBO，在GPU显存上开辟data大小的内存，并将数据从CPU传到GPU上。解绑GL_ARRAY_BUFFER
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //编译Shader
    GLuint vsShader = compileShader(GL_VERTEX_SHADER, vsCode);
    GLuint fsShader = compileShader(GL_FRAGMENT_SHADER, fsCode);
    //创建program,绑定顶点着色器，片元着色器
    program = createProgram(vsShader, fsShader);
    //获取program中着色器中相对应参数的句柄
    colorLocation = glGetUniformLocation(program, "u_Color");
    positionLocation = glGetAttribLocation(program, "a_Position");
    modelLocation = glGetUniformLocation(program, "M");
    viewLocation = glGetUniformLocation(program, "V");
    projectLocation = glGetUniformLocation(program, "P");
}

void changeViewPort(float width, float height) {
    glViewport(0, 0, width, height);
    //计算投影矩阵（透视投影）
    projectionMatrix = glm::perspective(45.0f, width / height, 0.1f, 1000.0f);

}

void drawOneFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    //清空缓存
    glUseProgram(program);    //使用program
    glBindBuffer(GL_ARRAY_BUFFER, vbo);     //绑定vbo

    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));//通过句柄，设置model矩阵
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));//通过句柄，设置view矩阵
    glUniformMatrix4fv(projectLocation, 1, GL_FALSE,
                       glm::value_ptr(projectionMatrix));//通过句柄，设置projection矩阵

    glUniform4f(colorLocation, 1.0f, 0.75f, 0.145f,
                1.0f);//     glUniform4fv(colorLocation, 1, color); 设置颜色的两种方式（土黄色）

    glEnableVertexAttribArray(
            positionLocation);    //启用positionLocation属性。（shader中attribute参数可以，uniform不能）

    glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4,
                          0);//通知OpenGL，positionLocation句柄对应的shader中的gl_Position。如何渲染。
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);//渲染，三角形，起始位置，数量

    glDisableVertexAttribArray(positionLocation);//关闭positionLocation

    glBindBuffer(GL_ARRAY_BUFFER, 0);//将帮GL_ARRAY_BUFFER
    glUseProgram(0);//重置OpenGL的program
}