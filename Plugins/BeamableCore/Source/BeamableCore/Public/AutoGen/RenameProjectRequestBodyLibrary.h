#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RenameProjectRequestBody.h"

#include "RenameProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URenameProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RenameProjectRequestBody To JSON String")
	static FString RenameProjectRequestBodyToJsonString(const URenameProjectRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RenameProjectRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URenameProjectRequestBody* Make(FBeamPid ProjectId, FString NewName, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RenameProjectRequestBody", meta=(NativeBreakFunc))
	static void Break(const URenameProjectRequestBody* Serializable, FBeamPid& ProjectId, FString& NewName);
};