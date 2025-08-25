#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsProcessMatchResultResponse.h"

#include "BeamballMsProcessMatchResultResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsProcessMatchResultResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="BeamballMsProcessMatchResultResponse To JSON String")
	static FString BeamballMsProcessMatchResultResponseToJsonString(const UBeamballMsProcessMatchResultResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsProcessMatchResultResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamballMsProcessMatchResultResponse* Make(TMap<FString, FString> Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break BeamballMsProcessMatchResultResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamballMsProcessMatchResultResponse* Serializable, TMap<FString, FString>& Value);
};