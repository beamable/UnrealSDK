
#pragma once

#include "CoreMinimal.h"
#include "PlayerOfferView.h"

#include "PlayerOfferViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerOfferViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerOfferView To JSON String")
	static FString PlayerOfferViewToJsonString(const UPlayerOfferView* Serializable, const bool Pretty);		
};