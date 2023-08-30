#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateParty.h"

#include "CreatePartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreatePartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CreateParty To JSON String")
	static FString CreatePartyToJsonString(const UCreateParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CreateParty", meta=(DefaultToSelf="Outer", AdvancedDisplay="Restriction, Leader, MaxSize, Outer", NativeMakeFunc))
	static UCreateParty* Make(FOptionalString Restriction, FOptionalString Leader, FOptionalInt32 MaxSize, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CreateParty", meta=(NativeBreakFunc))
	static void Break(const UCreateParty* Serializable, FOptionalString& Restriction, FOptionalString& Leader, FOptionalInt32& MaxSize);
};