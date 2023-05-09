#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateRoomResponse.h"

#include "CreateRoomResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateRoomResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateRoomResponse To JSON String")
	static FString CreateRoomResponseToJsonString(const UCreateRoomResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateRoomResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCreateRoomResponse* Make(URoomInfo* Room, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateRoomResponse", meta=(NativeBreakFunc))
	static void Break(const UCreateRoomResponse* Serializable, URoomInfo*& Room);
};