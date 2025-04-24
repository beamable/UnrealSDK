#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "EmptyResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEmptyResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="EmptyResponse To JSON String")
	static FString EmptyResponseToJsonString(const UEmptyResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make EmptyResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEmptyResponse* Make(FString Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break EmptyResponse", meta=(NativeBreakFunc))
	static void Break(const UEmptyResponse* Serializable, FString& Result);
};