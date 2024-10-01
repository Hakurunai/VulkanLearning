REM chemin relatif au dossier contenant glslc.exe
set GLSLC_PATH=%~dp0..\..\..\libs\VulkanSDK\1.3.290.0\Bin\

%GLSLC_PATH%glslc.exe simple_shader.vert -o simple_shader.vert.spv
%GLSLC_PATH%glslc.exe simple_shader.frag -o simple_shader.frag.spv
REM pause