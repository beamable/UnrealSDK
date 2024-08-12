#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientContentInfoJson.h"

#include "ClientContentInfoJsonLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientContentInfoJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ClientContentInfoJson To JSON String")
	static FString ClientContentInfoJsonToJsonString(const UClientContentInfoJson* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ClientContentInfoJson", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UClientContentInfoJson* Make(FString Uri, FString Version, FBeamContentId ContentId, EContentType Type, TArray<FString> Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ClientContentInfoJson", meta=(NativeBreakFunc))
	static void Break(const UClientContentInfoJson* Serializable, FString& Uri, FString& Version, FBeamContentId& ContentId, EContentType& Type, TArray<FString>& Tags);
};