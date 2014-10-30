BBGameEnglineTutorial
=====================

c plus plus game engine based on bennybox tutorials

3DGameEngine is the main project. The other two are test projects.
To run this app:
1) Download the .zip file of this project and unzip
2) Open 3DGameEngine with Visual Studio 2012/2013
3) 1.0	Basic Setup
      This project was written and tested with the following configurations:
      •	Operating System: 	Windows 8.1/7
      •	IDE: 			Microsoft Visual Studio 2013
      •	Languages: 		C++, GLSL(OpenGL Shading Language)
      •	API: 			OpenGL
      •	Version Control:	GitHub
      
      1.1 Operating System
      Windows 8.1 and 7 was mainly used in this project but it should be possible to achieve the same results with other operating systems such as OSX or Linux.
      1.2 IDE
      Microsoft Visual Studio 2013 or recent versions are recommended as the development environment to edit, build or run The Engine was originally developed using this IDE. However, other IDEs such as Code::Blocks and IntelliJ IDEA are good alternatives. Eclipse could also be used but is not recommended. Visual Studio 2013 can be obtained for free through a valid DreamSpark account or at the following website: 
      http://www.visualstudio.com/downloads/download-visual-studio-vs
      1.3 Programming Languages, API, and NShader
      C++ was used to write the The Engine’s CPU instructions. GLSL was used to write the shader programs that control the GPU. GLSL formatting is not supported natively by Microsoft Visual Studio 2013. The following plug-in can be installed to provide some useful formatting tools for writing GLSL programs:
      http://www.jostavo.net/NShader.rar
      1.4 Version Control
      GitHub was used for version control during the development of The Engine. Though initially the web and client based GitHub interface was used, eventually version control was accomplished using GitHub plug-in native to Visual Studio 2013. Compared to other GitHub interfaces we found the integration of GitHub in Visual Studio to be the simplest to use and provides a great deal of GitHub functionality through an easy to maneuver GUI.
      1.5 External Libraries
      Other than the standard libraries for C++, some extra external libraries were used in the development of this project. They include:
      •	Simple DirectMedia Layer(SDL) 2.0.3
      •	The OpenGL Extension Wrangler Library(GLEW) 1.10
      •	OpenGL Mathematics(GLM) 0.9.5.3
      
      1.5.1 Installation & Configuration
      Step 1) Download the appropriate libraries.
      •	All of the libraries used in the projection can be found at the following websites:
      o	SDL: https://www.libsdl.org/download-2.0.php
      o	GLEW: http://glew.sourceforge.net/index.html
      o	GLM: http://sourceforge.net/projects/ogl-math/files/
      
      •	When downloading the libraries, make sure to download the binary versions that contain both the .h and .cpp files along with the .lib files and in some cases, the .dll file.
      
      Step 2) Extract the downloaded files to local IDE directories*.
      •	Create folders named ‘SDL,’ ‘glm,’ and ‘GL’ at the following location:**
      o	C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include
      •	Extract the SDL ‘Include’ folder to this path**:
      o	C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\SDL
      •	Extract the GLM ‘glm’ folder to this path**:
      o	C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\GL
      •	Extract the GLEW ‘include’ folder to this path**:
      o	C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\glm
      
      Step 3) Extract .lib files to appropriate directories*.
      •	All .lib files should be extracted to**:
      o	C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib
      •	Files to be extracted to above location (GLM does not require any .lib files):
      o	SDL2.lib
      o	SDL2main.lib
      o	SDL2test.lib
      o	glew32.lib
      o	glew32s.lib
      •	Make sure to copy the 32-bit .lib files and not the 64-bit ones as this project will be a WIN32 project.
      
       
      Step 4) Linking libraries in Visual Studio.
      •	After extracting the library files to the appropriate folders, the libraries need to be linked to the project. The following steps describe how to link files in Visual Studio 2013:
      1.	In the Solution Explorer, right click the project that needs to be linked to the libraries.
      2.	Click ‘Properties’.
      3.	Navigate to Configuration Properties->Linker->Input.
      4.	In ‘Additional Dependencies’, click on the arrow icon on the far right and click ‘Edit’.
      5.	Type in the following libraries:-
      a.	SDL2.lib
      b.	SDL2main.lib
      c.	glew32.lib
      d.	glew32s.lib
      e.	glu32.lib
      f.	opengl32.lib
      •	The project should now be configured and ready for development.
      
      * Because Visual Studio 2013 was used for development of The Engine, the above instructions apply only to extracting files to appropriate Visual Studio 2013 directories.
      ** The path to Visual Studio’s include folder may differ on your machine depending on your installation.
4) Click run
