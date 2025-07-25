
#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetSocialStatusesResponseLibrary::GetSocialStatusesResponseToJsonString(const UGetSocialStatusesResponse* Serializable, const bool Pretty)
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

UGetSocialStatusesResponse* UGetSocialStatusesResponseLibrary::Make(TArray<USocial*> Statuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetSocialStatusesResponse>(Outer);
	Serializable->Statuses = Statuses;
	
	return Serializable;
}

void UGetSocialStatusesResponseLibrary::Break(const UGetSocialStatusesResponse* Serializable, TArray<USocial*>& Statuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Statuses = Serializable->Statuses;
	}
		
}

