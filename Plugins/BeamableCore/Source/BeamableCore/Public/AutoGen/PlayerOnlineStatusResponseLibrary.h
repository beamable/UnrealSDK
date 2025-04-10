#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PlayerOnlineStatusResponse.h"

#include "PlayerOnlineStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerOnlineStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="PlayerOnlineStatusResponse To JSON String")
	static FString PlayerOnlineStatusResponseToJsonString(const UPlayerOnlineStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make PlayerOnlineStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPlayerOnlineStatusResponse* Make(bool bOnline, int64 PlayerId, int64 LastSeen, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break PlayerOnlineStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UPlayerOnlineStatusResponse* Serializable, bool& bOnline, int64& PlayerId, int64& LastSeen);
};