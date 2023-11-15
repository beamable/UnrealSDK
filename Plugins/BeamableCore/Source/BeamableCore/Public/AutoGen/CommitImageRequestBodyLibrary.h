#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CommitImageRequestBody.h"

#include "CommitImageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCommitImageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CommitImageRequestBody To JSON String")
	static FString CommitImageRequestBodyToJsonString(const UCommitImageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CommitImageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCommitImageRequestBody* Make(UBeamoBasicReference* Service, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CommitImageRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCommitImageRequestBody* Serializable, UBeamoBasicReference*& Service);
};