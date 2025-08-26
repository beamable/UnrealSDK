
#include "BeamableCore/Public/AutoGen/UploadRequestsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUploadRequestsLibrary::UploadRequestsToJsonString(const UUploadRequests* Serializable, const bool Pretty)
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

UUploadRequests* UUploadRequestsLibrary::Make(TArray<UUploadRequestBody*> Request, FOptionalInt64 PlayerId, UObject* Outer)
{
	auto Serializable = NewObject<UUploadRequests>(Outer);
	Serializable->Request = Request;
	Serializable->PlayerId = PlayerId;
	
	return Serializable;
}

void UUploadRequestsLibrary::Break(const UUploadRequests* Serializable, TArray<UUploadRequestBody*>& Request, FOptionalInt64& PlayerId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Request = Serializable->Request;
		PlayerId = Serializable->PlayerId;
	}
		
}

