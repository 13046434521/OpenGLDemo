#include "utils.h"

#define info(...)__android_log_print(ANDROID_LOG_INFO,"JTL_C++",__VA_ARGS__);
GLuint compileShader(GLenum shaderType, const char *fsShader) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &fsShader, nullptr);
    glCompileShader(shader);

    GLint compileResult=GL_TRUE;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compileResult);
    if (!compileResult){
        char szLog[1024]={0};
        GLsizei logLen=0;
        glGetShaderInfoLog(shader,1024,&logLen,szLog);
        info("Compile Shader:%s\n", szLog);
        glDeleteShader(shader);

        shader=0;
    }

    return shader;
}

GLuint createProgram(GLuint vsShader,GLuint fsShader) {
    GLuint program=glCreateProgram();
    glAttachShader(program,vsShader);
    glAttachShader(program,fsShader);
    glLinkProgram(program);
    glUseProgram(program);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    GLint compileResult=GL_TRUE;
    glGetProgramiv(program,GL_LINK_STATUS,&compileResult);
    if (!compileResult){
        char szLog[1024]={0};
        GLsizei logLen=0;
        glGetProgramInfoLog(program,1024,&logLen,szLog);

        info("Create Program:%s\n", szLog);

        glDeleteProgram(program);
    }

    return program;
}

char *loadFileContent(AAssetManager *aAssetManager, char *path) {
    char *fileContent = nullptr;
    AAsset *aAsset = AAssetManager_open(aAssetManager, path, AASSET_MODE_UNKNOWN);
    if (aAsset == nullptr) {
        info("loadFile failed .")
        return 0;
    }

    int length = AAsset_getLength(aAsset);
    fileContent = new char[length + 1];
    AAsset_read(aAsset, fileContent, length);
    fileContent[length] = '\0';

    AAsset_close(aAsset);

    return fileContent;
}