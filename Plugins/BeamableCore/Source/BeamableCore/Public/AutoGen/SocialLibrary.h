
#pragma once

#include "CoreMinimal.h"
#include "Social.h"

#include "SocialLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USocialLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize Social To JSON String")
	static FString SocialToJsonString(const USocial* Serializable, const bool Pretty);		
};