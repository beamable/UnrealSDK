
#include "BeamableCore/Public/AutoGen/RealmsBasicNewCustomerRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicNewCustomerRequestBodyLibrary::RealmsBasicNewCustomerRequestBodyToJsonString(const URealmsBasicNewCustomerRequestBody* Serializable, const bool Pretty)
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

URealmsBasicNewCustomerRequestBody* URealmsBasicNewCustomerRequestBodyLibrary::Make(FString ProjectName, FString Email, FString Password, FOptionalBool bHierarchy, FOptionalString CustomerName, FOptionalString Alias, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicNewCustomerRequestBody>(Outer);
	Serializable->ProjectName = ProjectName;
	Serializable->Email = Email;
	Serializable->Password = Password;
	Serializable->bHierarchy = bHierarchy;
	Serializable->CustomerName = CustomerName;
	Serializable->Alias = Alias;
	
	return Serializable;
}

void URealmsBasicNewCustomerRequestBodyLibrary::Break(const URealmsBasicNewCustomerRequestBody* Serializable, FString& ProjectName, FString& Email, FString& Password, FOptionalBool& bHierarchy, FOptionalString& CustomerName, FOptionalString& Alias)
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

