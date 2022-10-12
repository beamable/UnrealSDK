
#pragma once

#include "CoreMinimal.h"
#include "GroupMetaData.h"

#include "GroupMetaDataLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGroupMetaDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GroupMetaData To JSON String")
	static FString GroupMetaDataToJsonString(const UGroupMetaData* Serializable, const bool Pretty);		
};