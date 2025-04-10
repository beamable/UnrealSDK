#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponse.h"

#include "GetStatusForGroupsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStatusForGroupsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetStatusForGroupsResponse To JSON String")
	static FString GetStatusForGroupsResponseToJsonString(const UGetStatusForGroupsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetStatusForGroupsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetStatusForGroupsResponse* Make(FString ContentId, TArray<UGroupStatus*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetStatusForGroupsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetStatusForGroupsResponse* Serializable, FString& ContentId, TArray<UGroupStatus*>& Statuses);
};