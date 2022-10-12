
#pragma once

#include "CoreMinimal.h"
#include "ObjectMetadataResponse.h"

#include "ObjectMetadataResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMetadataResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ObjectMetadataResponse To JSON String")
	static FString ObjectMetadataResponseToJsonString(const UObjectMetadataResponse* Serializable, const bool Pretty);		
};