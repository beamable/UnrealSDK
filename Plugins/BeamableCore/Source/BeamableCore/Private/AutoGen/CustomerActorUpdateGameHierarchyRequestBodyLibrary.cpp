
#include "BeamableCore/Public/AutoGen/CustomerActorUpdateGameHierarchyRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorUpdateGameHierarchyRequestBodyLibrary::CustomerActorUpdateGameHierarchyRequestBodyToJsonString(const UCustomerActorUpdateGameHierarchyRequestBody* Serializable, const bool Pretty)
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

UCustomerActorUpdateGameHierarchyRequestBody* UCustomerActorUpdateGameHierarchyRequestBodyLibrary::Make(TArray<URealmView*> Realms, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorUpdateGameHierarchyRequestBody>(Outer);
	Serializable->Realms = Realms;
	
	return Serializable;
}

void UCustomerActorUpdateGameHierarchyRequestBodyLibrary::Break(const UCustomerActorUpdateGameHierarchyRequestBody* Serializable, TArray<URealmView*>& Realms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Realms = Serializable->Realms;
	}
		
}

