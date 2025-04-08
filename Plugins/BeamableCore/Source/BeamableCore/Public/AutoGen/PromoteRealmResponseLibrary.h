#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"

#include "PromoteRealmResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteRealmResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="PromoteRealmResponse To JSON String")
	static FString PromoteRealmResponseToJsonString(const UPromoteRealmResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make PromoteRealmResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPromoteRealmResponse* Make(FBeamPid SourcePid, TArray<UPromotionScope*> Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break PromoteRealmResponse", meta=(NativeBreakFunc))
	static void Break(const UPromoteRealmResponse* Serializable, FBeamPid& SourcePid, TArray<UPromotionScope*>& Scopes);
};