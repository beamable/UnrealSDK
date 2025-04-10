#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetGameRequestBody.h"

#include "GetGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="GetGameRequestBody To JSON String")
	static FString GetGameRequestBodyToJsonString(const UGetGameRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetGameRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetGameRequestBody* Make(FBeamPid RootPID, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break GetGameRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetGameRequestBody* Serializable, FBeamPid& RootPID);
};