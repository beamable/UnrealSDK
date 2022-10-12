
#pragma once

#include "CoreMinimal.h"
#include "MetadataView.h"

#include "MetadataViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMetadataViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MetadataView To JSON String")
	static FString MetadataViewToJsonString(const UMetadataView* Serializable, const bool Pretty);		
};