#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AliasAvailableResponse.h"

#include "AliasAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAliasAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="AliasAvailableResponse To JSON String")
	static FString AliasAvailableResponseToJsonString(const UAliasAvailableResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make AliasAvailableResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAliasAvailableResponse* Make(FString Alias, bool bAvailable, FBeamCid Cid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break AliasAvailableResponse", meta=(NativeBreakFunc))
	static void Break(const UAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FBeamCid& Cid);
};