# use the dotnet sdk as a build stage
FROM mcr.microsoft.com/dotnet/sdk:8.0-alpine as build-env
WORKDIR /BeamableSource
COPY ./BeamableSource/*.nupkg ./
WORKDIR /subsrc/
RUN dotnet nuget add source /BeamableSource -n BeamableSource
RUN dotnet nuget update source BeamableSource

# <BEAM-CLI-COPY-ENV> this line signals the start of environment variables copies into the built container. Do not remove it. This will be overwritten every time a variable changes in the execution of the CLI.
ENV BEAM_CSPROJ_PATH="/subsrc/Microservices/services/DiscordSampleMs/DiscordSampleMs.csproj"
ENV BEAM_VERSION="0.0.123"
# </BEAM-CLI-COPY-ENV> this line signals the end of environment variables copies into the built container. Do not remove it.

# <BEAM-CLI-COPY-SRC> this line signals the start of Beamable Project Src copies into the built container. Do not remove it. The content between here and the closing tag will change anytime the Beam CLI modifies dependencies.
RUN mkdir -p /subsrc/Microservices/services/DiscordSampleMs
COPY Microservices/services/DiscordSampleMs /subsrc/Microservices/services/DiscordSampleMs
# </BEAM-CLI-COPY-SRC> this line signals the end of Beamable Project Src copies. Do not remove it.

# build the dotnet program
WORKDIR /

RUN dotnet publish ${BEAM_CSPROJ_PATH} -p:BeamableVersion=${BEAM_VERSION} -c release -o /beamApp

# use the dotnet runtime as the final stage
FROM mcr.microsoft.com/dotnet/runtime:8.0-alpine
WORKDIR /beamApp

RUN apk add --no-cache icu-libs

# expose the health port
EXPOSE 6565 

# copy the built program
COPY --from=build-env /beamApp .

# when starting the container, run dotnet with the built dll
ENTRYPOINT ["dotnet", "/beamApp/DiscordSampleMs.dll"]

# Swap entrypoints if the container is exploding and you want to keep it alive indefinitely so you can go look into it.
#ENTRYPOINT ["tail", "-f", "/dev/null"]

