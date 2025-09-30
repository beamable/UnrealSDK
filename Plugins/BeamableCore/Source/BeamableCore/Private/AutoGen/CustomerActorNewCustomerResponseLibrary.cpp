
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorNewCustomerResponseLibrary::CustomerActorNewCustomerResponseToJsonString(const UCustomerActorNewCustomerResponse* Serializable, const bool Pretty)
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

UCustomerActorNewCustomerResponse* UCustomerActorNewCustomerResponseLibrary::Make(UAuthResponse* Token, FString CustomerId, FString RealmId, FString Name, FString RealmName, FOptionalBool bActivationPending, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorNewCustomerResponse>(Outer);
	Serializable->Token = Token;
	Serializable->CustomerId = CustomerId;
	Serializable->RealmId = RealmId;
	Serializable->Name = Name;
	Serializable->RealmName = RealmName;
	Serializable->bActivationPending = bActivationPending;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UCustomerActorNewCustomerResponseLibrary::Break(const UCustomerActorNewCustomerResponse* Serializable, UAuthResponse*& Token, FString& CustomerId, FString& RealmId, FString& Name, FString& RealmName, FOptionalBool& bActivationPending, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
		CustomerId = Serializable->CustomerId;
		RealmId = Serializable->RealmId;
		Name = Serializable->Name;
		RealmName = Serializable->RealmName;
		bActivationPending = Serializable->bActivationPending;
		Alias = Serializable->Alias;
	}
		
}

