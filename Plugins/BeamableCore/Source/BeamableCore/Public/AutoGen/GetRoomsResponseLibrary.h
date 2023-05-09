#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetRoomsResponse.h"

#include "GetRoomsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetRoomsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetRoomsResponse To JSON String")
	static FString GetRoomsResponseToJsonString(const UGetRoomsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetRoomsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetRoomsResponse* Make(TArray<URoomInfo*> Rooms, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetRoomsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetRoomsResponse* Serializable, TArray<URoomInfo*>& Rooms);
};