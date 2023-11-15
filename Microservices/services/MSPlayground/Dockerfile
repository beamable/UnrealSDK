# use the dotnet SDK as a build stage
FROM mcr.microsoft.com/dotnet/sdk:6.0-alpine AS build-env

# Since generating the common library is optional, the CLI will replace the insert flag below to copy it correctly 
# At the moment, it'll only do so, if the common library project was created at the time of setting up the solution.
# If not, this line will remain so that we can make a command that adds only the common library to your C#MS solution.
# <BEAM-CLI-INSERT-FLAG:COPY_COMMON> do not delete this line. It is used by the beam CLI to insert custom actions

# <BEAM-CLI-INSERT-FLAG:COPY> do not delete this line. It is used by the beam CLI to insert custom actions

# copy in required files
WORKDIR /subsrc/MSPlayground
COPY MSPlayground/MSPlayground.csproj .
COPY MSPlayground/. .

# build the dotnet program
RUN dotnet publish -c release -o /subapp

# use the dotnet runtime as the final stage
FROM mcr.microsoft.com/dotnet/runtime:6.0-alpine
WORKDIR /subapp

# expose the health port
EXPOSE 6565 

# copy the built program
COPY --from=build-env /subapp .

# when starting the container, run dotnet with the built dll
ENTRYPOINT ["dotnet", "/subapp/MSPlayground.dll"]
