
#pragma once

#include "CoreMinimal.h"
#include "AccountPlayerView.h"

#include "AccountPlayerViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UAccountPlayerViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize AccountPlayerView To JSON String")
	static FString AccountPlayerViewToJsonString(const UAccountPlayerView* Serializable, const bool Pretty);		
};