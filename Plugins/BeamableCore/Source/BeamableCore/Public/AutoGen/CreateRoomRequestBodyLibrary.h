
#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateRoomRequestBody.h"

#include "CreateRoomRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateRoomRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateRoomRequestBody To JSON String")
	static FString CreateRoomRequestBodyToJsonString(const UCreateRoomRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateRoomRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCreateRoomRequestBody* Make(bool bKeepSubscribed, FString RoomName, TArray<int64> Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateRoomRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateRoomRequestBody* Serializable, bool& bKeepSubscribed, FString& RoomName, TArray<int64>& Players);
};