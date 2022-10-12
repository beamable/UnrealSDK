
#pragma once

#include "CoreMinimal.h"
#include "CreateRoomResponse.h"

#include "CreateRoomResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCreateRoomResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CreateRoomResponse To JSON String")
	static FString CreateRoomResponseToJsonString(const UCreateRoomResponse* Serializable, const bool Pretty);		
};