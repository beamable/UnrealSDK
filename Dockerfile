FROM ghcr.io/epicgames/unreal-engine:dev-5.3.2 as builder

USER ue4
# Copy your Unreal project files into the Docker image
COPY --chown=ue4 . /home/ue4/project
RUN echo $(ls -la /home/ue4/UnrealEngine/Engine/Build/BatchFiles/Linux)
RUN echo $(ls -la /home/ue4/project)

RUN /home/ue4/UnrealEngine/Engine/Build/BatchFiles/Linux/GenerateProjectFiles.sh -projectfiles -project=/home/ue4/project/BeamableUnreal.uproject -game -rocket -progress  
RUN /home/ue4/UnrealEngine/Engine/Build/BatchFiles/RunUAT.sh BuildCookRun -project=/home/ue4/project/BeamableUnreal.uproject \
-utf8output \
-platform=Linux \
-clientconfig=Shipping \
-serverconfig=Shipping \
-noP4 -nodebuginfo -allmaps \
-cook -build -stage -prereqs -pak -archive \
-archivedirectory=/home/ue4/PackagedProject
