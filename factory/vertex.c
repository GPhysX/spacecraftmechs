/*
** Factory Library - Vertex
** RCa, 2007
*/

#include "vertex.h"

struct Vertex		glVertex;

#if !defined(VERTEX_USE_SDL) && defined(VERTEX_SYS_WINDOWS)
int					main (int, char* []);

static HINSTANCE	glInstance;

LRESULT CALLBACK	WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT			mousePosition;
	unsigned int	x;
	unsigned int	y;

	switch (message)
	{
		case WM_CREATE:
		case WM_DESTROY:
		break;

		case WM_CLOSE:
			PostQuitMessage (0);
		break;

		case WM_SIZE:
			vertexSetSize (LOWORD (lParam), HIWORD (lParam));
		break;

		case WM_KEYDOWN:
			glVertex.input.keyLast = wParam;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[wParam] = 1;
		break;

		case WM_KEYUP:
			glVertex.input.keys[wParam] = 0;
		break;

		case WM_LBUTTONDOWN:
			glVertex.input.keyLast = 0;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[VK_LBUTTON] = 1;
		break;

		case WM_LBUTTONUP:
			glVertex.input.keys[VK_LBUTTON] = 0;
		break;

		case WM_MBUTTONDOWN:
			glVertex.input.keyLast = 1;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[VK_MBUTTON] = 1;
		break;

		case WM_MBUTTONUP:
			glVertex.input.keys[VK_MBUTTON] = 0;
		break;

		case WM_MOUSEMOVE:
			if (glVertex.input.mouseGrabbed)
			{
				x = glVertex.video.width >> 1;
				y = glVertex.video.height >> 1;

				if (!glVertex.input.mousePrev)
				{
					glVertex.input.mousePrev = 1;

					mousePosition.x = x;
					mousePosition.y = y;
				}
				else
				{
					GetCursorPos (&mousePosition);

					ScreenToClient (glVertex.video.hWnd, &mousePosition);
				}

				glVertex.input.mouseRx = mousePosition.x - x;
				glVertex.input.mouseRy = mousePosition.y - y;
				glVertex.input.mouseAx += glVertex.input.mouseRx;
				glVertex.input.mouseAy += glVertex.input.mouseRy;

				mousePosition.x = x;
				mousePosition.y = y;

				ClientToScreen (glVertex.video.hWnd, &mousePosition);
				SetCursorPos (mousePosition.x, mousePosition.y);

				if (glVertex.input.mouseAx < 0)
					glVertex.input.mouseAx = 0;
				else if (glVertex.input.mouseAx >= glVertex.video.width)
					glVertex.input.mouseAx = glVertex.video.width - 1;

				if (glVertex.input.mouseAy < 0)
					glVertex.input.mouseAy = 0;
				else if (glVertex.input.mouseAy >= glVertex.video.height)
					glVertex.input.mouseAy = glVertex.video.height - 1;
			}
			else
			{
				if (!glVertex.input.mousePrev)
				{
					glVertex.input.mousePrev = 1;
					glVertex.input.mouseRx = 0;
					glVertex.input.mouseRy = 0;
				}
				else
				{
					glVertex.input.mouseRx = LOWORD (lParam) - glVertex.input.mouseAx;
					glVertex.input.mouseRy = HIWORD (lParam) - glVertex.input.mouseAy;
				}

				glVertex.input.mouseAx = LOWORD (lParam);
				glVertex.input.mouseAy = HIWORD (lParam);
			}
		break;

		case WM_RBUTTONDOWN:
			glVertex.input.keyLast = 2;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[VK_RBUTTON] = 1;
		break;

		case WM_RBUTTONUP:
			glVertex.input.keys[VK_RBUTTON] = 0;
		break;

		default:
			return DefWindowProc (hWnd, message, wParam, lParam);
	}

	return 0;
}
#endif

static void	vertexInternalReset (void)
{
	glClearColor (0.0, 0.0, 0.0, 1.0);
	glClearDepth (1.0);
	glClearStencil (0.0);
	glDepthFunc (GL_LESS);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel (GL_SMOOTH);
}

