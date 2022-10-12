
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Project.h"
#include "AutoGen/RealmsBasicAccount.h"

#include "Customer.generated.h"

UCLASS(BlueprintType)
class UCustomer : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Status")
	FOptionalString PaymentStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image")
	FOptionalString Image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Contact")
	FOptionalString Contact;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias")
	FOptionalString Alias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	int64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated")
	FOptionalInt64 Updated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Crm Link")
	FOptionalString CrmLink;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Projects")
	TArray<UProject*> Projects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Accounts")
	TArray<URealmsBasicAccount*> Accounts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	FOptionalInt64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};