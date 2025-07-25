
#include "BeamableCore/Public/AutoGen/NewCustomerRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNewCustomerRequestBodyLibrary::NewCustomerRequestBodyToJsonString(const UNewCustomerRequestBody* Serializable, const bool Pretty)
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

UNewCustomerRequestBody* UNewCustomerRequestBodyLibrary::Make(FString ProjectName, FString Email, FString Password, FOptionalBool bHierarchy, FOptionalString CustomerName, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<UNewCustomerRequestBody>(Outer);
	Serializable->ProjectName = ProjectName;
	Serializable->Email = Email;
	Serializable->Password = Password;
	Serializable->bHierarchy = bHierarchy;
	Serializable->CustomerName = CustomerName;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void UNewCustomerRequestBodyLibrary::Break(const UNewCustomerRequestBody* Serializable, FString& ProjectName, FString& Email, FString& Password, FOptionalBool& bHierarchy, FOptionalString& CustomerName, FOptionalString& Alias)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ProjectName = Serializable->ProjectName;
		Email = Serializable->Email;
		Password = Serializable->Password;
		bHierarchy = Serializable->bHierarchy;
		CustomerName = Serializable->CustomerName;
		Alias = Serializable->Alias;
	}
		
}

