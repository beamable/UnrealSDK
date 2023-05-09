#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetAdminsResponse.h"

#include "GetAdminsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetAdminsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetAdminsResponse To JSON String")
	static FString GetAdminsResponseToJsonString(const UGetAdminsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetAdminsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetAdminsResponse* Make(TArray<UAccountPortalView*> Accounts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetAdminsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetAdminsResponse* Serializable, TArray<UAccountPortalView*>& Accounts);
};