# TheScholar
 An offline Book and article database for users to join and access.
 
## Created By:
Nikesh D.C    (PUL075BCT052)
Ravi Pandey   (PUL075BCT065)
Rohan Chhetry (PUL075BCT066)
 
## SETTING UP THE LIBRARY
Freeglut library folder is included inside the Library folder.

The "freeglut.dll" binary file should be placed in the Windows Folder present in the drive in which the O.S is installed.

The "lib" and "include" folders of the freeglut library should be merged with the "lib" and "include" folder of the MinGW compiler.

To use this library in CodeBlocks IDE the "wizard.script" file presnt in "...CodeBlocks\share\CodeBlocks\templates\wizard\glut" must be replaced 
with the "wizard.script" file supplied in the freeglut folder. 

In order to compiler our "main.cpp" we recommend adding the following link libraries in the linker settings of CodeBlocks:-
-freeglut
-opengl32
-glu32
-winmm
-gdi32

##### For this specific project, we recommend C++17.
In case of error during building, we have included additional informations in the "Additional Information" Sub-Folder of Library Folder.

