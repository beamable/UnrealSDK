
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaveRoomRequestBody.h"

#include "LeaveRoomRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaveRoomRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaveRoomRequestBody To JSON String")
	static FString LeaveRoomRequestBodyToJsonString(const ULeaveRoomRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaveRoomRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaveRoomRequestBody* Make(FString RoomId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaveRoomRequestBody", meta=(NativeBreakFunc))
	static void Break(const ULeaveRoomRequestBody* Serializable, FString& RoomId);
};