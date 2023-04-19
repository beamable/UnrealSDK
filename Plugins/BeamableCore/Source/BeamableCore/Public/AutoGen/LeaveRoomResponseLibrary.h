
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LeaveRoomResponse.h"

#include "LeaveRoomResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULeaveRoomResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LeaveRoomResponse To JSON String")
	static FString LeaveRoomResponseToJsonString(const ULeaveRoomResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LeaveRoomResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULeaveRoomResponse* Make(FString Removed, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LeaveRoomResponse", meta=(NativeBreakFunc))
	static void Break(const ULeaveRoomResponse* Serializable, FString& Removed);
};