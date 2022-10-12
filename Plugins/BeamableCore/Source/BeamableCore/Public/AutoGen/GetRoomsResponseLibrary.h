
#pragma once

#include "CoreMinimal.h"
#include "GetRoomsResponse.h"

#include "GetRoomsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRoomsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize GetRoomsResponse To JSON String")
	static FString GetRoomsResponseToJsonString(const UGetRoomsResponse* Serializable, const bool Pretty);		
};