#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CreateMatchResultRequestArgs.h"

#include "CreateMatchResultRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCreateMatchResultRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Json", DisplayName="CreateMatchResultRequestArgs To JSON String")
	static FString CreateMatchResultRequestArgsToJsonString(const UCreateMatchResultRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make CreateMatchResultRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCreateMatchResultRequestArgs* Make(int64 UserId, FString LobbyId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Break CreateMatchResultRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UCreateMatchResultRequestArgs* Serializable, int64& UserId, FString& LobbyId);
};