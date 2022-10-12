
#pragma once

#include "CoreMinimal.h"
#include "RoomInfo.h"

#include "RoomInfoLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URoomInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RoomInfo To JSON String")
	static FString RoomInfoToJsonString(const URoomInfo* Serializable, const bool Pretty);		
};