
#include "BeamableCore/Public/AutoGen/CustomerActorAliasAvailableResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorAliasAvailableResponseLibrary::CustomerActorAliasAvailableResponseToJsonString(const UCustomerActorAliasAvailableResponse* Serializable, const bool Pretty)
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

UCustomerActorAliasAvailableResponse* UCustomerActorAliasAvailableResponseLibrary::Make(FString Alias, bool bAvailable, FOptionalString CustomerId, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorAliasAvailableResponse>(Outer);
	Serializable->Alias = Alias;
	Serializable->bAvailable = bAvailable;
	Serializable->CustomerId = CustomerId;
	
	return Serializable;
}

void UCustomerActorAliasAvailableResponseLibrary::Break(const UCustomerActorAliasAvailableResponse* Serializable, FString& Alias, bool& bAvailable, FOptionalString& CustomerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Alias = Serializable->Alias;
		bAvailable = Serializable->bAvailable;
		CustomerId = Serializable->CustomerId;
	}
		
}

