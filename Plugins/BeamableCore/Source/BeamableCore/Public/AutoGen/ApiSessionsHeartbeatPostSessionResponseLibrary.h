#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsHeartbeatPostSessionResponse.h"

#include "ApiSessionsHeartbeatPostSessionResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiSessionsHeartbeatPostSessionResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="ApiSessionsHeartbeatPostSessionResponse To JSON String")
	static FString ApiSessionsHeartbeatPostSessionResponseToJsonString(const UApiSessionsHeartbeatPostSessionResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make ApiSessionsHeartbeatPostSessionResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiSessionsHeartbeatPostSessionResponse* Make(UObject* Outer);

	
};