REM chemin relatif au dossier contenant glslc.exe
set GLSLC_PATH=%~dp0..\..\..\..\libs\VulkanSDK\1.3.290.0\Bin\

%GLSLC_PATH%glslc.exe Shaders\simple_shader.vert -o Shaders\simple_shader.vert.spv
%GLSLC_PATH%glslc.exe Shaders\simple_shader.frag -o Shaders\simple_shader.frag.spv
pause