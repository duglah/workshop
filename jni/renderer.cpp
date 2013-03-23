
#include <jni.h>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOG_TAG "OpenGL"

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    __android_log_print(ANDROID_LOG_INFO,LOG_TAG,"GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,"after %s() glError (0x%x)\n", op, error);
    }
}

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,"Could not compile shader %d:\n%s\n",shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,"Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

char gFragmentShader[] =
    "precision mediump float;\n"
	"uniform vec4 vColor;\n"
    "void main() {\n"
    "  gl_FragColor = vColor;\n"
    "}\n";



GLuint gProgram;
GLuint gvPositionHandle;
GLuint gvColorHandle;

bool setupGraphics(int w, int h) {
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        return false;
    }

    glViewport(0, 0, w, h);

    glClearColor(1.0f,1.0f,1.0f,1.0f);
    return true;
}

GLfloat gTriangleVertices[] = {
		0.0f, 0.5f,
		-0.5f, -0.5f,
        0.5f, -0.5f
};

GLfloat gColor[] = {
		1.0f,0.0f,0.0f,1.0f
};

const GLushort gTriangleDrawOrder[] ={0,1,2};

void renderFrame() {

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(gvPositionHandle);

    gvColorHandle = glGetUniformLocation(gProgram,"vColor");
    glUniform4fv(gvColorHandle,1,gColor);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_SHORT,gTriangleDrawOrder);
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_helloopengljni_CustomRenderer_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_example_helloopengljni_CustomRenderer_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_example_helloopengljni_HelloOpenGLJNIActivity_setColor(JNIEnv* env, jobject obj,jfloat r, jfloat g, jfloat b);
};

JNIEXPORT void JNICALL Java_com_example_helloopengljni_CustomRenderer_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_example_helloopengljni_CustomRenderer_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}

JNIEXPORT void JNICALL Java_com_example_helloopengljni_HelloOpenGLJNIActivity_setColor(JNIEnv* env, jobject obj,jfloat r, jfloat g, jfloat b){
	gColor[0] = r;
	gColor[1] = g;
	gColor[2] = b;
}
