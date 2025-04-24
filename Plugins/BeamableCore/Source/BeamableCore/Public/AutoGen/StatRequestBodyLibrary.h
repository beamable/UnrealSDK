#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatRequestBody.h"

#include "StatRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="StatRequestBody To JSON String")
	static FString StatRequestBodyToJsonString(const UStatRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make StatRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Stats, Outer", NativeMakeFunc))
	static UStatRequestBody* Make(FOptionalString Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break StatRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStatRequestBody* Serializable, FOptionalString& Stats);
};