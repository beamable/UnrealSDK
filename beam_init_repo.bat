
REM Copy the Sandbox plugin over to the plugin folder. 
REM This is a local-only plugin that you can do whatever you want in.
REM It is not committed to the repo and it is the default plugin configured to load 
REM (this means the repo won't work unless you run this script exactly once first).
set SANDBOX_PROJ_NAME=BEAMPROJ_Sandbox
set PLUGIN_SANDBOX_PATH="%cd%\Plugins\%SANDBOX_PROJ_NAME%"
set TEMPLATE_SANDBOX_PATH="%cd%\Templates\Plugins\%SANDBOX_PROJ_NAME%"

mkdir %PLUGIN_SANDBOX_PATH%
xcopy /E %TEMPLATE_SANDBOX_PATH% %PLUGIN_SANDBOX_PATH%


REM ### Copy the BuildConfiguration.xml into the saved directory so that we correctly generate intellisense data with rider
set BUILD_CONFIG_PATH="%cd%\Saved\UnrealBuildTool"
set TEMPLATE_BUILD_CONFIG_PATH="%cd%\Templates\Saved\UnrealBuildTool"

xcopy /E %TEMPLATE_BUILD_CONFIG_PATH% %BUILD_CONFIG_PATH%