
#pragma once

#include "CoreMinimal.h"
#include "PlayerListingView.h"

#include "PlayerListingViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerListingViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerListingView To JSON String")
	static FString PlayerListingViewToJsonString(const UPlayerListingView* Serializable, const bool Pretty);		
};