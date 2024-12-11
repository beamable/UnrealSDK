ARG BEAM_DOTNET_VERSION="8.0-alpine"
FROM mcr.microsoft.com/dotnet/runtime:${BEAM_DOTNET_VERSION}

# These args are provided by the Beam CLI

# Declares the relative path from the beamable workspace to the pre-build support binaries for BeamService
#  Normally, this will be /services/BeamService/bin/beamApp/support
ARG BEAM_SUPPORT_SRC_PATH

# Declares the relative path from the beamable workspace to the pre-built binaries for BeamService
#  Normally, this will be /services/BeamService/bin/beamApp/app
ARG BEAM_APP_SRC_PATH

# Declares where the built application will exist inside the Docker image.
#  This value is usually /beamApp/BeamService
ARG BEAM_APP_DEST

# <beamReserved> Beamable may inject custom settings into this Dockerfile. Please do not remove these lines. 
# </beamReserved>

# /beamApp is the directory that will hold the application
WORKDIR /beamApp

# expose the health port
EXPOSE 6565 

# copy general supporting files
COPY $BEAM_SUPPORT_SRC_PATH .

# copy specific application code
COPY $BEAM_APP_SRC_PATH .

# ensure that the application is runnable
RUN chmod +x $BEAM_APP_DEST
ENV BEAM_APP=$BEAM_APP_DEST

# when starting the container, run dotnet with the built dll
ENTRYPOINT "dotnet" $BEAM_APP

# Swap entrypoints if the container is exploding and you want to keep it alive indefinitely so you can go look into it.
#ENTRYPOINT ["tail", "-f", "/dev/null"]
