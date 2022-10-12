
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "AutoGen/Optionals/OptionalArrayOfDonationRequestBody.h"
#include "AutoGen/Optionals/OptionalMapOfDonationRequestBody.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalArrayOfGroupRole.h"
#include "AutoGen/Member.h"
#include "AutoGen/Enums/GroupType.h"

#include "Group.generated.h"

UCLASS(BlueprintType)
class UGroup : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight")
	FOptionalArrayOfInFlightMessage InFlight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type")
	FString EnrollmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Donations")
	FOptionalArrayOfDonationRequestBody Donations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Free Slots")
	int32 FreeSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Maybe Donations")
	FOptionalMapOfDonationRequestBody MaybeDonations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag")
	FOptionalString Tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update MOTD")
	FOptionalBool bCanUpdateMOTD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard")
	FOptionalString Shard;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update Slogan")
	FOptionalBool bCanUpdateSlogan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leader")
	int64 Leader;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slogan")
	FString Slogan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement")
	int64 Requirement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Motd")
	FString Motd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version")
	FOptionalInt32 Version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	int64 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	FOptionalString ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles")
	FOptionalArrayOfGroupRole Roles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores")
	TMap<FString, FString> Scores;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update Enrollment")
	FOptionalBool bCanUpdateEnrollment;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Members")
	TArray<UMember*> Members;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Disband")
	FOptionalBool bCanDisband;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type")
	EGroupType Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size")
	int32 MaxSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Groups")
	TArray<UGroup*> SubGroups;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	int64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};