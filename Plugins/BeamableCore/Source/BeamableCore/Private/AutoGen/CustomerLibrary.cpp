
#include "BeamableCore/Public/AutoGen/CustomerLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerLibrary::CustomerToJsonString(const UCustomer* Serializable, const bool Pretty)
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

UCustomer* UCustomerLibrary::Make(FString Name, FBeamCid Cid, TArray<UProject*> Projects, TArray<URealmsBasicAccount*> Accounts, FOptionalString ActivationStatus, FOptionalString PaymentStatus, FOptionalString Image, FOptionalString Contact, FOptionalString Alias, FOptionalInt64 Updated, FOptionalString CrmLink, FOptionalInt64 Created, UObject* Outer)
{
	auto Serializable = NewObject<UCustomer>(Outer);
	Serializable->Name = Name;
	Serializable->Cid = Cid;
	Serializable->Projects = Projects;
	Serializable->Accounts = Accounts;
	Serializable->ActivationStatus = ActivationStatus;
	Serializable->PaymentStatus = PaymentStatus;
	Serializable->Image = Image;
	Serializable->Contact = Contact;
	Serializable->Alias = Alias;
	Serializable->Updated = Updated;
	Serializable->CrmLink = CrmLink;
	Serializable->Created = Created;
	
	return Serializable;
}

void UCustomerLibrary::Break(const UCustomer* Serializable, FString& Name, FBeamCid& Cid, TArray<UProject*>& Projects, TArray<URealmsBasicAccount*>& Accounts, FOptionalString& ActivationStatus, FOptionalString& PaymentStatus, FOptionalString& Image, FOptionalString& Contact, FOptionalString& Alias, FOptionalInt64& Updated, FOptionalString& CrmLink, FOptionalInt64& Created)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Cid = Serializable->Cid;
		Projects = Serializable->Projects;
		Accounts = Serializable->Accounts;
		ActivationStatus = Serializable->ActivationStatus;
		PaymentStatus = Serializable->PaymentStatus;
		Image = Serializable->Image;
		Contact = Serializable->Contact;
		Alias = Serializable->Alias;
		Updated = Serializable->Updated;
		CrmLink = Serializable->CrmLink;
		Created = Serializable->Created;
	}
		
}

