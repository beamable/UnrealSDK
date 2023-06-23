#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "PartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Party To JSON String")
	static FString PartyToJsonString(const UParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Party", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Restriction, Leader, MaxSize, Members, PendingInvites, Outer", NativeMakeFunc))
	static UParty* Make(FOptionalString Id, FOptionalString Restriction, FOptionalString Leader, FOptionalInt32 MaxSize, FOptionalArrayOfString Members, FOptionalArrayOfString PendingInvites, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Party", meta=(NativeBreakFunc))
	static void Break(const UParty* Serializable, FOptionalString& Id, FOptionalString& Restriction, FOptionalString& Leader, FOptionalInt32& MaxSize, FOptionalArrayOfString& Members, FOptionalArrayOfString& PendingInvites);
};