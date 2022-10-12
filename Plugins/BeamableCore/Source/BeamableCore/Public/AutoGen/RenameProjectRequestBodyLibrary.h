
#pragma once

#include "CoreMinimal.h"
#include "RenameProjectRequestBody.h"

#include "RenameProjectRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URenameProjectRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RenameProjectRequestBody To JSON String")
	static FString RenameProjectRequestBodyToJsonString(const URenameProjectRequestBody* Serializable, const bool Pretty);		
};