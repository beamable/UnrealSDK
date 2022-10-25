
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/RoomInfo.h"

#include "RoomInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URoomInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RoomInfo To JSON String")
	static FString RoomInfoToJsonString(const URoomInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RoomInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Players, Outer", NativeMakeFunc))
	static URoomInfo* Make(bool bKeepSubscribed, FString Id, FString Name, FOptionalArrayOfInt64 Players, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RoomInfo", meta=(NativeBreakFunc))
	static void Break(const URoomInfo* Serializable, bool& bKeepSubscribed, FString& Id, FString& Name, FOptionalArrayOfInt64& Players);
};