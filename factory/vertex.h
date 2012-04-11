/*
** Factory Library - Vertex
** RCa, 2007
*/

#ifndef VERTEX_H_
#define VERTEX_H_

#ifdef __cplusplus
extern "C" {
#endif

#define VERTEX_COUNT_KEYS		512

#define VERTEX_KEY_CAPTURE()	({ glVertex.input.keyPending = 0; glVertex.input.keyLast; })
#define VERTEX_KEY_HIT(K)		({ char value = glVertex.input.keys[(int)(K)]; glVertex.input.keys[(int)(K)] = 0; value; })
#define VERTEX_KEY_LAST()		(glVertex.input.keyLast)
#define VERTEX_KEY_PENDING()	(glVertex.input.keyPending)
#define VERTEX_KEY_PRESSED(K)	(glVertex.input.keys[(int)(K)])
#define VERTEX_KEY_RESET(K)		({ glVertex.input.keys[(int)(K)] = 0; })

#define VERTEX_TIME_FPS			1000

#define VERTEX_USE_SDL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__WIN32__)
	#define VERTEX_SYS_WINDOWS

	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>

	typedef int	(APIENTRY* PFNWGLSWAPINTERVALFARPROC) (int);
#elif defined(__APPLE__) && defined(__MACH__)
	#define VERTEX_SYS_MACOSX

	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else
	#define VERTEX_SYS_UNIX

	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#if defined(VERTEX_USE_SDL)
	#include <SDL/SDL.h>

	#define VERTEX_KEY_BACKSPACE	SDLK_BACKSPACE
	#define VERTEX_KEY_BUTTON_L		SDL_BUTTON_LEFT
	#define VERTEX_KEY_BUTTON_M		SDL_BUTTON_MIDDLE
	#define VERTEX_KEY_BUTTON_R		SDL_BUTTON_RIGHT
	#define VERTEX_KEY_DOWN			SDLK_DOWN
	#define	VERTEX_KEY_ESCAPE		SDLK_ESCAPE
	#define VERTEX_KEY_LEFT			SDLK_LEFT
	#define VERTEX_KEY_RIGHT		SDLK_RIGHT
	#define	VERTEX_KEY_SPACE		SDLK_SPACE
	#define VERTEX_KEY_UP			SDLK_UP
#elif defined(VERTEX_SYS_WINDOWS)
	#define VERTEX_CLASS_NAME		"VertexApp"

	#define VERTEX_KEY_BACKSPACE	VK_BACK
	#define VERTEX_KEY_BUTTON_L		VK_LBUTTON
	#define VERTEX_KEY_BUTTON_M		VK_MBUTTON
	#define VERTEX_KEY_BUTTON_R		VK_RBUTTON
	#define VERTEX_KEY_DOWN			VK_DOWN
	#define	VERTEX_KEY_ESCAPE		VK_ESCAPE
	#define VERTEX_KEY_LEFT			VK_LEFT
	#define VERTEX_KEY_RIGHT		VK_RIGHT
	#define	VERTEX_KEY_SPACE		VK_SPACE
	#define VERTEX_KEY_UP			VK_UP
#else
	#error Neither SDL nor Windows mode are used
#endif

enum	VertexDimention
{
	VERTEX_DIMENTION_3D,
	VERTEX_DIMENTION_2D
};

struct				VertexInput
{
	unsigned int	keyLast;
	char			keyPending;
	char			keys[VERTEX_COUNT_KEYS];
	int				mouseAx;
	int				mouseAy;
	char			mouseGrabbed;
	char			mousePrev;
	int				mouseRx;
	int				mouseRy;
};

struct						VertexVideo
{
#if defined(VERTEX_USE_SDL)
	SDL_Surface*			surface;
#elif defined(VERTEX_SYS_WINDOWS)
	char					fullscreen;
	HDC						hDC;
	HGLRC					hRC;
	HWND					hWnd;
	WNDCLASS				wc;
#endif
	enum VertexDimention	dimention;
	int						height;
	int						width;
};

struct					Vertex
{
	struct VertexInput	input;
	struct VertexVideo	video;
	unsigned int		time;
	float				factor;
	float				fps;
	unsigned int		fpsCount;
	unsigned int		fpsTime;
	float				speed;
	char				exit;
	char				ready;
};

extern struct Vertex	glVertex;

int		vertexInit (int, int, int, char);
int		vertexLoop (GLuint);
void	vertexSetDimention (enum VertexDimention);
void	vertexSetMouse (char, char);
void	vertexSetSize (GLuint, GLuint);
void	vertexSetVSync (int);
void	vertexSetWindow (const char*, const char*);
void	vertexStop (void);

#ifdef __cplusplus
}
#endif

#endif
