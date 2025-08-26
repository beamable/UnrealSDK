
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorPromoteRealmResponseLibrary::CustomerActorPromoteRealmResponseToJsonString(const UCustomerActorPromoteRealmResponse* Serializable, const bool Pretty)
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

UCustomerActorPromoteRealmResponse* UCustomerActorPromoteRealmResponseLibrary::Make(FString SourceRealmId, FOptionalArrayOfPromotionScope Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorPromoteRealmResponse>(Outer);
	Serializable->SourceRealmId = SourceRealmId;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UCustomerActorPromoteRealmResponseLibrary::Break(const UCustomerActorPromoteRealmResponse* Serializable, FString& SourceRealmId, FOptionalArrayOfPromotionScope& Scopes)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		SourceRealmId = Serializable->SourceRealmId;
		Scopes = Serializable->Scopes;
	}
		
}

