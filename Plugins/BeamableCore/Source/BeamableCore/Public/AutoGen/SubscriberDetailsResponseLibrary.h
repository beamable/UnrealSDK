
#pragma once

#include "CoreMinimal.h"
#include "SubscriberDetailsResponse.h"

#include "SubscriberDetailsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API USubscriberDetailsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize SubscriberDetailsResponse To JSON String")
	static FString SubscriberDetailsResponseToJsonString(const USubscriberDetailsResponse* Serializable, const bool Pretty);		
};