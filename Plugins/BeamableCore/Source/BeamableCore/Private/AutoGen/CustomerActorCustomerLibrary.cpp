
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorCustomerLibrary::CustomerActorCustomerToJsonString(const UCustomerActorCustomer* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCustomerActorCustomer* UCustomerActorCustomerLibrary::Make(int64 CustomerId, FString Name, FOptionalString Alias, FOptionalPaymentStatus PaymentStatus, FOptionalActivationStatus ActivationStatus, FOptionalString Contact, FOptionalInt64 Created, FOptionalInt64 Updated, FOptionalArrayOfRealm Realms, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorCustomer>(Outer);
	Serializable->CustomerId = CustomerId;
	Serializable->Name = Name;
	Serializable->Alias = Alias;
	Serializable->PaymentStatus = PaymentStatus;
	Serializable->ActivationStatus = ActivationStatus;
	Serializable->Contact = Contact;
	Serializable->Created = Created;
	Serializable->Updated = Updated;
	Serializable->Realms = Realms;
	
	return Serializable;
}

void UCustomerActorCustomerLibrary::Break(const UCustomerActorCustomer* Serializable, int64& CustomerId, FString& Name, FOptionalString& Alias, FOptionalPaymentStatus& PaymentStatus, FOptionalActivationStatus& ActivationStatus, FOptionalString& Contact, FOptionalInt64& Created, FOptionalInt64& Updated, FOptionalArrayOfRealm& Realms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		CustomerId = Serializable->CustomerId;
		Name = Serializable->Name;
		Alias = Serializable->Alias;
		PaymentStatus = Serializable->PaymentStatus;
		ActivationStatus = Serializable->ActivationStatus;
		Contact = Serializable->Contact;
		Created = Serializable->Created;
		Updated = Serializable->Updated;
		Realms = Serializable->Realms;
	}
		
}

