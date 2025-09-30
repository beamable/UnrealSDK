
#include "BeamableCore/Public/AutoGen/CustomerActorCustomerViewLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorCustomerViewLibrary::CustomerActorCustomerViewToJsonString(const UCustomerActorCustomerView* Serializable, const bool Pretty)
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

UCustomerActorCustomerView* UCustomerActorCustomerViewLibrary::Make(FString CustomerId, FString Name, FOptionalString Alias, FOptionalArrayOfRealmView Realms, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorCustomerView>(Outer);
	Serializable->CustomerId = CustomerId;
	Serializable->Name = Name;
	Serializable->Alias = Alias;
	Serializable->Realms = Realms;
	
	return Serializable;
}

void UCustomerActorCustomerViewLibrary::Break(const UCustomerActorCustomerView* Serializable, FString& CustomerId, FString& Name, FOptionalString& Alias, FOptionalArrayOfRealmView& Realms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		CustomerId = Serializable->CustomerId;
		Name = Serializable->Name;
		Alias = Serializable->Alias;
		Realms = Serializable->Realms;
	}
		
}

