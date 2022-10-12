
#pragma once

#include "CoreMinimal.h"
#include "ArchiveProjectRequestBody.h"

#include "ArchiveProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UArchiveProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ArchiveProjectRequestBody To JSON String")
	static FString ArchiveProjectRequestBodyToJsonString(const UArchiveProjectRequestBody* Serializable, const bool Pretty);		
};