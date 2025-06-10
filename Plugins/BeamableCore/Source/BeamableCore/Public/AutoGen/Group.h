#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfDonationRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDonationRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupRole.h"
#include "BeamableCore/Public/AutoGen/Member.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamGroupType.h"

#include "Group.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGroup : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requirement", Category="Beam")
	int64 Requirement = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size", Category="Beam")
	int32 MaxSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Type", Category="Beam")
	EBeamGroupType Type = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	int64 Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Motd", Category="Beam")
	FString Motd = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Slogan", Category="Beam")
	FString Slogan = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leader", Category="Beam")
	int64 Leader = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	int64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Enrollment Type", Category="Beam")
	FString EnrollmentType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Free Slots", Category="Beam")
	int32 FreeSlots = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sub Groups", Category="Beam")
	TArray<UGroup*> SubGroups = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Members", Category="Beam")
	TArray<UMember*> Members = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scores", Category="Beam")
	TMap<FString, FString> Scores = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Disband", Category="Beam")
	FOptionalBool bCanDisband = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update Enrollment", Category="Beam")
	FOptionalBool bCanUpdateEnrollment = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update MOTD", Category="Beam")
	FOptionalBool bCanUpdateMOTD = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Can Update Slogan", Category="Beam")
	FOptionalBool bCanUpdateSlogan = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Shard", Category="Beam")
	FOptionalString Shard = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data", Category="Beam")
	FOptionalString ClientData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FOptionalInt32 Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag", Category="Beam")
	FOptionalString Tag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Donations", Category="Beam")
	FOptionalArrayOfDonationRequestBody Donations = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Roles", Category="Beam")
	FOptionalArrayOfGroupRole Roles = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight", Category="Beam")
	FOptionalArrayOfInFlightMessage InFlight = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Maybe Donations", Category="Beam")
	FOptionalMapOfDonationRequestBody MaybeDonations = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};