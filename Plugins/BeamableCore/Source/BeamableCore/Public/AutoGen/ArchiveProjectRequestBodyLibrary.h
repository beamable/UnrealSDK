#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ArchiveProjectRequestBody.h"

#include "ArchiveProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UArchiveProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ArchiveProjectRequestBody To JSON String")
	static FString ArchiveProjectRequestBodyToJsonString(const UArchiveProjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ArchiveProjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UArchiveProjectRequestBody* Make(FBeamPid Pid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ArchiveProjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const UArchiveProjectRequestBody* Serializable, FBeamPid& Pid);
};