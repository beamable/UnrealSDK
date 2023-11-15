#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StartSessionResponse.h"

#include "StartSessionResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStartSessionResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StartSessionResponse To JSON String")
	static FString StartSessionResponseToJsonString(const UStartSessionResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StartSessionResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Gamer, Outer", NativeMakeFunc))
	static UStartSessionResponse* Make(FString Result, FOptionalGamerTag Gamer, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StartSessionResponse", meta=(NativeBreakFunc))
	static void Break(const UStartSessionResponse* Serializable, FString& Result, FOptionalGamerTag& Gamer);
};