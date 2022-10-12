
#pragma once

#include "CoreMinimal.h"
#include "PlayerStoreView.h"

#include "PlayerStoreViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPlayerStoreViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PlayerStoreView To JSON String")
	static FString PlayerStoreViewToJsonString(const UPlayerStoreView* Serializable, const bool Pretty);		
};