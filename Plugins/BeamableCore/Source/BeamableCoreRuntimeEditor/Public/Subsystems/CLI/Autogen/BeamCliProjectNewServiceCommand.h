#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectNewServiceCommand.generated.h"



/**
 Description:
  Create a new microservice project

Usage:
  Beamable.Tools project new service <name> [options]

Arguments:
  <name>  Name of the new project

Options:
  --sln <sln>                              Relative path to the .sln file to use for the new project. If the .sln file does not exist, it will be created. When no option is configured, if this command is executing inside a .beamable folder, then the first .sln found in .beamable/.. will be used. If no .sln is found, the .sln path will be <name>.sln. If no .beamable folder exists, then the <project>/<project>.sln will be used [default: BeamableUnreal.sln]
  --service-directory <service-directory>  Relative path to directory where project should be created. Defaults to "SOLUTION_DIR/services"
  --version <version>                      Specifies version of Beamable project dependencies. Defaults to the current version of the CLI [default: 0.0.123]
  --generate-common                        If passed, will create a common library for this project
  --beamable-dev                           INTERNAL This enables a sane workflow for beamable developers to be happy and productive [default: False]
  --dryrun                                 Should any networking happen?
  --cid <cid>                              Cid to use; will default to whatever is in the file system
  --pid <pid>                              Pid to use; will default to whatever is in the file system
  -q, --quiet                              When true, skip input waiting and use defaults [default: False]
  --host <host>                            The host endpoint for beamable
  --refresh-token <refresh-token>          Refresh token to use for the requests
  --log, --logs <log>                      Extra logs gets printed out
  --dir <dir>                              Directory to use for configuration
  --raw                                    Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                 Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>              a custom location for dotnet
  -?, -h, --help                           Show help and usage information




 */
UCLASS()
class UBeamCliProjectNewServiceCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
