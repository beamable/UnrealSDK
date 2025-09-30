
#include "BeamableCore/Public/AutoGen/CustomerActorNewCustomerRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorNewCustomerRequestBodyLibrary::CustomerActorNewCustomerRequestBodyToJsonString(const UCustomerActorNewCustomerRequestBody* Serializable, const bool Pretty)
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

UCustomerActorNewCustomerRequestBody* UCustomerActorNewCustomerRequestBodyLibrary::Make(FString RealmName, FString Email, FString Password, FOptionalBool bHierarchy, FOptionalString CustomerName, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorNewCustomerRequestBody>(Outer);
	Serializable->RealmName = RealmName;
	Serializable->Email = Email;
	Serializable->Password = Password;
	Serializable->bHierarchy = bHierarchy;
	Serializable->CustomerName = CustomerName;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UCustomerActorNewCustomerRequestBodyLibrary::Break(const UCustomerActorNewCustomerRequestBody* Serializable, FString& RealmName, FString& Email, FString& Password, FOptionalBool& bHierarchy, FOptionalString& CustomerName, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RealmName = Serializable->RealmName;
		Email = Serializable->Email;
		Password = Serializable->Password;
		bHierarchy = Serializable->bHierarchy;
		CustomerName = Serializable->CustomerName;
		Alias = Serializable->Alias;
	}
		
}

