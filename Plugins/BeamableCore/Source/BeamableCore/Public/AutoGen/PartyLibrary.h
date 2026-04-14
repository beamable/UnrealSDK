#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "PartyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPartyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="Party To JSON String")
	static FString PartyToJsonString(const UParty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make Party", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Restriction, Leader, MaxSize, Created, Members, PendingInvites, MembersTags, Outer", NativeMakeFunc))
	static UParty* Make(FOptionalString Id, FOptionalString Restriction, FOptionalBeamGamerTag Leader, FOptionalInt32 MaxSize, FOptionalDateTime Created, FOptionalArrayOfBeamGamerTag Members, FOptionalArrayOfString PendingInvites, FOptionalMapOfTagList MembersTags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break Party", meta=(NativeBreakFunc))
	static void Break(const UParty* Serializable, FOptionalString& Id, FOptionalString& Restriction, FOptionalBeamGamerTag& Leader, FOptionalInt32& MaxSize, FOptionalDateTime& Created, FOptionalArrayOfBeamGamerTag& Members, FOptionalArrayOfString& PendingInvites, FOptionalMapOfTagList& MembersTags);
};