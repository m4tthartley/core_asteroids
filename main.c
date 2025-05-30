//
//  Created by Matt Hartley on 27/05/2025.
//  Copyright 2025 GiantJelly. All rights reserved.
//


#include <core/sysvideo.h>
#define CORE_IMPL
#include <core/core.h>
#include <core/math.h>

#ifdef __APPLE__
#	define GL_SILENCE_DEPRECATION 1
#	include <OpenGL/gl.h>
#	include <OpenGL/glu.h>
#endif
#ifdef __WIN32__
#	include <gl/gl.h>
#	include <gl/glu.h>
#endif

vec3_t shipMesh[] = {
	{-0.4f, -0.5f},
	{ 0.0f, -0.25f},
	{ 0.4f, -0.5f},
	{ 0.0f,  0.5f},
	{-0.4f, -0.5f},
};

vec2_t playerPos = {0};
vec2_t playerSpeed = {0};
float playerRot = 0;

void CheckGLError()
{
	// char* err = gluErrorString(glGetError());
	GLenum err = glGetError();
	char* errstr = gluErrorString(err);
	assert(err == GL_NO_ERROR);
}

int main()
{
	sys_window_t window;
	sys_init_window(&window, "Asteroids", 1280, 720, WINDOW_CENTERED);
	sys_init_opengl(&window);

	CheckGLError();

	for (;;) {
		sys_poll_events(&window);

		static float color = 0.0f;
		color = fmodf(color + 0.01f, 1.0f);
		glClearColor(color, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		CheckGLError();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		CheckGLError();
		float aspect = (float)window.fbWidth / (float)window.fbHeight;
		glOrtho(-10*aspect, 10*aspect, -10, 10, -10, 10);
		CheckGLError();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		CheckGLError();

		// glColor4f(1, 1, 1, 1);
		// glBegin(GL_QUADS);
		// glVertex2f(-0.5f, -0.5f);
		// glVertex2f( 0.5f, -0.5f);
		// glVertex2f( 0.5f,  0.5f);
		// glVertex2f(-0.5f,  0.5f);
		// glEnd();

		if (window.keyboard[KEY_LEFT].down) {
			playerRot += 0.03f;
		}
		if (window.keyboard[KEY_RIGHT].down) {
			playerRot -= 0.03f;
		}
		if (window.keyboard[KEY_UP].down) {
			float len = len2(playerSpeed);
			playerSpeed.x -= sinf(playerRot) * (0.001f);
			playerSpeed.y += cosf(playerRot) * (0.001f);
		}

		playerPos = add2(playerPos, playerSpeed);
		playerSpeed = mul2f(playerSpeed, 0.99f);
		glTranslatef(playerPos.x, playerPos.y, 0);
		glRotatef(todeg(playerRot), 0, 0, 1);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_LINE_STRIP);
		for (int i=0; i<array_size(shipMesh); ++i) {
			glVertex2f(shipMesh[i].x, shipMesh[i].y);
		}
		glEnd();
		
		CheckGLError();

		sys_present_opengl(&window);
	}
}
