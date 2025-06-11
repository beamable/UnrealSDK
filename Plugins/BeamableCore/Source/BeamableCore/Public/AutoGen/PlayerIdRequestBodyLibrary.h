#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerIdRequestBody.h"

#include "PlayerIdRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerIdRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="PlayerIdRequestBody To JSON String")
	static FString PlayerIdRequestBodyToJsonString(const UPlayerIdRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PlayerIdRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPlayerIdRequestBody* Make(FBeamGamerTag PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break PlayerIdRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPlayerIdRequestBody* Serializable, FBeamGamerTag& PlayerId);
};