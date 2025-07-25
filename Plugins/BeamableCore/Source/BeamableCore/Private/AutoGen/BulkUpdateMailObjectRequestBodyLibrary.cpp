
#include "BeamableCore/Public/AutoGen/BulkUpdateMailObjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBulkUpdateMailObjectRequestBodyLibrary::BulkUpdateMailObjectRequestBodyToJsonString(const UBulkUpdateMailObjectRequestBody* Serializable, const bool Pretty)
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

UBulkUpdateMailObjectRequestBody* UBulkUpdateMailObjectRequestBodyLibrary::Make(TArray<UMyMailUpdate*> UpdateMailRequests, UObject* Outer)
{
	auto Serializable = NewObject<UBulkUpdateMailObjectRequestBody>(Outer);
	Serializable->UpdateMailRequests = UpdateMailRequests;
	
	return Serializable;
}

void UBulkUpdateMailObjectRequestBodyLibrary::Break(const UBulkUpdateMailObjectRequestBody* Serializable, TArray<UMyMailUpdate*>& UpdateMailRequests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		UpdateMailRequests = Serializable->UpdateMailRequests;
	}
		
}

