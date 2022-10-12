
#pragma once

#include "CoreMinimal.h"
#include "MetadataPair.h"

#include "MetadataPairLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UMetadataPairLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize MetadataPair To JSON String")
	static FString MetadataPairToJsonString(const UMetadataPair* Serializable, const bool Pretty);		
};