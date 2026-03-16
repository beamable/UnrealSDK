#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsStatusGetSessionResponse.h"

#include "ApiSessionsStatusGetSessionResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiSessionsStatusGetSessionResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="ApiSessionsStatusGetSessionResponse To JSON String")
	static FString ApiSessionsStatusGetSessionResponseToJsonString(const UApiSessionsStatusGetSessionResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make ApiSessionsStatusGetSessionResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiSessionsStatusGetSessionResponse* Make(UObject* Outer);

	
};