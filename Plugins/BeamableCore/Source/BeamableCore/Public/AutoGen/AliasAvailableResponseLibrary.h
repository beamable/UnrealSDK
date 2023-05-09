#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AliasAvailableResponse.h"

#include "AliasAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAliasAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AliasAvailableResponse To JSON String")
	static FString AliasAvailableResponseToJsonString(const UAliasAvailableResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AliasAvailableResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAliasAvailableResponse* Make(FString Alias, bool bAvailable, FBeamCid Cid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AliasAvailableResponse", meta=(NativeBreakFunc))
	static void Break(const UAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FBeamCid& Cid);
};