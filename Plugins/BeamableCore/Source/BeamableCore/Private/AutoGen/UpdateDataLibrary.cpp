
#include "BeamableCore/Public/AutoGen/UpdateDataLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateDataLibrary::UpdateDataToJsonString(const UUpdateData* Serializable, const bool Pretty)
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

UUpdateData* UUpdateDataLibrary::Make(FOptionalArrayOfString Deletes, FOptionalMapOfString Updates, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateData>(Outer);
	Serializable->Deletes = Deletes;
	Serializable->Updates = Updates;
	
	return Serializable;
}

void UUpdateDataLibrary::Break(const UUpdateData* Serializable, FOptionalArrayOfString& Deletes, FOptionalMapOfString& Updates)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Deletes = Serializable->Deletes;
		Updates = Serializable->Updates;
	}
		
}

