#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientDataEntry.h"

#include "ClientDataEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientDataEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="ClientDataEntry To JSON String")
	static FString ClientDataEntryToJsonString(const UClientDataEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make ClientDataEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UClientDataEntry* Make(FString Name, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break ClientDataEntry", meta=(NativeBreakFunc))
	static void Break(const UClientDataEntry* Serializable, FString& Name, FString& Value);
};