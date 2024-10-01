REM chemin relatif au dossier contenant glslc.exe
set GLSLC_PATH=%~dp0..\..\..\libs\VulkanSDK\1.3.290.0\Bin\

REM path to the ressources folder used by our program
set OUTPUT_DIR=%~dp0..\..\..\Ressources\Shaders\
if not exist "%OUTPUT_DIR%" ( mkdir "%OUTPUT_DIR%" )

%GLSLC_PATH%glslc.exe simple_shader.vert -o %OUTPUT_DIR%simple_shader.vert.spv
%GLSLC_PATH%glslc.exe simple_shader.frag -o %OUTPUT_DIR%simple_shader.frag.spv
REM pause