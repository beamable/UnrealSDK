 
FROM mcr.microsoft.com/dotnet/sdk:6.0-alpine as build-env
WORKDIR /BeamableSource
COPY ./BeamableSource/*.nupkg ./
WORKDIR /subsrc/
RUN dotnet nuget add source /BeamableSource

# <BEAM-CLI-COPY-SRC> this line signals the start of Beamable Project Src copies into the built container. Do not remove it. The content between here and the closing tag will change anytime the Beam CLI modifies dependencies.
RUN mkdir /subsrc/MSPlayground
COPY Microservices/services/MSPlayground /subsrc/MSPlayground
# </BEAM-CLI-COPY-SRC> this line signals the end of Beamable Project Src copies. Do not remove it.

# build the dotnet program
WORKDIR /
RUN dotnet publish /subsrc/MSPlayground/MSPlayground.csproj -c release -o /subapp


# use the dotnet runtime as the final stage
FROM mcr.microsoft.com/dotnet/runtime:6.0-alpine
WORKDIR /subapp

# expose the health port
EXPOSE 6565 

# copy the built program
COPY --from=build-env /subapp .

# when starting the container, run dotnet with the built dll
#ENTRYPOINT ["tail", "-f", "/dev/null"]
ENTRYPOINT ["dotnet", "/subapp/MSPlayground.dll"]
