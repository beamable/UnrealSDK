
#include "BeamableCore/Public/AutoGen/ItemLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UItemLibrary::ItemToJsonString(const UItem* Serializable, const bool Pretty)
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

UItem* UItemLibrary::Make(int64 Id, TArray<UItemProperty*> Properties, FOptionalInt64 UpdatedAt, FOptionalString ProxyId, FOptionalFederationInfo Proxy, FOptionalInt64 CreatedAt, UObject* Outer)
{
	auto Serializable = NewObject<UItem>(Outer);
	Serializable->Id = Id;
	Serializable->Properties = Properties;
	Serializable->UpdatedAt = UpdatedAt;
	Serializable->ProxyId = ProxyId;
	Serializable->Proxy = Proxy;
	Serializable->CreatedAt = CreatedAt;
	
	return Serializable;
}

void UItemLibrary::Break(const UItem* Serializable, int64& Id, TArray<UItemProperty*>& Properties, FOptionalInt64& UpdatedAt, FOptionalString& ProxyId, FOptionalFederationInfo& Proxy, FOptionalInt64& CreatedAt)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Properties = Serializable->Properties;
		UpdatedAt = Serializable->UpdatedAt;
		ProxyId = Serializable->ProxyId;
		Proxy = Serializable->Proxy;
		CreatedAt = Serializable->CreatedAt;
	}
		
}

