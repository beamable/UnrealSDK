#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"

#include "GetStatusForGroupsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStatusForGroupsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetStatusForGroupsResponse To JSON String")
	static FString GetStatusForGroupsResponseToJsonString(const UGetStatusForGroupsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetStatusForGroupsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetStatusForGroupsResponse* Make(FString ContentId, TArray<UGroupStatus*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetStatusForGroupsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetStatusForGroupsResponse* Serializable, FString& ContentId, TArray<UGroupStatus*>& Statuses);
};