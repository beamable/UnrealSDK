#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicAliasAvailableResponse.h"

#include "RealmsBasicAliasAvailableResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicAliasAvailableResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicAliasAvailableResponse To JSON String")
	static FString RealmsBasicAliasAvailableResponseToJsonString(const URealmsBasicAliasAvailableResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicAliasAvailableResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicAliasAvailableResponse* Make(FString Alias, bool bAvailable, FBeamCid Cid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicAliasAvailableResponse", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FBeamCid& Cid);
};