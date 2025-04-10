#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetGroupStatusResponse.h"

#include "GetGroupStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetGroupStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Json", DisplayName="GetGroupStatusResponse To JSON String")
	static FString GetGroupStatusResponseToJsonString(const UGetGroupStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetGroupStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetGroupStatusResponse* Make(TArray<UGroupStatus*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Break GetGroupStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UGetGroupStatusResponse* Serializable, TArray<UGroupStatus*>& Statuses);
};