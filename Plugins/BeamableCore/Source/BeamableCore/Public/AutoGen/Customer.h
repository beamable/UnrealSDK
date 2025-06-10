#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/SemanticTypes/BeamCid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Project.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicAccount.h"

#include "Customer.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomer : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FBeamCid Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Projects", Category="Beam")
	TArray<UProject*> Projects = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Accounts", Category="Beam")
	TArray<URealmsBasicAccount*> Accounts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Activation Status", Category="Beam")
	FOptionalString ActivationStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Status", Category="Beam")
	FOptionalString PaymentStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image", Category="Beam")
	FOptionalString Image = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Contact", Category="Beam")
	FOptionalString Contact = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	FOptionalInt64 Updated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Crm Link", Category="Beam")
	FOptionalString CrmLink = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalInt64 Created = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};