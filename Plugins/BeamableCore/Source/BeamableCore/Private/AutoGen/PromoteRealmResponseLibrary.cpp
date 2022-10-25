
#include "AutoGen/PromoteRealmResponseLibrary.h"

#include "CoreMinimal.h"


FString UPromoteRealmResponseLibrary::PromoteRealmResponseToJsonString(const UPromoteRealmResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UPromoteRealmResponse* UPromoteRealmResponseLibrary::Make(FString SourcePid, TArray<UPromotionScope*> Scopes, UObject* Outer)
{
	auto Serializable = NewObject<UPromoteRealmResponse>(Outer);
	Serializable->SourcePid = SourcePid;
	Serializable->Scopes = Scopes;
	
	return Serializable;
}

void UPromoteRealmResponseLibrary::Break(const UPromoteRealmResponse* Serializable, FString& SourcePid, TArray<UPromotionScope*>& Scopes)
{
	SourcePid = Serializable->SourcePid;
	Scopes = Serializable->Scopes;
		
}