/*
** Create OpenGL window
*/
int		vertexInit (int width, int height, int bpp, char fullscreen)
{
#if defined(VERTEX_USE_SDL)
	const SDL_VideoInfo*	infos;

	memset (&glVertex, 0, sizeof (glVertex));

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		return 1;

	SDL_GL_SetAttribute (SDL_GL_STENCIL_SIZE, 8);

	if ((infos = SDL_GetVideoInfo ()) &&
	    (glVertex.video.surface = SDL_SetVideoMode (width, height, bpp, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | (infos->hw_available ? SDL_HWSURFACE : SDL_SWSURFACE) | (fullscreen ? SDL_FULLSCREEN : SDL_RESIZABLE))))
	{
		vertexInternalReset ();
		vertexSetSize (width, height);

		glVertex.factor = 1;
		glVertex.ready = 1;
		glVertex.time = 0;

		return 0;
	}

	SDL_Quit ();

	return 1;
#elif defined(VERTEX_SYS_WINDOWS)
	DEVMODE					devmode;
	DWORD					dwExStyle;
	DWORD					dwStyle;
	PIXELFORMATDESCRIPTOR	pfd;
	RECT					rect;
	signed long				iFormat;

	memset (&glVertex, 0, sizeof (glVertex));

	if ((glVertex.video.fullscreen = fullscreen))
	{
		memset (&devmode, 0, sizeof (devmode));

		devmode.dmBitsPerPel = bpp;
		devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		devmode.dmPelsWidth = width;
		devmode.dmPelsHeight = height;
		devmode.dmSize = sizeof (devmode);

		if (ChangeDisplaySettings (&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			return 1;

		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = /*WS_OVERLAPPEDWINDOW*/WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	}

	glVertex.video.wc.style = CS_OWNDC;
	glVertex.video.wc.lpfnWndProc = WndProc;
	glVertex.video.wc.cbClsExtra = 0;
	glVertex.video.wc.cbWndExtra = 0;
	glVertex.video.wc.hInstance = glInstance;
	glVertex.video.wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	glVertex.video.wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	glVertex.video.wc.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
	glVertex.video.wc.lpszMenuName = NULL;
	glVertex.video.wc.lpszClassName = VERTEX_CLASS_NAME;

	if (!RegisterClass (&glVertex.video.wc))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 1;

	rect.left = 0;
	rect.right = width - 1;
	rect.top = 0;
	rect.bottom = height - 1;

	AdjustWindowRectEx (&rect, dwStyle, FALSE, dwExStyle);

	if (!(glVertex.video.hWnd = CreateWindowEx (dwExStyle, VERTEX_CLASS_NAME, VERTEX_CLASS_NAME, dwStyle, (GetSystemMetrics (SM_CXSCREEN) - width) >> 1, (GetSystemMetrics (SM_CYSCREEN) - height) >> 1, rect.right - rect.left + 1, rect.bottom - rect.top + 1, NULL, NULL, glInstance, NULL)))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 2;

	if (!(glVertex.video.hDC = GetDC (glVertex.video.hWnd)))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 3;

	memset (&pfd, 0, sizeof (pfd));

	pfd.nSize = sizeof (pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = bpp;
	pfd.cDepthBits = 16;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	if (!(iFormat = ChoosePixelFormat (glVertex.video.hDC, &pfd)))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 4;

	if (!SetPixelFormat (glVertex.video.hDC, iFormat, &pfd))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 5;

	if (!(glVertex.video.hRC = wglCreateContext (glVertex.video.hDC)))
	{
		vertexStop ();

		return 1;
	}

	glVertex.ready = 6;

	if (!wglMakeCurrent(glVertex.video.hDC, glVertex.video.hRC))
	{
		vertexStop ();

		return 1;
	}

	vertexInternalReset ();
	vertexSetSize (width, height);

	glVertex.factor = 1;
	glVertex.ready = 7;
	glVertex.time = 0;

	return 0;
#endif
}

/*
** Update internal values
*/
int		vertexLoop (GLuint wait)
{
#if defined(VERTEX_USE_SDL)
	SDL_Event		event;
	unsigned int	time;

	time = SDL_GetTicks ();

	if (glVertex.time)
	{
		while (time - glVertex.time < wait)
			time = SDL_GetTicks ();

		glVertex.speed = glVertex.factor * (time - glVertex.time);
	}
	else
		glVertex.speed = 0;

	if (glVertex.fpsTime < glVertex.time)
	{
		glVertex.fps = glVertex.fpsCount * 1000 / VERTEX_TIME_FPS;
		glVertex.fpsCount = 0;
		glVertex.fpsTime = glVertex.time + VERTEX_TIME_FPS;
	}

	++glVertex.fpsCount;
	glVertex.input.mouseRx = 0;
	glVertex.input.mouseRy = 0;
	glVertex.time = time;

	while (SDL_PollEvent (&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			glVertex.input.keyLast = event.key.keysym.sym;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[event.key.keysym.sym] = 1;
		}
		else if (event.type == SDL_KEYUP)
			glVertex.input.keys[event.key.keysym.sym] = 0;
		else if (event.type == SDL_MOUSEMOTION)
		{
			glVertex.input.mouseAx = event.motion.x;
			glVertex.input.mouseAy = event.motion.y;
			glVertex.input.mouseRx = event.motion.xrel;
			glVertex.input.mouseRy = event.motion.yrel;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			glVertex.input.keyLast = event.button.button;
			glVertex.input.keyPending = 1;
			glVertex.input.keys[event.button.button] = 1;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			glVertex.input.keys[event.button.button] = 0;
		}
		else if (event.type == SDL_VIDEORESIZE)
			vertexSetSize (event.resize.w, event.resize.h);
		else if (event.type == SDL_QUIT)
			glVertex.exit = 1;
	}

	SDL_GL_SwapBuffers ();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	return glVertex.exit;
#elif defined(VERTEX_SYS_WINDOWS)
	MSG				message;
	unsigned int	time;

	time = GetTickCount ();

	if (glVertex.time)
	{
		while (time - glVertex.time < wait)
			time = GetTickCount ();

		glVertex.speed = glVertex.factor * (time - glVertex.time);
	}
	else
		glVertex.speed = 0;

	if (glVertex.fpsTime < glVertex.time)
	{
		glVertex.fps = glVertex.fpsCount * 1000 / VERTEX_TIME_FPS;
		glVertex.fpsCount = 0;
		glVertex.fpsTime = glVertex.time + VERTEX_TIME_FPS;
	}

	++glVertex.fpsCount;
	glVertex.input.mouseRx = 0;
	glVertex.input.mouseRy = 0;
	glVertex.time = time;

	if (PeekMessage (&message, NULL, 0, 0, PM_REMOVE))
	{
		switch (message.message)
		{
			case WM_QUIT:
				glVertex.exit = 1;
			break;

			default:
				TranslateMessage (&message);
				DispatchMessage (&message);
			break;
		}
	}

	SwapBuffers (glVertex.video.hDC);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	return glVertex.exit;
#endif
}

/*
** Change display mode to 2D or 3D
*/
void	vertexSetDimention (enum VertexDimention dimention)
{
	if ((glVertex.video.dimention = dimention) == VERTEX_DIMENTION_3D)
	{
		glEnable (GL_DEPTH_TEST);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective (80.0f, (float)glVertex.video.width / (float)(glVertex.video.height ? glVertex.video.height : 1), 0.1, 10000.0);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
	}
	else
	{
		glDisable (GL_DEPTH_TEST);
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glOrtho (0, glVertex.video.width, glVertex.video.height, 0, -1, 1);
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
	}
}

/*
** Hide or display mouse cursor
*/
void	vertexSetMouse (char visible, char grabbed)
{
#if defined(VERTEX_USE_SDL)
	SDL_ShowCursor (visible ? SDL_ENABLE : SDL_DISABLE );
	SDL_WM_GrabInput (grabbed ? SDL_GRAB_ON : SDL_GRAB_OFF);
#elif defined(VERTEX_SYS_WINDOWS)
	glVertex.input.mouseGrabbed = grabbed;

	ShowCursor (visible);
#endif
}

/*
** Change window width and height
*/
void	vertexSetSize (GLuint width, GLuint height)
{
	glVertex.video.height = height;
	glVertex.video.width = width;

	glViewport (0, 0, width, height);

	vertexSetDimention (glVertex.video.dimention);
}

/*
** Enable or disable vertical synchronization
*/
void	vertexSetVSync (int sync)
{
#if defined(VERTEX_SYS_WINDOWS)
	PFNWGLSWAPINTERVALFARPROC	wglSwapIntervalEXT;

	if (strstr ((const char*)glGetString (GL_EXTENSIONS), "WGL_EXT_swap_control") != 0)
	{
		wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress ("wglSwapIntervalEXT");

    	if (wglSwapIntervalEXT)
			wglSwapIntervalEXT (sync);
	}
#endif
}

/*
** Change window text and icon
*/
void	vertexSetWindow (const char* title, const char* icon)
{
#if defined(VERTEX_USE_SDL)
	SDL_WM_SetCaption (title, icon);
#elif defined(VERTEX_SYS_WINDOWS)
	SetWindowText (glVertex.video.hWnd, title);

	icon = NULL;
#endif
}

/*
** Destroy OpenGL window
*/
void	vertexStop (void)
{
#if defined(VERTEX_USE_SDL)
	if (glVertex.ready)
	{
		SDL_FreeSurface (glVertex.video.surface);
		SDL_Quit ();

 		glVertex.ready = 0;
	 }
#elif defined(VERTEX_SYS_WINDOWS)
	if (glVertex.video.fullscreen)
		ChangeDisplaySettings (NULL,0);

	if (glVertex.ready > 0)
	{
		if (glVertex.ready > 1)
		{
			if (glVertex.ready > 2)
			{
				if (glVertex.ready > 5)
				{
					if (glVertex.ready > 6)
						wglMakeCurrent(NULL,NULL);

					wglDeleteContext (glVertex.video.hRC);
				}

				ReleaseDC (glVertex.video.hWnd, glVertex.video.hDC);
			}

			DestroyWindow (glVertex.video.hWnd);
		}

		UnregisterClass (VERTEX_CLASS_NAME, glVertex.video.wc.hInstance);
	}

	glVertex.ready = 0;
#endif
}

/*
** Allow Windows programs to be run the same way than Unix ones
*/
#if defined(VERTEX_SYS_WINDOWS)
int APIENTRY	WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance __attribute__((unused)), LPSTR lpCmdLine, int nCmdShow __attribute__((unused)))
{
	char**		arga;
	char**		argv;
	int			argc;
	int			err;
	int			i;

	while (*lpCmdLine != '\0' && *lpCmdLine <= ' ')
		++lpCmdLine;

#if !defined(VERTEX_USE_SDL)
	glInstance = hInstance;
#endif

	argc = 1;
	argv = NULL;

	for (err = -1; err == -1; )
	{
		if (!(arga = (char**)realloc (argv, (argc + 1) * sizeof (*argv))))
			err = 1;
		else
		{
			argv = arga;

			if (*lpCmdLine == '\0')
			{
				argv[0] = "<exename>";
				argv[argc] = NULL;

#if defined(VERTEX_USE_SDL)
				err = SDL_main (argc, argv);
#else
				err = main (argc, argv);
#endif
			}
			else
			{
				for (i = 1; lpCmdLine[i] != '\0' && lpCmdLine[i] > ' '; )
					++i;

				if (!(argv[argc] = malloc ((i + 1) * sizeof (*argv))))
					err = 1;
				else
				{
					memcpy (argv[argc], lpCmdLine, i * sizeof (*argv));
					argv[argc++][i] = '\0';
				}

				if (lpCmdLine[i] == '\0')
					lpCmdLine += i;
				else
					lpCmdLine += i + 1;
			}
		}
	}

	while (argc)
		free (argv[--argc]);

	if (argv)
		free (argv);

	return err;
}
#endif
