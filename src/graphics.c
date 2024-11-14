/*C-Ware License

Copyright (c) 2024, Tristan Wellman
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Redistributions of modified source code must append a copyright notice in
   the form of 'Copyright <YEAR> <NAME>' to each modified source file's
   copyright notice, and the standalone license file if one exists.

A "redistribution" can be constituted as any version of the source code
that is intended to comprise some other derivative work of this code. A
fork created for the purpose of contributing to any version of the source
does not constitute a truly "derivative work" and does not require listing.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#include "util.h"
#include "graphics.h"

winData *dataPtr;

void initWindow(winData *data) {
	/*Get things ready for initialization*/
	if(dataPtr==NULL) dataPtr = (winData *)malloc(sizeof(winData));
	dataPtr = data;
	WASSERT(SDL_Init(SDL_INIT_VIDEO)>=0,
			"ERROR:: Failed to initialize SDL!");
	if(dataPtr->title==NULL) dataPtr->title = "title";

	/*Initialization & error checking*/
	SDL_GL_LoadLibrary(NULL);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	dataPtr->window = SDL_CreateWindow(dataPtr->title, 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			dataPtr->width, dataPtr->height, SDL_WINDOW_OPENGL);
	WASSERT(dataPtr->window!=NULL,
			"ERROR:: Failed to initialize SDL window!");

	dataPtr->glContext = SDL_GL_CreateContext(dataPtr->window);
	WASSERT(dataPtr->glContext!=NULL,
			"ERROR:: Failed to initialize OpenGL context!");

	WASSERT(gladLoadGLLoader(SDL_GL_GetProcAddress),
			"ERROR:: Failed to initialize GLAD!");

	SDL_GL_SetSwapInterval(1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	/*setup viewport*/
	int w,h;
	SDL_GetWindowSize(dataPtr->window, &w, &h);
	glViewport(0, 0, w, h);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*Log information*/
	WLOG(INFO_VENDOR, glGetString(GL_VENDOR));
	WLOG(INFO_RENDERER, glGetString(GL_RENDERER));
	WLOG(INFO_GL_VERSION, glGetString(GL_VERSION));


}

void runProgram() {
	int running=1;
	while(running) {
    	while (SDL_PollEvent(&dataPtr->event)) {
      		if (dataPtr->event.type == SDL_QUIT) running=0;
    	}
		/*TODO: rendering*/
	
    	glClear(GL_COLOR_BUFFER_BIT);
    	SDL_GL_SwapWindow(dataPtr->window);
	}
}
