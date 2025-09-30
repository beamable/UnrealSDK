#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmResponse.h"

#include "RealmsBasicPromoteRealmResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicPromoteRealmResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicPromoteRealmResponse To JSON String")
	static FString RealmsBasicPromoteRealmResponseToJsonString(const URealmsBasicPromoteRealmResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicPromoteRealmResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicPromoteRealmResponse* Make(FBeamPid SourcePid, TArray<UPromotionScope*> Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicPromoteRealmResponse", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicPromoteRealmResponse* Serializable, FBeamPid& SourcePid, TArray<UPromotionScope*>& Scopes);
};