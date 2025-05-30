#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Group.h"

#include "GroupLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="Group To JSON String")
	static FString GroupToJsonString(const UGroup* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make Group", meta=(DefaultToSelf="Outer", AdvancedDisplay="bCanDisband, bCanUpdateEnrollment, bCanUpdateMOTD, bCanUpdateSlogan, Shard, ClientData, Version, Tag, Donations, Roles, InFlight, MaybeDonations, Outer", NativeMakeFunc))
	static UGroup* Make(int64 Requirement, int32 MaxSize, EBeamGroupType Type, int64 Id, FString Motd, FString Slogan, int64 Leader, int64 Created, FString Name, FString EnrollmentType, int32 FreeSlots, TArray<UGroup*> SubGroups, TArray<UMember*> Members, TMap<FString, FString> Scores, FOptionalBool bCanDisband, FOptionalBool bCanUpdateEnrollment, FOptionalBool bCanUpdateMOTD, FOptionalBool bCanUpdateSlogan, FOptionalString Shard, FOptionalString ClientData, FOptionalInt32 Version, FOptionalString Tag, FOptionalArrayOfDonationRequestBody Donations, FOptionalArrayOfGroupRole Roles, FOptionalArrayOfInFlightMessage InFlight, FOptionalMapOfDonationRequestBody MaybeDonations, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break Group", meta=(NativeBreakFunc))
	static void Break(const UGroup* Serializable, int64& Requirement, int32& MaxSize, EBeamGroupType& Type, int64& Id, FString& Motd, FString& Slogan, int64& Leader, int64& Created, FString& Name, FString& EnrollmentType, int32& FreeSlots, TArray<UGroup*>& SubGroups, TArray<UMember*>& Members, TMap<FString, FString>& Scores, FOptionalBool& bCanDisband, FOptionalBool& bCanUpdateEnrollment, FOptionalBool& bCanUpdateMOTD, FOptionalBool& bCanUpdateSlogan, FOptionalString& Shard, FOptionalString& ClientData, FOptionalInt32& Version, FOptionalString& Tag, FOptionalArrayOfDonationRequestBody& Donations, FOptionalArrayOfGroupRole& Roles, FOptionalArrayOfInFlightMessage& InFlight, FOptionalMapOfDonationRequestBody& MaybeDonations);
};