
#pragma once

#include "CoreMinimal.h"
#include "LeaveRoomRequestBody.h"

#include "LeaveRoomRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API ULeaveRoomRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize LeaveRoomRequestBody To JSON String")
	static FString LeaveRoomRequestBodyToJsonString(const ULeaveRoomRequestBody* Serializable, const bool Pretty);		
};