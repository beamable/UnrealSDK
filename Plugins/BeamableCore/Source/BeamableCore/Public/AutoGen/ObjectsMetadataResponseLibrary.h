
#pragma once

#include "CoreMinimal.h"
#include "ObjectsMetadataResponse.h"

#include "ObjectsMetadataResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectsMetadataResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ObjectsMetadataResponse To JSON String")
	static FString ObjectsMetadataResponseToJsonString(const UObjectsMetadataResponse* Serializable, const bool Pretty);		
};