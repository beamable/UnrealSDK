
#pragma once

#include "CoreMinimal.h"
#include "CreateRoomRequestBody.h"

#include "CreateRoomRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreateRoomRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreateRoomRequestBody To JSON String")
	static FString CreateRoomRequestBodyToJsonString(const UCreateRoomRequestBody* Serializable, const bool Pretty);		
};