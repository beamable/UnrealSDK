#pragma once

#include "Subsystems/CLI/BeamCliCommand.h"
#include "Serialization/BeamJsonUtils.h"

#include "BeamCliProjectNewStorageCommand.generated.h"



/**
 Description:
  Create and add a new Microstorage

Usage:
  Beamable.Tools project new storage <name> [options]

Arguments:
  <name>  Name of the new project

Options:
  --sln <sln>                              Relative path to the .sln file to use for the new project. If the .sln file does not exist, it will be created. When no option is configured, if this command is executing inside a .beamable folder, then the first .sln found in .beamable/.. will be used. If no .sln is found, the .sln path will be <name>.sln. If no .beamable folder exists, then the <project>/<project>.sln will be used [default: BeamableUnreal.sln]
  --service-directory <service-directory>  Relative path to directory where project should be created. Defaults to "SOLUTION_DIR/services"
  --link-to <link-to>                      The name of the project to link this storage to
  --dryrun                                 Should any networking happen?
  --cid <cid>                              Cid to use; will default to whatever is in the file system
  --pid <pid>                              Pid to use; will default to whatever is in the file system
  -q, --quiet                              When true, skip input waiting and use defaults [default: False]
  --host <host>                            The host endpoint for beamable
  --access-token <access-token>            The access token to use for the requests
  --refresh-token <refresh-token>          Refresh token to use for the requests
  --log, --logs <log>                      Extra logs gets printed out
  --no-redirect                            If there is a local dotnet tool installation (with a ./config/dotnet-tools.json file) for the beam tool, then any global invocation of the beam tool will automatically redirect and call the local version. However, there will be a performance penalty due to the extra process invocation. This option flag will cause an error to occur instead of automatically redirecting the execution to a new process invocation.
  --unmask-logs                            By default, logs will automatically mask tokens. However, when this option is enabled, tokens will be visible in their full text. This is a security risk.
  --no-log-file                            By default, logs are automatically written to a temp file so that they can be used in an error case. However, when this option is enabled, logs are not written. Also, if the BEAM_CLI_NO_FILE_LOG environment variable is set, no log file will be written.  [default: False]
  --docker-cli-path <docker-cli-path>      a custom location for docker. By default, the CLI will attempt to resolve docker through its usual install locations. You can also use the BEAM_DOCKER_EXE environment variable to specify. 
                                           Currently, a docker path has been automatically identified. [default: docker]
  --dir <dir>                              Directory to use for configuration
  --raw                                    Output raw JSON to standard out. This happens by default when the command is being piped
  --pretty                                 Output syntax highlighted box text. This happens by default when the command is not piped
  --dotnet-path <dotnet-path>              a custom location for dotnet [default: dotnet]
  -?, -h, --help                           Show help and usage information




 */
UCLASS()
class UBeamCliProjectNewStorageCommand : public UBeamCliCommand
{
	GENERATED_BODY()

public:
		

	TFunction<void (const int& ResCode, const FBeamOperationHandle& Op)> OnCompleted;
	virtual void HandleStreamReceived(FBeamOperationHandle Op, FString ReceivedStreamType, int64 Timestamp, TSharedRef<FJsonObject> DataJson, bool isServer) override;
	virtual void HandleStreamCompleted(FBeamOperationHandle Op, int ResultCode, bool isServer) override;
	virtual FString GetCommand() override;
};
