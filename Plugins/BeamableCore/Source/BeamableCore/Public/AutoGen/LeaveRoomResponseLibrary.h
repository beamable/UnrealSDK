
#pragma once

#include "CoreMinimal.h"
#include "LeaveRoomResponse.h"

#include "LeaveRoomResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaveRoomResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaveRoomResponse To JSON String")
	static FString LeaveRoomResponseToJsonString(const ULeaveRoomResponse* Serializable, const bool Pretty);		
};