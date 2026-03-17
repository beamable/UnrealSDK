#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsPostSessionResponse.h"

#include "ApiSessionsPostSessionResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiSessionsPostSessionResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="ApiSessionsPostSessionResponse To JSON String")
	static FString ApiSessionsPostSessionResponseToJsonString(const UApiSessionsPostSessionResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make ApiSessionsPostSessionResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiSessionsPostSessionResponse* Make(UObject* Outer);

	
};