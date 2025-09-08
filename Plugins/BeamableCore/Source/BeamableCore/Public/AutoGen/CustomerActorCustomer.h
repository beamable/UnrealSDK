#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealm.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCustomerActorAccount.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPaymentStatus.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalActivationStatus.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"

#include "CustomerActorCustomer.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorCustomer : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	int64 CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias", Category="Beam")
	FOptionalString Alias = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Status", Category="Beam")
	FOptionalPaymentStatus PaymentStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Activation Status", Category="Beam")
	FOptionalActivationStatus ActivationStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Contact", Category="Beam")
	FOptionalString Contact = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalDateTime Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	FOptionalDateTime Updated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realms", Category="Beam")
	FOptionalArrayOfRealm Realms = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Accounts", Category="Beam")
	FOptionalArrayOfCustomerActorAccount Accounts = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};