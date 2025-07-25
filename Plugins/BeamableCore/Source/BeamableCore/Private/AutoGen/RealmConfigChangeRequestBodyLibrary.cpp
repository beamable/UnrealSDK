
#include "BeamableCore/Public/AutoGen/RealmConfigChangeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmConfigChangeRequestBodyLibrary::RealmConfigChangeRequestBodyToJsonString(const URealmConfigChangeRequestBody* Serializable, const bool Pretty)
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

URealmConfigChangeRequestBody* URealmConfigChangeRequestBodyLibrary::Make(FOptionalArrayOfString Deletes, FOptionalMapOfString Upserts, UObject* Outer)
{
	auto Serializable = NewObject<URealmConfigChangeRequestBody>(Outer);
	Serializable->Deletes = Deletes;
	Serializable->Upserts = Upserts;
	
	return Serializable;
}

void URealmConfigChangeRequestBodyLibrary::Break(const URealmConfigChangeRequestBody* Serializable, FOptionalArrayOfString& Deletes, FOptionalMapOfString& Upserts)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Deletes = Serializable->Deletes;
		Upserts = Serializable->Upserts;
	}
		
}

