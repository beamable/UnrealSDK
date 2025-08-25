#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/ProcessMatchResultRequestArgs.h"

#include "ProcessMatchResultRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UProcessMatchResultRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="ProcessMatchResultRequestArgs To JSON String")
	static FString ProcessMatchResultRequestArgsToJsonString(const UProcessMatchResultRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make ProcessMatchResultRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UProcessMatchResultRequestArgs* Make(FString WinnerId, FString LobbyId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break ProcessMatchResultRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UProcessMatchResultRequestArgs* Serializable, FString& WinnerId, FString& LobbyId);
};